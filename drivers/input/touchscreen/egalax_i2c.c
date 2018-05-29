/*
 *
 * Touch Screen I2C Driver for EETI Controller
 *
 * Copyright (C) 2000-2015  eGalax_eMPIA Technology Inc.
 * All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#define RELEASE_DATE "2015/06/03 DM SKJ 151015"

#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/wait.h>
#include <linux/delay.h>
#include <linux/i2c.h>
#include <linux/gpio.h>
#include <linux/device.h>
#include <asm/uaccess.h>
#include <linux/kfifo.h>
#include <linux/version.h>
#include <linux/input.h>
#include <linux/irq.h>
#include <linux/timer.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/miscdevice.h>
#include <linux/slab.h>
#include <linux/poll.h>
#include <linux/input/mt.h>
#include <linux/of_gpio.h>

	#define __devinit 
	#define __devexit 
	#define __devexit_p(x) x

//SKJ 20150622 for EETI Touch for SHN-8912
#define GPIO_IRQ 						EXTINT_GPIOE_27

// Global define to enable function
//#define _SWITCH_XY
//#define _CONVERT_Y

#define MAX_EVENTS		600
#define MAX_I2C_LEN		64
#define FIFO_SIZE		8192 //(PAGE_SIZE*2)
#define MAX_SUPPORT_POINT	16
#define REPORTID_VENDOR		0x03
#define REPORTID_MTOUCH_SERIAL	0x04
#define REPORTID_MTOUCH		0x06
#define MAX_RESOLUTION		4095

// running mode
#define MODE_STOP	0
#define MODE_WORKING	1
#define MODE_IDLE	2
#define MODE_SUSPEND	3

// protocol mode
#define PROTOCOL_HIDI2C	0
#define PROTOCOL_EETI	1

#if 1 //SKJ 20160114 : Wake up 모드 설정
//key event
#define RELEASED      0
#define PRESSED       1
#define REPEAT        2
#define NO_EVENT      3
#endif

struct tagMTContacts {
	unsigned char ID;
	signed char Status;
	unsigned short X;
	unsigned short Y;
};

struct _egalax_i2c {
	struct workqueue_struct *ktouch_wq;
	struct work_struct work_irq;
	struct delayed_work delay_work_cmd;
	struct mutex mutex_wq;
	struct i2c_client *client;
	unsigned char work_state;
	unsigned char skip_packet;
	unsigned int ioctl_cmd;
	int interrupt_gpio;
	unsigned char protocol;
	unsigned char input_length;
};

struct egalax_char_dev
{
	int OpenCnts;
	struct kfifo DataKFiFo;
	unsigned char *pFiFoBuf;
	spinlock_t FiFoLock;
	struct semaphore sem;
	wait_queue_head_t fifo_inq;
};

static struct _egalax_i2c *p_egalax_i2c_dev = NULL;	// allocated in egalax_i2c_probe
static struct egalax_char_dev *p_char_dev = NULL;	// allocated in init_module
static atomic_t egalax_char_available = ATOMIC_INIT(1);
static atomic_t wait_command_ack = ATOMIC_INIT(0);
static struct input_dev *input_dev = NULL;
static struct tagMTContacts pContactBuf[MAX_SUPPORT_POINT];
static unsigned char input_report_buf[MAX_I2C_LEN+2] = {0};
static unsigned char vendor_cmd_buf[MAX_I2C_LEN] = {0};
static int iCmdReadLen = 0, iTargetCmdLen = 0;

#define DBG_MODULE	0x00000001
#define DBG_CDEV	0x00000002
#define DBG_PROC	0x00000004
#define DBG_POINT	0x00000008
#define DBG_INT		0x00000010
#define DBG_I2C		0x00000020
#define DBG_SUSP	0x00000040
#define DBG_INPUT	0x00000080
#define DBG_CONST	0x00000100
#define DBG_IDLE	0x00000200
#define DBG_WAKEUP	0x00000400
#define DBG_BUTTON	0x00000800
static unsigned int DbgLevel = DBG_MODULE | DBG_POINT;

#define PROC_FS_NAME	"egalax_dbg"
#define PROC_FS_MAX_LEN	8
static struct proc_dir_entry *dbgProcFile;

#define EGALAX_DBG(level, fmt, args...)  do{ if( (level&DbgLevel)>0 ) \
					printk( KERN_DEBUG "[egalax_i2c]: " fmt, ## args); }while(0)

static int egalax_I2C_read(unsigned char *pBuf, unsigned short len)
{
	struct i2c_msg xfer;

	if(pBuf==NULL)
		return -1;

	// Read device data
	xfer.addr = p_egalax_i2c_dev->client->addr;
	xfer.flags = I2C_M_RD;
	xfer.len = len;
	xfer.buf = pBuf;

	if(i2c_transfer(p_egalax_i2c_dev->client->adapter, &xfer, 1) != 1) 
	{
		EGALAX_DBG(DBG_MODULE, " %s: i2c transfer fail\n", __func__);
		return -EIO;
	}
	else
		EGALAX_DBG(DBG_I2C, " %s: i2c transfer success\n", __func__);

	return 0;
}

static int egalax_I2C_write(unsigned short reg, unsigned char *pBuf, unsigned short len)
{
	unsigned char cmdbuf[80]={0}, validXfer=0, idx, i;
	struct i2c_msg xfer[8];

	if(pBuf==NULL)
		return -1;

	if(p_egalax_i2c_dev->protocol==PROTOCOL_HIDI2C)
	{
		cmdbuf[0] = reg & 0x00FF;
		cmdbuf[1] = (reg >> 8) & 0x00FF;
		cmdbuf[2] = (len+2) & 0x00FF;
		cmdbuf[3] = ((len+2) >> 8) & 0x00FF;
		memcpy(cmdbuf+4, pBuf, len);

		// Write data to device
		xfer[0].addr = p_egalax_i2c_dev->client->addr;
		xfer[0].flags = 0;
		xfer[0].len = 4+len;
		xfer[0].buf = cmdbuf;

		validXfer = 1;
	}
	else
	{
		len = pBuf[1]+2;
		idx = len/8;
		if(len%8) idx++;
		for(i=0; i<idx; i++)
		{
			xfer[i].addr = p_egalax_i2c_dev->client->addr;
			xfer[i].flags = 0;
			xfer[i].len = 10;

			*(cmdbuf+i*10) = 0x03;
			*(cmdbuf+i*10+1) = (len-i*8>=8?8:len-i*8);
			memcpy(cmdbuf+i*10+2, pBuf+i*8, *(cmdbuf+i*10+1));
			xfer[i].buf = cmdbuf+i*10;
			validXfer++;
		}	
	}

	for(i=0; i<validXfer; i++)
	{
		if(i2c_transfer(p_egalax_i2c_dev->client->adapter, &(xfer[i]), 1) != 1) 
		{
			EGALAX_DBG(DBG_MODULE, " %s: i2c transfer fail\n", __func__);
			return -EIO;
		}
	}
	
	EGALAX_DBG(DBG_I2C, " %s: i2c transfer success\n", __func__);

	return 0;
}

static int wakeup_controller(int irq)
{
	int ret = 0;
#if 0   //SKJ : 20151014 for not suspend mode
	disable_irq(irq);
	
	gpio_direction_output(p_egalax_i2c_dev->interrupt_gpio, 0);
	udelay(200);
	gpio_direction_input(p_egalax_i2c_dev->interrupt_gpio); //return to high level
	
	enable_irq(irq);
#endif	
	EGALAX_DBG(DBG_WAKEUP, " INT wakeup touch controller done\n");
	
	return ret;
}

static int ChkProtoCnt=0;
static bool check_protocol(struct _egalax_i2c *p_egalax_i2c)
{
	unsigned char buf[10] = {0};

	if( egalax_I2C_read(buf, sizeof(buf))==0 )
	{
		if(buf[0]==0x03 || buf[0]==0x04)
		{
			p_egalax_i2c->protocol = PROTOCOL_EETI;
			p_egalax_i2c->input_length = 10;
		}
		else if(buf[0]==0x00)
		{
			ChkProtoCnt++;
			if(ChkProtoCnt>=3)
			{
				p_egalax_i2c->protocol = PROTOCOL_EETI;
				p_egalax_i2c->input_length = 10;
			}
			else
			{
				return false;
			}
		}
		else
		{
			p_egalax_i2c->protocol = PROTOCOL_HIDI2C;
			p_egalax_i2c->input_length = MAX_I2C_LEN+2;
		}
		ChkProtoCnt = 0;

		EGALAX_DBG(DBG_MODULE, " Detect I2C protocol: %d\n", p_egalax_i2c->protocol);
		return true;
	}

	return false;
}

static void postPointReport(unsigned char id, short pointStatus, unsigned int pointX, unsigned int pointY)
{
	input_mt_slot(input_dev, id);
	input_mt_report_slot_state(input_dev, MT_TOOL_FINGER, pointStatus);
	if(pointStatus)
	{
		input_report_abs(input_dev, ABS_MT_TOUCH_MAJOR, pointStatus);
		input_report_abs(input_dev, ABS_MT_POSITION_X, pointX);
		input_report_abs(input_dev, ABS_MT_POSITION_Y, pointY);
	}
}

static int LastUpdateID = 0;
static void ProcessSerialReport(unsigned char *buf, struct _egalax_i2c *p_egalax_i2c)
{
	int i, cnt_down=0, cnt_up=0;
	short x=0, y=0, contactID=0, status=0;
	bool bNeedReport = false;

	status = buf[1]&0x01;
	contactID = (buf[1]&0x7C)>>2;
	x = ((buf[3]<<8) + buf[2])>>3;
	y = ((buf[5]<<8) + buf[4])>>3;
	
	if( !(contactID>=0 && contactID<MAX_SUPPORT_POINT) )
	{
		EGALAX_DBG(DBG_POINT, " Get Serial Point data error [%02X][%02X][%02X][%02X][%02X][%02X]\n", buf[0], buf[1], buf[2], buf[3], buf[4], buf[5]);
		return;
	}

#ifdef _SWITCH_XY
	short tmp = x;
	x = y;
	y = tmp;
#endif
#ifdef _CONVERT_X
	x = MAX_RESOLUTION-x;
#endif
#ifdef _CONVERT_Y
	y = MAX_RESOLUTION-y;
#endif

	pContactBuf[contactID].X = x;
	pContactBuf[contactID].Y = y;
	if(pContactBuf[contactID].Status!=status)
	{		
		pContactBuf[contactID].Status = status;
		bNeedReport = true;
	}

	EGALAX_DBG(DBG_POINT, " Get Serial Point[%d] Update: Status=%d X=%d Y=%d\n", contactID, status, x, y);

	// Send point report
	if( bNeedReport || (contactID <= LastUpdateID) )
	{
		for(i=0; i<MAX_SUPPORT_POINT; i++)
		{
			if(pContactBuf[i].Status >= 0)
			{
				postPointReport(i, pContactBuf[i].Status, pContactBuf[i].X, pContactBuf[i].Y);

				if(pContactBuf[i].Status == 0)
				{
					pContactBuf[i].Status--;
					cnt_up++;
				}
				else
					cnt_down++;
			}
		}
	
		input_sync(input_dev);

		EGALAX_DBG(DBG_POINT, " Input sync point data done! (Down:%d Up:%d)\n", cnt_down, cnt_up);
	}

	LastUpdateID = contactID;
}

#define MAX_POINT_PER_PACKET	5
#define POINT_STRUCT_SIZE	10
static int TotalPtsCnt=0, RecvPtsCnt=0;
static void ProcessReport(unsigned char *buf, struct _egalax_i2c *p_egalax_i2c)
{
	unsigned char i, index=0, cnt_down=0, cnt_up=0, shift=0;
	unsigned char status=0;
	unsigned short contactID=0, x=0, y=0;

	if(TotalPtsCnt<=0)
	{
		if(buf[1]==0 || buf[1]>MAX_SUPPORT_POINT)
		{
			EGALAX_DBG(DBG_POINT, " NumsofContacts mismatch, skip packet\n");
			return;
		}

		TotalPtsCnt = buf[1];
		RecvPtsCnt = 0;
	}
	else if(buf[1]>0)
	{
		TotalPtsCnt = RecvPtsCnt = 0;
		EGALAX_DBG(DBG_POINT, " NumsofContacts mismatch, skip packet\n");
		return;
	}

	while(index<MAX_POINT_PER_PACKET)
	{
		shift = index * POINT_STRUCT_SIZE + 2;
		status = buf[shift] & 0x01;
		contactID = buf[shift+1];
		x = ((buf[shift+3]<<8) + buf[shift+2]);
		y = ((buf[shift+5]<<8) + buf[shift+4]);

		if( contactID>=MAX_SUPPORT_POINT )
		{
			TotalPtsCnt = RecvPtsCnt = 0;
			EGALAX_DBG(DBG_MODULE, " Get error ContactID.\n");
			return;
		}

		EGALAX_DBG(DBG_POINT, " Get Point[%d] Update: Status=%d X=%d Y=%d\n", contactID, status, x, y);

	#ifdef _SWITCH_XY
		short tmp = x;
		x = y;
		y = tmp;
	#endif
	#ifdef _CONVERT_X
		x = MAX_RESOLUTION-x;
	#endif

	#ifdef _CONVERT_Y
		y = MAX_RESOLUTION-y;
	#endif

		pContactBuf[RecvPtsCnt].ID = contactID;
		pContactBuf[RecvPtsCnt].Status = status;
		pContactBuf[RecvPtsCnt].X = x;
		pContactBuf[RecvPtsCnt].Y = y;

		RecvPtsCnt++;
		index++;

		// Recv all points, send input report
		if(RecvPtsCnt==TotalPtsCnt)
		{
			for(i=0; i<RecvPtsCnt; i++)
			{
				postPointReport(pContactBuf[i].ID, pContactBuf[i].Status, pContactBuf[i].X, pContactBuf[i].Y);

				if(pContactBuf[i].Status)
					cnt_down++;
				else
					cnt_up++;
			}

			input_sync(input_dev);
			EGALAX_DBG(DBG_POINT, " Input sync point data done! (Down:%d Up:%d)\n", cnt_down, cnt_up);
			
			TotalPtsCnt = RecvPtsCnt = 0;
			return;
		}
	}
}

static struct input_dev * allocate_Input_Dev(void)
{
	int ret;
	struct input_dev *pInputDev=NULL;

	pInputDev = input_allocate_device();
	if(pInputDev == NULL)
	{
		EGALAX_DBG(DBG_MODULE, " Failed to allocate input device\n");
		return NULL;//-ENOMEM;
	}

	pInputDev->name = "eGalax_Touch_Screen";
	pInputDev->phys = "I2C";
	pInputDev->id.bustype = BUS_I2C;
	pInputDev->id.vendor = 0x0EEF;
	pInputDev->id.product = 0x0020;
	pInputDev->id.version = 0x0001;
	
#if 1 //SKJ 20160114 : Wake up 모드 설정
	pInputDev->evbit[0] |= BIT_MASK(EV_ABS) | BIT_MASK(EV_KEY);
  set_bit(KEY_F1 & KEY_MAX, pInputDev->keybit);
#else    
	set_bit(EV_ABS, pInputDev->evbit);
#endif
    
	__set_bit(INPUT_PROP_DIRECT, pInputDev->propbit);
	input_mt_init_slots(pInputDev, MAX_SUPPORT_POINT, 0);
	input_set_abs_params(pInputDev, ABS_MT_POSITION_X, 0, MAX_RESOLUTION, 0, 0);
	input_set_abs_params(pInputDev, ABS_MT_POSITION_Y, 0, MAX_RESOLUTION, 0, 0);
	input_set_abs_params(pInputDev, ABS_MT_TOUCH_MAJOR, 0, 255, 0, 0);

	input_set_events_per_packet(pInputDev, MAX_EVENTS);

	ret = input_register_device(pInputDev);
	if(ret) 
	{
		EGALAX_DBG(DBG_MODULE, " Unable to register input device.\n");
		input_free_device(pInputDev);
		pInputDev = NULL;
	}
	
	return pInputDev;
}

static int egalax_i2c_measure(struct _egalax_i2c *egalax_i2c)
{
	int ret=0, frameLen=0, loop=3, i;
	unsigned char header=0;
	unsigned char *pVendorBufData;

	EGALAX_DBG(DBG_INT, " egalax_i2c_measure\n");

	if( egalax_I2C_read(input_report_buf, egalax_i2c->input_length) < 0)
	{
		EGALAX_DBG(DBG_MODULE, " I2C read input report fail!\n");
		return -1;
	}
	
	if( DbgLevel&DBG_I2C )
	{
		char dbgmsg[(MAX_I2C_LEN+2)*4];
		for(i=0; i<egalax_i2c->input_length; i++)
			sprintf(dbgmsg+i*4, "[%02X]", input_report_buf[i]);
		EGALAX_DBG(DBG_I2C, " Buf=%s\n", dbgmsg);
	}

	if(egalax_i2c->protocol==PROTOCOL_HIDI2C)
	{
		if(input_report_buf[0]==0x03 || input_report_buf[0]==0x04 || input_report_buf[0]==0x00)
		{
			egalax_i2c->protocol = PROTOCOL_EETI;
			egalax_i2c->input_length = 10;
			EGALAX_DBG(DBG_MODULE, " Switch protocol to %d\n", egalax_i2c->protocol);
			return 0;
		}
	}
	else
	{
		if(input_report_buf[0]==0x42 || input_report_buf[0]==0x02)
		{
			egalax_i2c->protocol = PROTOCOL_HIDI2C;
			egalax_i2c->input_length = MAX_I2C_LEN+2;
			EGALAX_DBG(DBG_MODULE, " Switch protocol to %d\n", egalax_i2c->protocol);
			return 0;
		}
	}

	if(egalax_i2c->protocol==PROTOCOL_HIDI2C)
	{
		frameLen = input_report_buf[0] + (input_report_buf[1]<<8);
		EGALAX_DBG(DBG_I2C, " I2C read data with Len=%d\n", frameLen);

		if(frameLen==0)
		{
			EGALAX_DBG(DBG_MODULE, " Device reset\n");
			return 0;
		}

		header = input_report_buf[2];
	}
	else
	{
		header = input_report_buf[0];
	}

	switch(header)
	{
		case REPORTID_MTOUCH:
			if( !egalax_i2c->skip_packet && egalax_i2c->work_state==MODE_WORKING )
				ProcessReport(input_report_buf+2, egalax_i2c);
			ret = 0;
			break;
		case REPORTID_MTOUCH_SERIAL:
			if( !egalax_i2c->skip_packet && egalax_i2c->work_state==MODE_WORKING )
				ProcessSerialReport(input_report_buf, egalax_i2c);
			ret = 0;
			break;
		case REPORTID_VENDOR:
			atomic_set(&wait_command_ack, 1);
			EGALAX_DBG(DBG_I2C, " I2C get vendor command packet\n");

			if( p_char_dev->OpenCnts>0 ) // If someone reading now! put the data into the buffer!
			{
				if(egalax_i2c->protocol==PROTOCOL_EETI)
				{
					if(iCmdReadLen==0)
					{
						memset(vendor_cmd_buf, 0, sizeof(vendor_cmd_buf));
						iTargetCmdLen = input_report_buf[3]+2;						
					}
					memcpy(vendor_cmd_buf+iCmdReadLen, input_report_buf+2, input_report_buf[1]);
					iCmdReadLen += input_report_buf[1];

					if(iCmdReadLen>=iTargetCmdLen)
					{
						pVendorBufData = vendor_cmd_buf;
						iCmdReadLen = iTargetCmdLen = 0;
					}
					else
						return ret;
				}
				else
					pVendorBufData = input_report_buf+2;

				loop=3;
				do {
					ret = wait_event_timeout(p_char_dev->fifo_inq, kfifo_avail(&p_char_dev->DataKFiFo)>=MAX_I2C_LEN, HZ);
				}while(ret<=0 && --loop);

				if(ret>0) // fifo size is ready
				{
					ret = kfifo_in_locked(&p_char_dev->DataKFiFo, pVendorBufData, MAX_I2C_LEN, &p_char_dev->FiFoLock);
					wake_up_interruptible( &p_char_dev->fifo_inq );
				}
				else
					EGALAX_DBG(DBG_MODULE, " [Warning] Can't write data because fifo size is overflow.\n");
			}
			break;
		default:
			EGALAX_DBG(DBG_MODULE, " I2C read error data with hedaer=%d\n", header);
			ret = -1;
			break;
	}

	return ret;
}

static void egalax_i2c_wq_irq(struct work_struct *work)
{
	struct _egalax_i2c *egalax_i2c = container_of(work, struct _egalax_i2c, work_irq);
	struct i2c_client *client = egalax_i2c->client;

	EGALAX_DBG(DBG_INT, " egalax_i2c_wq run\n");

	/*continue recv data*/
	while( !gpio_get_value(egalax_i2c->interrupt_gpio) )
	{
		egalax_i2c_measure(egalax_i2c);
		schedule();
	}

	if( egalax_i2c->skip_packet > 0 )
		egalax_i2c->skip_packet = 0;

	EGALAX_DBG(DBG_INT, " egalax_i2c_wq leave\n");
}

