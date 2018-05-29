/* drivers/input/touchscreen/sis_i2c.c - I2C Touch panel driver for SiS 9200 family
 *
 * Copyright (C) 2011 SiS, Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * Date: 2012/11/13
 * Version:	Android_v2.05.00-A639-1113
 */

#include <linux/module.h>
#include <linux/delay.h>

#include <linux/i2c.h>
#include <linux/input.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#include "sis_i2c_ts.h"
#include <linux/linkage.h>
#include <linux/slab.h>
#include <linux/gpio.h>
#include <asm/uaccess.h>
#include <linux/irq.h>

#include <linux/bitops.h>
#include <linux/input/mt.h>
#include <linux/of_gpio.h>

//key event
#define RELEASED      0
#define PRESSED       1
#define REPEAT        2
#define NO_EVENT      3

//running mode
#define MODE_STOP	    0
#define MODE_SUSPEND	1
#define MODE_IDLE	    2
#define MODE_WORKING	3

unsigned char sis_work_state;

static int gpio_irq;
static int gpio_reset;

static struct workqueue_struct *sis_wq;
struct sisTP_driver_data *TPInfo = NULL;
static void sis_tpinfo_clear(struct sisTP_driver_data *TPInfo, int max);

/*
static struct timer_list tsp_wakeup_timer;
void func_tsp_wakeup_timer(unsigned long arg)
{
	//printk("%s(): touch to working state\n",__func__);
 	sis_work_state = MODE_WORKING;
}
*/

void PrintBuffer(int start, int length, char* buf)
{
	int i;
	for ( i = start; i < length; i++ )
	{
		printk("%02x ", buf[i]);
		if (i != 0 && i % 30 == 0)
			printk("\n");
	}
	printk("\n");	
}

int sis_command_for_write(struct i2c_client *client, int wlength, unsigned char *wdata)
{
    int ret = -1;
    struct i2c_msg msg[1];

    msg[0].addr = client->addr;
    msg[0].flags = 0; //Write
    msg[0].len = wlength;
    msg[0].buf = (unsigned char *)wdata;

    ret = i2c_transfer(client->adapter, msg, 1);

    return ret;
}

int sis_command_for_read(struct i2c_client *client, int rlength, unsigned char *rdata)
{
    int ret = -1;
    struct i2c_msg msg[1];

    msg[0].addr = client->addr;
    msg[0].flags = I2C_M_RD; //Read
    msg[0].len = rlength;
    msg[0].buf = rdata;

    ret = i2c_transfer(client->adapter, msg, 1);

    return ret;
}

int sis_cul_unit(uint8_t report_id)
{
	int basic = 6;
	int area = 2;
	int pressure = 1;
	int ret = basic;
	
	if (report_id != ALL_IN_ONE_PACKAGE)
	{
		if (IS_AREA(report_id) /*&& IS_TOUCH(report_id)*/)
		{
			ret += area;
		}
		if (IS_PRESSURE(report_id))
		{
			ret += pressure;
		}
	}
	
	return ret;	
}