static irqreturn_t egalax_i2c_interrupt(int irq, void *dev_id)
{
	struct _egalax_i2c *egalax_i2c = (struct _egalax_i2c *)dev_id;

	EGALAX_DBG(DBG_INT, " INT with irq:%d\n", irq);

#if 1 //SKJ 20160114 : Wake up 모드 설정
  if(p_egalax_i2c_dev->work_state == MODE_SUSPEND)
  {
		input_report_key(input_dev, KEY_F1, PRESSED);
		input_sync(input_dev);

  	input_report_key(input_dev, KEY_F1, RELEASED);
  	input_sync(input_dev);
  }
#endif

	queue_work(egalax_i2c->ktouch_wq, &egalax_i2c->work_irq);

	return IRQ_HANDLED;
}

static void egalax_i2c_senduppoint(void) 
{
	int i=0;
	
	EGALAX_DBG(DBG_SUSP, " %s\n", __func__);

	for(i=0; i<MAX_SUPPORT_POINT; i++)
	{
		input_mt_slot(input_dev, pContactBuf[i].ID);
		input_mt_report_slot_state(input_dev, MT_TOOL_FINGER, 0);
	
		if(pContactBuf[i].Status)
			pContactBuf[i].Status = 0;
	}

	input_sync(input_dev);
	EGALAX_DBG(DBG_POINT, " Sent up point data done!\n");
}

static int egalax_i2c_pm_suspend(struct i2c_client *client, pm_message_t mesg)
{
	unsigned char cmdbuf[4];
	struct i2c_msg xfer;

	EGALAX_DBG(DBG_SUSP, " Enter early_suspend state:%d\n", p_egalax_i2c_dev->work_state);
	
	if(!p_egalax_i2c_dev) 
		goto fail_suspend;
#if 0   //SKJ : 20151014 for not suspend mode
	//Power sleep command
	cmdbuf[0] = 0xA7;	cmdbuf[1] = 0x00;
	cmdbuf[2] = 0x01;	cmdbuf[3] = 0x08;
	
	// Write data to device
	xfer.addr = p_egalax_i2c_dev->client->addr;
	xfer.flags = 0;
	xfer.len = sizeof(cmdbuf);
	xfer.buf = cmdbuf;

	if(i2c_transfer(p_egalax_i2c_dev->client->adapter, &xfer, 1) != 1) 
	{
		EGALAX_DBG(DBG_MODULE, " %s: i2c send Power command fail\n", __func__);
		goto fail_suspend2;
	}
#endif
	p_egalax_i2c_dev->work_state = MODE_SUSPEND;

	EGALAX_DBG(DBG_SUSP, " Early_suspend done!!\n");
	return 0;

fail_suspend2:
	p_egalax_i2c_dev->work_state = MODE_SUSPEND;
fail_suspend:
	EGALAX_DBG(DBG_MODULE, " Early_suspend failed!!\n");
	return -1;
}