int sis_ReadPacket(struct i2c_client *client, uint8_t cmd, uint8_t* buf)
{
	uint8_t tmpbuf[MAX_BYTE] = {0};	//MAX_BYTE = 64;
	int ret = -1;
	int touchnum = 0;
	int p_count = 0;
	int touc_formate_id = 0;
	int locate = 0;
	bool read_first = true;
  
	//dev_err(&client->dev, "%s()\n",__func__);
    
	/* New i2c format 
	* buf[0] = Low 8 bits of byte count value
	* buf[1] = High 8 bits of byte counte value
	* buf[2] = Report ID
	* buf[touch num * 6 + 2 ] = Touch informations; 1 touch point has 6 bytes, it could be none if no touch 
	* buf[touch num * 6 + 3] = Touch numbers
	* 
	* One touch point information include 6 bytes, the order is 
	* 
	* 1. status = touch down or touch up
	* 2. id = finger id 
	* 3. x axis low 8 bits
	* 4. x axis high 8 bits
	* 5. y axis low 8 bits
	* 6. y axis high 8 bits
	*/
	do
	{
		if (locate >= PACKET_BUFFER_SIZE)
		{
			printk(KERN_ERR "sis_ReadPacket: Buf Overflow\n");
			return -1;
		}
		
		ret = sis_command_for_read(client, MAX_BYTE, tmpbuf);

#ifdef _DEBUG_PACKAGE
		printk(KERN_INFO "chaoban test: Buf_Data [0~63] \n");
		PrintBuffer(0, 64, tmpbuf);	
#endif			

		if(ret < 0 )
		{
			printk(KERN_ERR "sis_ReadPacket: i2c transfer error\n");
			return ret;
		}
		// error package length of receiving data
		else if (tmpbuf[P_BYTECOUNT] > MAX_BYTE)
		{
			printk(KERN_ERR "sis_ReadPacket: Error Bytecount\n");
			return -1;	
		}
		
		if (read_first)
		{
			// access NO TOUCH event unless BUTTON NO TOUCH event
			if (tmpbuf[P_BYTECOUNT] == 0/*NO_TOUCH_BYTECOUNT*/)
			{
				return touchnum;	//touchnum is 0
			}
		}

		//skip parsing data when two devices are registered at the same slave address
		//parsing data when P_REPORT_ID && 0xf is TOUCH_FORMAT or P_REPORT_ID is ALL_IN_ONE_PACKAGE
		touc_formate_id = tmpbuf[P_REPORT_ID] & 0xf;
		if ((touc_formate_id != TOUCH_FORMAT) && (touc_formate_id != HIDI2C_FORMAT) && (tmpbuf[P_REPORT_ID] != ALL_IN_ONE_PACKAGE))
		{
			printk(KERN_ERR "sis_ReadPacket: Error Report_ID\n");
			return -1;		
		}
		
		p_count = (int) tmpbuf[P_BYTECOUNT] - 1;	//start from 0
		if (tmpbuf[P_REPORT_ID] != ALL_IN_ONE_PACKAGE)
		{
			if (IS_TOUCH(tmpbuf[P_REPORT_ID]))
			{
				p_count -= BYTE_CRC_I2C;	//delete 2 byte crc
			}
			else if (IS_HIDI2C(tmpbuf[P_REPORT_ID]))
			{
				p_count -= BYTE_CRC_HIDI2C;
			}
			else	//should not be happen
			{
				printk(KERN_ERR "sis_ReadPacket: delete crc error\n");
				return -1;
			}

			if (IS_SCANTIME(tmpbuf[P_REPORT_ID]))
			{
				p_count -= BYTE_SCANTIME;
			}
		}
		//else {}    						// For ALL_IN_ONE_PACKAGE
		
		if (read_first)
		{
			touchnum = tmpbuf[p_count]; 	
		}
		else
		{
			if (tmpbuf[p_count] != 0)
			{
				printk(KERN_ERR "sis_ReadPacket: get error package\n");
				return -1;
			}
		}

		memcpy(&buf[locate], &tmpbuf[0], 64);	//Buf_Data [0~63] [64~128]
		locate += 64;
		read_first = false;
		
	}while(tmpbuf[P_REPORT_ID] != ALL_IN_ONE_PACKAGE  &&  tmpbuf[p_count] > 5);

	return touchnum;
}