static int egalax_i2c_pm_resume(struct i2c_client *client)
{
	EGALAX_DBG(DBG_SUSP, " Enter early_resume state:%d\n", p_egalax_i2c_dev->work_state);

	if(!p_egalax_i2c_dev) 
		goto fail_resume;

	if( wakeup_controller(p_egalax_i2c_dev->client->irq)==0 )
		p_egalax_i2c_dev->work_state = MODE_WORKING;
	else
		goto fail_resume2;

	egalax_i2c_senduppoint();

	EGALAX_DBG(DBG_SUSP, " Early_resume done!!\n");
	return 0;

fail_resume2:
	p_egalax_i2c_dev->work_state = MODE_WORKING;
fail_resume:
	EGALAX_DBG(DBG_MODULE, " Early_resume failed!!\n");
	return -1;
}

static void egalax_i2c_wq_cmd(struct work_struct *work)
{
	struct _egalax_i2c *egalax_i2c = container_of(work, struct _egalax_i2c, delay_work_cmd.work);

	if( !check_protocol(egalax_i2c) )
		queue_delayed_work(egalax_i2c->ktouch_wq, &egalax_i2c->delay_work_cmd, HZ/10);

	return;
}

static int egalax_i2c_probe(struct i2c_client *client, const struct i2c_device_id *idp)
{
	int ret, i;
	int gpio_reset;
	struct device *dev = &client->dev;
		
	printk("%s()\n",__func__);
	EGALAX_DBG(DBG_MODULE, " Start probe\n");

	p_egalax_i2c_dev = (struct _egalax_i2c *)kzalloc(sizeof(struct _egalax_i2c), GFP_KERNEL);
	if (!p_egalax_i2c_dev) 
	{
		EGALAX_DBG(DBG_MODULE, " Request memory failed\n");
		ret = -ENOMEM;
		goto fail1;
	}

	p_egalax_i2c_dev->protocol = PROTOCOL_EETI;
	p_egalax_i2c_dev->input_length = 10;

  //SKJ : 20151014 for Touch reset
	printk("%s(): configure gpios\n",__func__);
	gpio_reset = of_get_named_gpio(dev->of_node, "reset-gpio", 0);
	if (gpio_reset < 0) {
		printk("%s(): cannot get reset-gpios %d\n", __func__,	gpio_reset);
		goto fail3;
	}
	gpio_direction_output(gpio_reset, 0);
	gpio_request(gpio_reset, "touchreset");
	msleep(10);
	gpio_direction_output(gpio_reset, 1);

	p_egalax_i2c_dev->interrupt_gpio = of_get_named_gpio(dev->of_node, "int-gpio", 0);
	if (p_egalax_i2c_dev->interrupt_gpio < 0) {
		printk("%s(): cannot get int-gpios %d\n",__func__, p_egalax_i2c_dev->interrupt_gpio);
		p_egalax_i2c_dev->skip_packet = 1;
		goto fail2;
	}
	gpio_direction_input(p_egalax_i2c_dev->interrupt_gpio);
	p_egalax_i2c_dev->skip_packet = 0;

	input_dev = allocate_Input_Dev();
	if(input_dev==NULL)
	{
		EGALAX_DBG(DBG_MODULE, " allocate_Input_Dev failed\n");
		ret = -EINVAL; 
		goto fail2;
	}
	EGALAX_DBG(DBG_MODULE, " Register input device done\n");

	for(i=0; i<MAX_SUPPORT_POINT;i++)
	{
		pContactBuf[i].Status = -1;
		pContactBuf[i].ID = pContactBuf[i].X = pContactBuf[i].Y = 0;
	}

	p_egalax_i2c_dev->client = client;
	mutex_init(&p_egalax_i2c_dev->mutex_wq);

	p_egalax_i2c_dev->ktouch_wq = create_singlethread_workqueue("egalax_touch_wq");
	INIT_WORK(&p_egalax_i2c_dev->work_irq, egalax_i2c_wq_irq);

	INIT_DELAYED_WORK(&p_egalax_i2c_dev->delay_work_cmd, egalax_i2c_wq_cmd);
	queue_delayed_work(p_egalax_i2c_dev->ktouch_wq, &p_egalax_i2c_dev->delay_work_cmd, HZ/10);

	i2c_set_clientdata(client, p_egalax_i2c_dev);
	
	p_egalax_i2c_dev->work_state = MODE_WORKING;

	printk("%s(): devm_request_threaded_irq\n",__func__);
	ret = devm_request_threaded_irq(&client->dev, client->irq, NULL,
					  egalax_i2c_interrupt,
					  IRQF_TRIGGER_LOW | IRQF_ONESHOT,
					  "egalax_i2c", p_egalax_i2c_dev);
	if (ret < 0) {
		printk("%s(): Failed to register interrupt\n",__func__);
		goto fail3;
	}

	EGALAX_DBG(DBG_MODULE, " Request irq(%d) gpio(%d) with result:%d\n", client->irq, p_egalax_i2c_dev->interrupt_gpio, ret);
	
	EGALAX_DBG(DBG_MODULE, " I2C probe done\n");
	return 0;

fail3:
	i2c_set_clientdata(client, NULL);
	destroy_workqueue(p_egalax_i2c_dev->ktouch_wq); 
	free_irq(client->irq, p_egalax_i2c_dev);
	input_unregister_device(input_dev);
	input_dev = NULL;
fail2:
	gpio_free(p_egalax_i2c_dev->interrupt_gpio);
fail1:
	kfree(p_egalax_i2c_dev);
	p_egalax_i2c_dev = NULL;

	EGALAX_DBG(DBG_MODULE, " I2C probe failed\n");
	return ret;
}

static int egalax_i2c_remove(struct i2c_client *client)
{
	struct _egalax_i2c *egalax_i2c = i2c_get_clientdata(client);

	printk("%s()\n",__func__);
	egalax_i2c->work_state = MODE_STOP;

	cancel_delayed_work_sync(&p_egalax_i2c_dev->delay_work_cmd);

	cancel_work_sync(&egalax_i2c->work_irq);

	if(client->irq)
	{
		disable_irq(client->irq);
		free_irq(client->irq, egalax_i2c);
	}

	gpio_free(egalax_i2c->interrupt_gpio);
	
	if(egalax_i2c->ktouch_wq) 
		destroy_workqueue(egalax_i2c->ktouch_wq); 

	if(input_dev)
	{
		EGALAX_DBG(DBG_MODULE,  " Unregister input device\n");
		input_unregister_device(input_dev);
		input_dev = NULL;
	}

	i2c_set_clientdata(client, NULL);
	kfree(egalax_i2c);
	p_egalax_i2c_dev = NULL;

	EGALAX_DBG(DBG_MODULE,  " I2C remove done\n");
	
	return 0;
}

static SIMPLE_DEV_PM_OPS(egalax_i2c_pm_ops, egalax_i2c_pm_suspend, egalax_i2c_pm_resume);

static const struct i2c_device_id egalax_i2c_idtable[] = { 
	{ "egalax_i2c", 0 }, 
	{ } 
};
MODULE_DEVICE_TABLE(i2c, egalax_i2c_idtable);

static const struct of_device_id egalax_i2c_dt_ids[] = { 
	{ .compatible = "eeti,egalax_i2c" }, 
	{ } 
};
MODULE_DEVICE_TABLE(i2c, egalax_i2c_dt_ids);


static struct i2c_driver egalax_i2c_driver = {
	.probe		= egalax_i2c_probe,
	.remove		= egalax_i2c_remove,
	.id_table	= egalax_i2c_idtable,
	.driver = {
		.name 	= "egalax_i2c",
		.pm	= &egalax_i2c_pm_ops,
		.of_match_table = egalax_i2c_dt_ids,
	},
};

module_i2c_driver(egalax_i2c_driver);

MODULE_AUTHOR("EETI <touch_fae@eeti.com>");
MODULE_DESCRIPTION("egalax all points controller i2c driver");
MODULE_LICENSE("GPL");