static void sis_ts_work_func(struct work_struct *work)
{
	struct sis_ts_data *ts = container_of(work, struct sis_ts_data, work);
	int ret = -1;
	int point_unit;  
	uint8_t buf[PACKET_BUFFER_SIZE] = {0};
	uint8_t i = 0, fingers = 0;
	uint8_t px = 0, py = 0, pstatus = 0;
	uint8_t p_area = 0;
	uint8_t p_preasure = 0;
	bool all_touch_up = true;
	
	//dev_err(&ts->client->dev, "%s()\n",__func__);
	
	mutex_lock(&ts->mutex_wq); 
	
	/* I2C or SMBUS block data read */
	ret = sis_ReadPacket(ts->client, SIS_CMD_NORMAL, buf);
#ifdef _DEBUG_PACKAGE_WORKFUNC
	printk(KERN_INFO "zerget ret:%d\n", ret);
	printk(KERN_INFO "chaoban test: Buf_Data [0~63] \n");
	PrintBuffer(0, 64, buf);			
	if ((buf[P_REPORT_ID] != ALL_IN_ONE_PACKAGE) && (ret > 5))
	{
		printk(KERN_INFO "chaoban test: Buf_Data [64~125] \n");
		PrintBuffer(64, 128, buf);	
	}
#endif

	if (ret < 0) // Error Number
	{
	    printk(KERN_INFO "chaoban test: ret = -1\n");
		goto err_free_allocate;
	}
	// access NO TOUCH event unless BUTTON NO TOUCH event
	else if (ret == 0)
	{
		fingers = 0;
		sis_tpinfo_clear(TPInfo, MAX_FINGERS);
		goto label_send_report;  //need to report input_mt_sync()
	}
	
	sis_tpinfo_clear(TPInfo, MAX_FINGERS);
	
#if 1 //SKJ 20160221 : Wake up 모드 설정 (절전모드 깨어나면서 터치가 먹지 안하게 하기 위해)
	if(sis_work_state < MODE_WORKING)
	{
		//printk("%s(): not working state=%d... return\n",__func__, sis_work_state);
		goto label_send_report;  //need to report input_mt_sync()
	}
#endif
	
	/* Parser and Get the sis9200 data */
	point_unit = sis_cul_unit(buf[P_REPORT_ID]);
	fingers = ret;
	
	TPInfo->fingers = fingers = (fingers > MAX_FINGERS ? 0 : fingers);
	
	for (i = 0; i < fingers; i++) // fingers 10 =  0 ~ 9
	{
    if ((buf[P_REPORT_ID] != ALL_IN_ONE_PACKAGE) && (i >= 5))
    {
			pstatus = BYTE_BYTECOUNT + BYTE_ReportID + ((i - 5) * point_unit);    	// Calc point status
			pstatus += 64;
		}
		else 
		{
			pstatus = BYTE_BYTECOUNT + BYTE_ReportID + (i * point_unit);          	// Calc point status
		}

    px = pstatus + 2;                   			// Calc point x_coord
    py = px + 2;                        			// Calc point y_coord

		if ((buf[pstatus]) == TOUCHUP)
		{
			TPInfo->pt[i].Width = 0;
			TPInfo->pt[i].Height = 0;
			TPInfo->pt[i].Pressure = 0;
		}
		else if (buf[P_REPORT_ID] == ALL_IN_ONE_PACKAGE && (buf[pstatus]) == TOUCHDOWN)
		{
			TPInfo->pt[i].Width = 1;
			TPInfo->pt[i].Height = 1;
			TPInfo->pt[i].Pressure = 1;			
		}
		else if ((buf[pstatus]) == TOUCHDOWN)
		{	
			p_area = py + 2;
			p_preasure = py + 2 + (IS_AREA(buf[P_REPORT_ID]) * 2);

			//area		
			if (IS_AREA(buf[P_REPORT_ID]))
			{
				TPInfo->pt[i].Width = buf[p_area] & 0xff;
				TPInfo->pt[i].Height = buf[p_area + 1] & 0xff;
			}
			else 
			{
				TPInfo->pt[i].Width = 1;
				TPInfo->pt[i].Height = 1;
			}
			//preasure
			if (IS_PRESSURE(buf[P_REPORT_ID]))
				TPInfo->pt[i].Pressure = (buf[p_preasure]);
			else 
				TPInfo->pt[i].Pressure = 1;				
		}
		else
		{
			printk(KERN_ERR "sis_ts_work_func: Error Touch Status\n");
			goto err_free_allocate;
		}
		
		TPInfo->pt[i].id = (buf[pstatus + 1]);
		TPInfo->pt[i].x = ((buf[px] & 0xff) | ((buf[px + 1] & 0xff)<< 8));
    TPInfo->pt[i].y = ((buf[py] & 0xff) | ((buf[py + 1] & 0xff)<< 8));      
	}
		
#ifdef _DEBUG_REPORT
	for (i = 0; i < TPInfo->fingers; i++)
	{
		dev_err(&ts->client->dev, "DEBUG: i = %d, id = %d, x = %d, y = %d, pstatus = %d, width = %d, height = %d, pressure = %d, \n", i, TPInfo->pt[i].id, TPInfo->pt[i].x, TPInfo->pt[i].y, buf[pstatus], TPInfo->pt[i].Width,  TPInfo->pt[i].Height, TPInfo->pt[i].Pressure);
	}
#endif

label_send_report:
	/* Report co-ordinates to the multi-touch stack */
	for(i = 0; ((i < TPInfo->fingers) && (i < MAX_FINGERS)); i++)
	{
		if(TPInfo->pt[i].Pressure)
		{
			TPInfo->pt[i].Width *= AREA_UNIT;	
			input_report_abs(ts->input_dev, ABS_MT_TOUCH_MAJOR, TPInfo->pt[i].Width);
			TPInfo->pt[i].Height *= AREA_UNIT;
			input_report_abs(ts->input_dev, ABS_MT_TOUCH_MINOR, TPInfo->pt[i].Height);			
			input_report_abs(ts->input_dev, ABS_MT_PRESSURE, TPInfo->pt[i].Pressure);
			input_report_abs(ts->input_dev, ABS_MT_POSITION_X, TPInfo->pt[i].x);
			input_report_abs(ts->input_dev, ABS_MT_POSITION_Y, TPInfo->pt[i].y);
			input_report_abs(ts->input_dev, ABS_MT_TRACKING_ID, TPInfo->pt[i].id);     //Android 2.3
			input_mt_sync(ts->input_dev);
			all_touch_up = false;
		}
		
		if (i == (TPInfo->fingers -1) && all_touch_up == true)
		{
			input_mt_sync(ts->input_dev);
		}
	}

	if(TPInfo->fingers == 0)
	{
		input_mt_sync(ts->input_dev);
	}

	input_sync(ts->input_dev);

err_free_allocate:
    if (ts->use_irq)
    {
		enable_irq(ts->client->irq);
	}

	mutex_unlock(&ts->mutex_wq);
	return;
}

static void sis_tpinfo_clear(struct sisTP_driver_data *TPInfo, int max)
{
	int i = 0;
	for(i = 0; i < max; i++)
	{
		TPInfo->pt[i].id = -1;
		TPInfo->pt[i].x = 0;
		TPInfo->pt[i].y = 0;
		TPInfo->pt[i].Pressure = 0;
		TPInfo->pt[i].Width = 0;
	}
	TPInfo->id = 0x0;
	TPInfo->fingers = 0;
}

static irqreturn_t sis_ts_irq_handler(int irq, void *dev_id)
{
	struct sis_ts_data *ts = dev_id;
	struct i2c_client *client = ts->client;
	
	if(sis_work_state == MODE_SUSPEND)
	{
		dev_err(&client->dev, "%s() : MODE_SUSPEND\n",__func__);
		input_report_key(ts->input_dev, KEY_F1, PRESSED);
		input_sync(ts->input_dev);
		input_report_key(ts->input_dev, KEY_F1, RELEASED);
		input_sync(ts->input_dev);
	
		//tsp_wakeup_timer.expires = get_jiffies_64() + (1*HZ/2); //500ms
		//add_timer(&tsp_wakeup_timer);
	}
	
	disable_irq_nosync(ts->client->irq);
	queue_work(sis_wq, &ts->work);
		
	return IRQ_HANDLED;
}

uint16_t cal_crc (char* cmd, int start, int end)
{
	int i = 0;
	uint16_t crc = 0;
	for (i = start; i <= end ; i++)
	{
		crc = (crc<<8) ^ crc16tab[((crc>>8) ^ cmd[i] )&0x00FF];
	}
	return crc;
}

uint16_t cal_crc_with_cmd (char* data, int start, int end, uint8_t cmd)
{
	int i = 0;
	uint16_t crc = 0;
	
	crc = (crc<<8) ^ crc16tab[((crc>>8) ^ cmd)&0x00FF];
	for (i = start; i <= end ; i++)
	{
		crc = (crc<<8) ^ crc16tab[((crc>>8) ^ data[i] )&0x00FF];
	}
	return crc;
}

void write_crc (unsigned char *buf, int start, int end)
{
	uint16_t crc = 0;
	crc = cal_crc (buf, start , end);
	buf[end+1] = (crc >> 8)& 0xff;
	buf[end+2] = crc & 0xff;
}

static int sis_ts_probe(
	struct i2c_client *client, const struct i2c_device_id *id)
{
	int ret = 0;
	struct sis_ts_data *ts = NULL;
	struct device *dev = &client->dev;

	dev_err(dev, "%s() Start\n",__func__);
	
	dev_err(dev, "%s() : allocate memory\n",__func__);
    TPInfo = kzalloc(sizeof(struct sisTP_driver_data), GFP_KERNEL);
    if (TPInfo == NULL) 
    {
		dev_err(dev, "Failed to allocate memory\n");
		return -ENOMEM;
	}

	ts = kzalloc(sizeof(*ts), GFP_KERNEL);
	if (ts == NULL) 
	{
		dev_err(dev, "Failed to allocate memory\n");
		return -ENOMEM;
	}
	
	ts->input_dev = devm_input_allocate_device(&client->dev);
	if (ts->input_dev == NULL) 
	{
		dev_err(dev, "Failed to allocate memory\n");
		return -ENOMEM;
	}
	ts->client = client;
	
	mutex_init(&ts->mutex_wq);	

	dev_err(dev, "%s() : configure gpios\n",__func__);
	gpio_reset = of_get_named_gpio(dev->of_node, "reset-gpio", 0);
	if (gpio_reset < 0) {
		dev_err(dev, "cannot get reset-gpios %d\n",	gpio_reset);
		return gpio_reset;
	}
	gpio_direction_output(gpio_reset, 0);
	gpio_request(gpio_reset, "touchreset");
	msleep(10);
	gpio_direction_output(gpio_reset, 1);

	gpio_irq = of_get_named_gpio(dev->of_node, "int-gpio", 0);
	if (gpio_irq < 0) {
		dev_err(dev, "cannot get int-gpios %d\n", gpio_irq);
		return gpio_irq;
	}
	gpio_direction_input(gpio_irq);
	
	dev_err(dev, "%s() : create_singlethread_workqueue\n",__func__);
	sis_wq = create_singlethread_workqueue("sis_wq");
	if (!sis_wq)
		return -ENOMEM;
	INIT_WORK(&ts->work, sis_ts_work_func);

	ts->input_dev->name = "sis_i2c_ts";
	ts->input_dev->id.bustype = BUS_I2C;

	set_bit(EV_ABS, ts->input_dev->evbit);
	set_bit(EV_KEY, ts->input_dev->evbit);
	set_bit(ABS_MT_POSITION_X, ts->input_dev->absbit);
	set_bit(ABS_MT_POSITION_Y, ts->input_dev->absbit);
	set_bit(ABS_MT_TRACKING_ID, ts->input_dev->absbit);

	set_bit(ABS_MT_PRESSURE, ts->input_dev->absbit);
	set_bit(ABS_MT_TOUCH_MAJOR, ts->input_dev->absbit);
	set_bit(ABS_MT_TOUCH_MINOR, ts->input_dev->absbit);
	input_set_abs_params(ts->input_dev, ABS_MT_PRESSURE, 0, PRESSURE_MAX, 0, 0);
	input_set_abs_params(ts->input_dev, ABS_MT_TOUCH_MAJOR, 0, AREA_LENGTH_LONGER, 0, 0);
	input_set_abs_params(ts->input_dev, ABS_MT_TOUCH_MINOR, 0, AREA_LENGTH_SHORT, 0, 0);   

	input_set_abs_params(ts->input_dev, ABS_MT_POSITION_X, 0, SIS_MAX_X, 0, 0);
	input_set_abs_params(ts->input_dev, ABS_MT_POSITION_Y, 0, SIS_MAX_Y, 0, 0);
	input_set_abs_params(ts->input_dev, ABS_MT_TRACKING_ID, 0, 15, 0, 0);

	/* add for touch keys */
	set_bit(KEY_COMPOSE, ts->input_dev->keybit);
	set_bit(KEY_BACK, ts->input_dev->keybit);
	set_bit(KEY_MENU, ts->input_dev->keybit);
	set_bit(KEY_HOME, ts->input_dev->keybit);
	set_bit(KEY_F1 & KEY_MAX, ts->input_dev->keybit);
	
	sis_work_state = MODE_WORKING;
	//init_timer(&tsp_wakeup_timer);
	//tsp_wakeup_timer.function = func_tsp_wakeup_timer;

	dev_err(dev, "%s() : devm_request_threaded_irq\n",__func__);
	ret = devm_request_threaded_irq(&client->dev, client->irq, NULL,
					  sis_ts_irq_handler,
					  IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
					  "sis_i2c_ts", ts);
	if (ret < 0) {
		dev_err(&client->dev, "Failed to register interrupt\n");
		return ret;
	}
	else
	{
		ts->use_irq = 1;
	}
	
	dev_err(dev, "%s() : input_register_device\n",__func__);
	ret = input_register_device(ts->input_dev);
	if (ret) 
	{
		dev_err(dev, "%s(): Unable to register %s input device\n",__func__, ts->input_dev->name);
		return ret;
	}
	
	dev_err(dev, "%s() : i2c_set_clientdata\n",__func__);
	i2c_set_clientdata(client, ts);

	dev_err(dev, "%s() End\n",__func__);
	
	return 0;
}

static int sis_ts_remove(struct i2c_client *client)
{
	struct sis_ts_data *ts = i2c_get_clientdata(client);

	if (ts->use_irq)
		free_irq(client->irq, ts);
		
	input_unregister_device(ts->input_dev);
	kfree(ts);
	return 0;
}

static int sis_ts_suspend(struct device *dev)
{
	struct i2c_client *client = to_i2c_client(dev);
	
	dev_err(dev, "%s()\n",__func__);
	sis_work_state = MODE_SUSPEND;
	flush_workqueue(sis_wq); 	   		// only flush sis_wq
	
	return 0;
}

static int sis_ts_resume(struct device *dev)
{
	struct i2c_client *client = to_i2c_client(dev);
	
	dev_err(dev, "%s()\n",__func__);
	sis_work_state = MODE_WORKING;
	return 0;
}

static SIMPLE_DEV_PM_OPS(sis_ts_pm_ops, sis_ts_suspend, sis_ts_resume);

static const struct i2c_device_id sis_ts_id[] = {
	{ SIS_I2C_NAME, 0 },
	{ }
};
MODULE_DEVICE_TABLE(i2c, sis_ts_id);

static const struct of_device_id sis_i2c_of_match[] = {
	{ .compatible = "sis,sis_i2c_ts", },
	{},
};
MODULE_DEVICE_TABLE(of, sis_i2c_of_match);

static struct i2c_driver sis_ts_driver = {
	.probe		= sis_ts_probe,
	.remove		= sis_ts_remove,
	.id_table	= sis_ts_id,
	.driver = {
		.name	= SIS_I2C_NAME,
		.pm	= &sis_ts_pm_ops,
		.of_match_table = sis_i2c_of_match,
	},
};
module_i2c_driver(sis_ts_driver);

MODULE_DESCRIPTION("SiS 9200 Family Touchscreen Driver");
MODULE_LICENSE("GPL");
