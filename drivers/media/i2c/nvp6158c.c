/*
 * Samsung Sensor Driver
 *
 * Copyright (c) 2018 Samsung Electronics Co., Ltd
 * Author: Sooman Jeong <sm5.jeong@samsung.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/i2c.h>
#include <linux/delay.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/vmalloc.h>
#include <linux/platform_device.h>
#include <media/v4l2-ctrls.h>
#include <media/v4l2-device.h>
#include <linux/gpio/consumer.h>
#include <linux/gpio.h>
#include "nvp6158c.h"
#include <linux/timer.h>

#define SENSOR_NAME "NVP6158C"
//#define FRAME_RATE_15
//#define CONFIG_CVBS
// Debug
static int debug = 0;
#define dprintk(msg...)	if(debug)	{printk("nvp6158c> " msg);}

struct sensor_reg {
	unsigned short reg;
	unsigned char val;
};

struct capture_size {
	unsigned long width;
	unsigned long height;
};

enum {
	INTERVAL_MIN = 0,
	INTERVAL_MAX,
	INTERVAL,
};

unsigned char __fmtdef[4] = {
	TVI_FHD_30P,
	TVI_FHD_30P,
	TVI_FHD_30P,
	TVI_FHD_30P
};

struct nx_resolution {
	uint32_t width;
	uint32_t height;
	uint32_t interval[INTERVAL];
};
#ifdef CONFIG_CVBS
static struct nx_resolution supported_resolutions[] = {
	{
		.width	= 960,
		.height = 480,
		.interval[INTERVAL_MIN] = 15,
		.interval[INTERVAL_MAX] = 30,
	}
};
#else
static struct nx_resolution supported_resolutions[] = {
	{
		.width	= 1920,
		.height = 1080,
		.interval[INTERVAL_MIN] = 15,
		.interval[INTERVAL_MAX] = 30,
	}
};
#endif

struct capture_size sensor_sizes_nvp6158c[] = {
	{  1920, 1080 },	/* FHD */
	{  1920, 1080 },	/* HD */
	{  1920, 1080 },	/* VGA */
	{  1920, 1080 },	/* QVGA */
	{  1920, 1080 }		/* QCIF */
};
#if 0
struct capture_size sensor_sizes_nvp6158c[] = {
	{  1920, 1080 },	/* FHD */
	{  1280,  720 },	/* HD */
	{   640,  480 },	/* VGA */
	{   320,  240 },	/* QVGA */
	{   176,  144 },	/* QCIF */
};
#endif
struct i2c_info {
	int i2c_id;
	int i2c_addr;
};

struct nvp6158c_state {
	struct v4l2_subdev	subdev;
	struct v4l2_mbus_framefmt fmt;
	struct media_pad	pad;	/* for media device pad */
	struct i2c_client	*client;
	struct gpio_desc *enable_gpio;	// camera power
	struct gpio_desc *reset_gpio;
	struct gpio_desc *door_gpio;	// door-camera power
	struct mutex		i2c_lock;
};
static struct timer_list my_timer;
struct i2c_client *my_client;

struct reg_value {
	u8 reg_addr;
	u8 val;
	u8 mask;
	u32 delay_ms;
};
static void default_init(struct i2c_client *client);

static inline struct nvp6158c_state *to_state(struct v4l2_subdev *subdev)
{
	struct nvp6158c_state *state =
		container_of(subdev, struct nvp6158c_state, subdev);
	return state;
}

static inline struct i2c_client *to_client(struct v4l2_subdev *subdev)
{
	return (struct i2c_client *)v4l2_get_subdevdata(subdev);
}

int sensor_i2c_write_reg(struct i2c_client *client, u8 reg, u8 val)
{
	struct i2c_msg msg;
	u8 buf[2];
	int ret;

	buf[0] = reg;
	buf[1] = val;

	msg.addr = client->addr;
	msg.flags = client->flags;
	msg.buf = buf;
	msg.len = sizeof(buf);

	ret = i2c_transfer(client->adapter, &msg, 1);
	if (ret < 0) {
		dev_err(&client->dev, "%s: error: reg=%x, val=%x\n",
			__func__, reg, val);
		return ret;
	}

	return 0;
}

int sensor_i2c_read_reg(struct i2c_client *client, u8 reg, u8 *val)
{
	struct i2c_msg msg[2];
	u8 buf[1];
	int ret;

	buf[0] = reg;

	msg[0].addr = client->addr;
	msg[0].flags = client->flags;
	msg[0].buf = buf;
	msg[0].len = sizeof(buf);

	msg[1].addr = client->addr;
	msg[1].flags = client->flags | I2C_M_RD;
	msg[1].buf = buf;
	msg[1].len = 1;

	ret = i2c_transfer(client->adapter, msg, 2);
	if (ret < 0)
		return ret;

	*val = buf[0];
	return 0;
}
/*
static int sensor_zn240_load_regs(struct v4l2_subdev *subdev,
			    const struct reg_value *regs, int size)
{
	unsigned int i;
	u32 delay_ms;
	u8 reg_addr;
	u8 val;
	int ret = 0;
	struct i2c_client *client = to_client(subdev);

	for (i = 0; i < size; ++i, ++regs) {
		delay_ms = regs->delay_ms;
		reg_addr = regs->reg_addr;
		val = regs->val;

		ret = sensor_zn240_write_reg(client, reg_addr, val);
		if (ret)
			break;

		if (delay_ms)
			usleep_range(1000*delay_ms, 1000*delay_ms+100);
	}

	return ret;
}
*/

void debug_i2c(unsigned long data)
{
	struct i2c_client *client = my_client;
	unsigned char r_data;
	dprintk("read i2c\n");
	
	sensor_i2c_write_reg(client, 0xff, 00);
	sensor_i2c_read_reg(client, 0x22, &r_data);
	printk("read reg(0x22) = 0x%02x\n", r_data);
	sensor_i2c_read_reg(client, 0x26, &r_data);
	printk("read reg(0x26) = 0x%02x\n", r_data);
	sensor_i2c_read_reg(client, 0xe8, &r_data);
	dprintk("read reg(0xe8) = 0x%02x\n", r_data);
	sensor_i2c_read_reg(client, 0xe9, &r_data);
	dprintk("read reg(0xe9) = 0x%02x\n", r_data);
	
	mod_timer(&my_timer, jiffies + msecs_to_jiffies(1000) );
}

void Bank_Dump(struct i2c_client *client, u8 bank)
{
	int i;
	unsigned char r_data;
	
	gpio_i2c_write(client, 0xff, bank);
	dprintk("Dump Bank(%d)!\n", bank);
	for(i=0; i<256; i++)
	{
		gpio_i2c_read(client, i, &r_data);
		dprintk("Reg(0x%02x), Val(0x%02x)\n", i, r_data);
	}
}

static int ir_count = 0, fr_count = 0, init_flag = 0;
static int sensor_nvp6158c_init(struct v4l2_subdev *subdev, u32 val)
{
	int ret, i, ch, port = 0;
	struct i2c_client *client = to_client(subdev);; 
	struct nvp6158c_state *state = to_state(subdev);;
	struct i2c_info *host = v4l2_get_subdev_hostdata(subdev);;
	unsigned char def_fmt = TVI_FHD_30P;
	unsigned char r_data, val_9x44;
		
	__fmtdef[0] = TVI_FHD_30P;
	__fmtdef[1] = TVI_FHD_30P;

	WARN_ON(!subdev);
	
	dprintk("%s(): start(%d)\n", __func__, val);
	//dev_info(&client->dev, "%s start(%d)\n", __func__, val);
	//mutex_lock(&state->i2c_lock);
	
	if(host->i2c_addr)
			client->addr = host->i2c_addr;
	
	gpio_i2c_write(client, 0xFF, 0x01);
	gpio_i2c_read(client, 0xCA, &r_data);
	if(init_flag == 0)  // init first time 
	{
		  init_flag = 1;
	    r_data &= 0x99;
		  gpio_i2c_write(client, 0xCA, r_data);
		  
		  default_init(client);
	}
	else if(host->i2c_addr) // IR
	{
	    dprintk("IR camera off\n");
			r_data &= 0xBB;
			gpio_i2c_write(client, 0xCA, r_data);
	}
	else  // Color
	{
	    dprintk("Color camera off\n");
			r_data &= 0xDD;
			gpio_i2c_write(client, 0xCA, r_data);
	}
	
	if(val == 0)  return ret;
/*	
	if(val == 0)	// stream off
	{
#if 1
	if(host->i2c_addr)	// IR인 경우(vdo2)
		{
			dprintk("IR camera off\n");
			client->addr = host->i2c_addr;
			gpio_i2c_write(client, 0xFF, 0x01);
			gpio_i2c_read(client, 0xCA, &r_data);
			r_data &= 0xBB;
			gpio_i2c_write(client, 0xCA, r_data);
			return ret;
		}
		else	// color (vdo1)
		{
			dprintk("Color camera off\n");
			gpio_i2c_write(client, 0xFF, 0x01);
			gpio_i2c_read(client, 0xCA, &r_data);
			r_data &= 0xDD;
			gpio_i2c_write(client, 0xCA, r_data);
			return ret;
		}
#else		
		return 0;
#endif	
	}
*/	
/*
	if (host->i2c_addr)
	{
		if (ir_count)
			return 0;
		client->addr = host->i2c_addr;
	
		ret = gpio_i2c_write(client, 0xFF, 0x01);
		if (ret)
			pr_err("[%s] IR failed to write i2c - 0xFF\n", __func__);
		ret = gpio_i2c_read(client, 0xCA, &r_data);
		if (ret)
			pr_err("[%s] IR failed to read i2c - 0xCA:0x%02x\n", __func__, r_data);
		dprintk("reg(0xca) = 0x%02x\n", r_data);
	
		if((r_data&0x44) == 0x00)		// YH: FR ir output이 off인지 체크
		{
			r_data |= 0x44;
			ret = gpio_i2c_write(client, 0xCA, r_data);
			if (ret)
				pr_err("[%s] IR failed to write i2c - 0xCA:0x%02x\n", __func__, r_data);
			//raptor3_output_set(client, 1, 2);
		}
		//ir_count++;		
		return ret;
	}
	
	if (fr_count)
		return 0;
*/
#if 0 // YH : 20180615 1time init
	//init
	video_output_colorbar_set(client);
	/* set initialization value  */
	for(ch = 0; ch < 4; ch++)
	{
		ret =gpio_i2c_write(client, 0xFF, 0x05+ch);
		ret = gpio_i2c_write(client, 0xD5, 0x80);
		ret = gpio_i2c_write(client, 0x00, 0xD0); //clamp speed
		ret = gpio_i2c_write(client, 0x76, 0x00);
	}

	/* set NOVIDEO */
	for(ch = 0; ch < 4; ch++)
	{
		ret = gpio_i2c_write(client, 0xFF, 0x09);
		ret = gpio_i2c_write(client, 0x80 + (ch * 0x20), 0x00);
		ret = gpio_i2c_write(client, 0x81 + (ch * 0x20), 0x00);

		ret = gpio_i2c_write(client, 0xFF, 0x05 + ch);
		ret = gpio_i2c_write(client, 0x2C, 0x00);
		ret = gpio_i2c_write(client, 0xB8, 0xB8);
		ret = gpio_i2c_write(client, 0xB9, 0xB2);
		ret = gpio_i2c_write(client, 0x25, 0xDC);


		ret = gpio_i2c_write(client, 0xFF, 0x09);
		ret = gpio_i2c_write(client, 0x50 + (ch*4) , 0x30);
		ret = gpio_i2c_write(client, 0x51 + (ch*4) , 0x6F);
		ret = gpio_i2c_write(client, 0x52 + (ch*4) , 0x67);
		ret = gpio_i2c_write(client, 0x53 + (ch*4) , 0x48);

		ret = gpio_i2c_read(client, 0x44, &val_9x44);
		val_9x44 &= ~(1 << ch);
		val_9x44 |= (1 << ch);
		ret = gpio_i2c_write(client, 0x44 , val_9x44);
	}
	ret = gpio_i2c_write(client, 0xff, 0x01);
	/* set Port setting */
	for(port = 1; port < 3; port++)
	{
		/* port channel sequence set */
		if(port == 1)
		{
			ret = gpio_i2c_write(client, 0xc0 + (port * 2), 0x10);
			ret = gpio_i2c_write(client, 0xc1 + (port * 2), 0x10);
		}
		else if(port == 2)
		{
			ret = gpio_i2c_write(client, 0xc0 + (port * 2), 0x32);
			ret = gpio_i2c_write(client, 0xc1 + (port * 2), 0x32);
		}
	}
	/* port 1mux set */
	ret = gpio_i2c_write(client, 0xc8, 0x00);	//YH : 20 -> 00
	ret = gpio_i2c_write(client, 0xc9, 0x00);	//YH : 02 -> 00

	/* all port enable */
	// YH : 20180615 Test output port enable at last
	//ret = gpio_i2c_write(client, 0xca, 0x66); 
	/*
	gpio_i2c_read(client, 0xca, &r_data);
	dprintk("reg(0xca) = 0x%02x\n", r_data);
	if (host->i2c_addr){	
		r_data |= 0x44;
		gpio_i2c_write(client, 0xca, r_data);
	}
	else{
		r_data |= 0x22;
		gpio_i2c_write(client, 0xca, r_data);
	}
	*/

	/* mux chid set */
	ret = gpio_i2c_write(client, 0xff, 0x00);
	ret = gpio_i2c_write(client, 0x55, 0x10);
	ret = gpio_i2c_write(client, 0x56, 0x10);

	 // for image enhancement 3M RT upper format when cable distance 300M over
	for(ch = 0; ch < 4; ch++)
	{
		 ret = gpio_i2c_write(client, 0xff, 0x05 + ch );
		 ret = gpio_i2c_write(client, 0x50, 0xc6 );

		 ret = gpio_i2c_write(client, 0xff, 0x0a + (ch / 2));

		 gpio_i2c_write(client, 0x00 + ( 0x80 * (ch % 2)), 0x80 );
		 gpio_i2c_write(client, 0x01 + ( 0x80 * (ch % 2)), 0x02 );
		 gpio_i2c_write(client, 0x02 + ( 0x80 * (ch % 2)), 0x04 );
		 gpio_i2c_write(client, 0x03 + ( 0x80 * (ch % 2)), 0x80 );
		 gpio_i2c_write(client, 0x04 + ( 0x80 * (ch % 2)), 0x06 );
		 gpio_i2c_write(client, 0x05 + ( 0x80 * (ch % 2)), 0x07 );
		 gpio_i2c_write(client, 0x06 + ( 0x80 * (ch % 2)), 0x80 );
		 gpio_i2c_write(client, 0x07 + ( 0x80 * (ch % 2)), 0x07 );
		 gpio_i2c_write(client, 0x08 + ( 0x80 * (ch % 2)), 0x03 );
		 gpio_i2c_write(client, 0x09 + ( 0x80 * (ch % 2)), 0x08 );
		 gpio_i2c_write(client, 0x0a + ( 0x80 * (ch % 2)), 0x04 );
		 gpio_i2c_write(client, 0x0b + ( 0x80 * (ch % 2)), 0x10 );
		 gpio_i2c_write(client, 0x0c + ( 0x80 * (ch % 2)), 0x08 );
		 gpio_i2c_write(client, 0x0d + ( 0x80 * (ch % 2)), 0x1f );
		 gpio_i2c_write(client, 0x0e + ( 0x80 * (ch % 2)), 0x2e );
		 gpio_i2c_write(client, 0x0f + ( 0x80 * (ch % 2)), 0x08 );
		 gpio_i2c_write(client, 0x10 + ( 0x80 * (ch % 2)), 0x38 );
		 gpio_i2c_write(client, 0x11 + ( 0x80 * (ch % 2)), 0x35 );
		 gpio_i2c_write(client, 0x12 + ( 0x80 * (ch % 2)), 0x00 );
		 gpio_i2c_write(client, 0x13 + ( 0x80 * (ch % 2)), 0x20 );
		 gpio_i2c_write(client, 0x14 + ( 0x80 * (ch % 2)), 0x0d );
		 gpio_i2c_write(client, 0x15 + ( 0x80 * (ch % 2)), 0x80 );
		 gpio_i2c_write(client, 0x16 + ( 0x80 * (ch % 2)), 0x54 );
		 gpio_i2c_write(client, 0x17 + ( 0x80 * (ch % 2)), 0xb1 );
		 gpio_i2c_write(client, 0x18 + ( 0x80 * (ch % 2)), 0x91 );
		 gpio_i2c_write(client, 0x19 + ( 0x80 * (ch % 2)), 0x1c );
		 gpio_i2c_write(client, 0x1a + ( 0x80 * (ch % 2)), 0x87 );
		 gpio_i2c_write(client, 0x1b + ( 0x80 * (ch % 2)), 0x92 );
		 gpio_i2c_write(client, 0x1c + ( 0x80 * (ch % 2)), 0xe2 );
		 gpio_i2c_write(client, 0x1d + ( 0x80 * (ch % 2)), 0x20 );
		 gpio_i2c_write(client, 0x1e + ( 0x80 * (ch % 2)), 0xd0 );
		 ret = gpio_i2c_write(client, 0x1f + ( 0x80 * (ch % 2)), 0xcc );
	 }
	// common_setting
	raptor3_def_set(client);
	
	for(i=0; i<2; i++)
	{
		// video format setting
		raptor3_on_video_set(client, i, def_fmt);
		// video output port setting
		if(i==0)
			raptor3_output_set(client, i, 1);	//vin1 -- vdo2->vdo1 (color)
		else
			raptor3_output_set(client, i, 2);	//vin2 -- vdo1->vdo2 (IR)
	}
	msleep(200);	// YH : wait for stable mode
#endif
	
	msleep(500);
	gpio_i2c_write(client, 0xFF, 0x01);
	gpio_i2c_read(client, 0xca, &r_data);
	dprintk("reg(0xca) = 0x%02x\n", r_data);
	if (host->i2c_addr){	
		r_data |= 0x44;
		gpio_i2c_write(client, 0xca, r_data);
		dprintk("IR camera on\n");
	}
	else{
		r_data |= 0x22;
		gpio_i2c_write(client, 0xca, r_data);
		dprintk("Color camera on\n");
	}

	/*
	//Test-ColorPattern
	gpio_i2c_write(client, 0xff, 0x05);
	gpio_i2c_write(client, 0x2c, 0x08);
	gpio_i2c_write(client, 0xff, 0x06);
	gpio_i2c_write(client, 0x2c, 0x08);
	gpio_i2c_write(client, 0xff, 0x07);
	gpio_i2c_write(client, 0x2c, 0x08);
	gpio_i2c_write(client, 0xff, 0x08);
	gpio_i2c_write(client, 0x2c, 0x08);
	gpio_i2c_write(client, 0xff, 0x00);
	gpio_i2c_write(client, 0x78, 0xaa);
	gpio_i2c_write(client, 0x79, 0xaa);
	
	msleep(5000);
	sensor_i2c_write_reg(client, 0xff, 00);
	sensor_i2c_read_reg(client, 0x22, &r_data);
	printk("read reg(0x22) = 0x%02x\n", r_data);
	sensor_i2c_read_reg(client, 0x26, &r_data);
	printk("read reg(0x26) = 0x%02x\n", r_data);
	sensor_i2c_read_reg(client, 0xe8, &r_data);
	printk("read reg(0xe8) = 0x%02x\n", r_data);
	sensor_i2c_read_reg(client, 0xe9, &r_data);
	printk("read reg(0xe9) = 0x%02x\n", r_data);
	msleep(5000);
	sensor_i2c_write_reg(client, 0xff, 00);
	sensor_i2c_read_reg(client, 0x22, &r_data);
	printk("read reg(0x22) = 0x%02x\n", r_data);
	sensor_i2c_read_reg(client, 0x26, &r_data);
	printk("read reg(0x26) = 0x%02x\n", r_data);
	sensor_i2c_read_reg(client, 0xe8, &r_data);
	printk("read reg(0xe8) = 0x%02x\n", r_data);
	sensor_i2c_read_reg(client, 0xe9, &r_data);
	printk("read reg(0xe9) = 0x%02x\n", r_data);
	*/
	/*
	my_client = client;
	setup_timer(&my_timer, debug_i2c, 0);
	ret = mod_timer(&my_timer, jiffies + msecs_to_jiffies(1000) );
	*/
	/*
	//All Bank
	for(ch=0; ch<9; ch++) 
	{
		gpio_i2c_write(client, 0xff, ch);
		dprintk("Dump Bank(%d)!\n", ch);
		for(i=0; i<256; i++)
		{
			gpio_i2c_read(client, i, &r_data);
			dprintk("Reg(0x%02x), Val(0x%02x)\n", i, r_data);
		}
	}
	*/
	/*
	Bank_Dump(client, 0);
	Bank_Dump(client, 1);
	Bank_Dump(client, 5);
	Bank_Dump(client, 9);
	Bank_Dump(client, 11);
	Bank_Dump(client, 13);
	*/
//quit:
	//mutex_unlock(&state->i2c_lock);
	//fr_count++;
	return ret;
}

static void default_init(struct i2c_client *client)
{
	int ret, i, ch, port = 0;
	unsigned char def_fmt = TVI_FHD_30P;
	unsigned char r_data, val_9x44;
		
	__fmtdef[0] = TVI_FHD_30P;
	__fmtdef[1] = TVI_FHD_30P;
	
	dprintk("%s()\n", __func__);
	
	//init
	video_output_colorbar_set(client);
	/* set initialization value  */
	for(ch = 0; ch < 4; ch++)
	{
		ret =gpio_i2c_write(client, 0xFF, 0x05+ch);
		ret = gpio_i2c_write(client, 0xD5, 0x80);
		ret = gpio_i2c_write(client, 0x00, 0xD0); //clamp speed
		ret = gpio_i2c_write(client, 0x76, 0x00);
	}

	/* set NOVIDEO */
	for(ch = 0; ch < 4; ch++)
	{
		ret = gpio_i2c_write(client, 0xFF, 0x09);
		ret = gpio_i2c_write(client, 0x80 + (ch * 0x20), 0x00);
		ret = gpio_i2c_write(client, 0x81 + (ch * 0x20), 0x00);

		ret = gpio_i2c_write(client, 0xFF, 0x05 + ch);
		ret = gpio_i2c_write(client, 0x2C, 0x00);
		ret = gpio_i2c_write(client, 0xB8, 0xB8);
		ret = gpio_i2c_write(client, 0xB9, 0xB2);
		ret = gpio_i2c_write(client, 0x25, 0xDC);


		ret = gpio_i2c_write(client, 0xFF, 0x09);
		ret = gpio_i2c_write(client, 0x50 + (ch*4) , 0x30);
		ret = gpio_i2c_write(client, 0x51 + (ch*4) , 0x6F);
		ret = gpio_i2c_write(client, 0x52 + (ch*4) , 0x67);
		ret = gpio_i2c_write(client, 0x53 + (ch*4) , 0x48);

		ret = gpio_i2c_read(client, 0x44, &val_9x44);
		val_9x44 &= ~(1 << ch);
		val_9x44 |= (1 << ch);
		ret = gpio_i2c_write(client, 0x44 , val_9x44);
	}
	ret = gpio_i2c_write(client, 0xff, 0x01);
	/* set Port setting */
	for(port = 1; port < 3; port++)
	{
		/* port channel sequence set */
		if(port == 1)
		{
			ret = gpio_i2c_write(client, 0xc0 + (port * 2), 0x10);
			ret = gpio_i2c_write(client, 0xc1 + (port * 2), 0x10);
		}
		else if(port == 2)
		{
			ret = gpio_i2c_write(client, 0xc0 + (port * 2), 0x32);
			ret = gpio_i2c_write(client, 0xc1 + (port * 2), 0x32);
		}
	}
	/* port 1mux set */
	ret = gpio_i2c_write(client, 0xc8, 0x00);	//YH : 20 -> 00
	ret = gpio_i2c_write(client, 0xc9, 0x00);	//YH : 02 -> 00

	/* all port enable */
	// YH : 20180615 Test output port enable at last
	//ret = gpio_i2c_write(client, 0xca, 0x66); 
	/*
	gpio_i2c_read(client, 0xca, &r_data);
	dprintk("reg(0xca) = 0x%02x\n", r_data);
	if (host->i2c_addr){	
		r_data |= 0x44;
		gpio_i2c_write(client, 0xca, r_data);
	}
	else{
		r_data |= 0x22;
		gpio_i2c_write(client, 0xca, r_data);
	}
	*/

	/* mux chid set */
	ret = gpio_i2c_write(client, 0xff, 0x00);
	ret = gpio_i2c_write(client, 0x55, 0x10);
	ret = gpio_i2c_write(client, 0x56, 0x10);

	 // for image enhancement 3M RT upper format when cable distance 300M over
	for(ch = 0; ch < 4; ch++)
	{
		 ret = gpio_i2c_write(client, 0xff, 0x05 + ch );
		 ret = gpio_i2c_write(client, 0x50, 0xc6 );

		 ret = gpio_i2c_write(client, 0xff, 0x0a + (ch / 2));

		 gpio_i2c_write(client, 0x00 + ( 0x80 * (ch % 2)), 0x80 );
		 gpio_i2c_write(client, 0x01 + ( 0x80 * (ch % 2)), 0x02 );
		 gpio_i2c_write(client, 0x02 + ( 0x80 * (ch % 2)), 0x04 );
		 gpio_i2c_write(client, 0x03 + ( 0x80 * (ch % 2)), 0x80 );
		 gpio_i2c_write(client, 0x04 + ( 0x80 * (ch % 2)), 0x06 );
		 gpio_i2c_write(client, 0x05 + ( 0x80 * (ch % 2)), 0x07 );
		 gpio_i2c_write(client, 0x06 + ( 0x80 * (ch % 2)), 0x80 );
		 gpio_i2c_write(client, 0x07 + ( 0x80 * (ch % 2)), 0x07 );
		 gpio_i2c_write(client, 0x08 + ( 0x80 * (ch % 2)), 0x03 );
		 gpio_i2c_write(client, 0x09 + ( 0x80 * (ch % 2)), 0x08 );
		 gpio_i2c_write(client, 0x0a + ( 0x80 * (ch % 2)), 0x04 );
		 gpio_i2c_write(client, 0x0b + ( 0x80 * (ch % 2)), 0x10 );
		 gpio_i2c_write(client, 0x0c + ( 0x80 * (ch % 2)), 0x08 );
		 gpio_i2c_write(client, 0x0d + ( 0x80 * (ch % 2)), 0x1f );
		 gpio_i2c_write(client, 0x0e + ( 0x80 * (ch % 2)), 0x2e );
		 gpio_i2c_write(client, 0x0f + ( 0x80 * (ch % 2)), 0x08 );
		 gpio_i2c_write(client, 0x10 + ( 0x80 * (ch % 2)), 0x38 );
		 gpio_i2c_write(client, 0x11 + ( 0x80 * (ch % 2)), 0x35 );
		 gpio_i2c_write(client, 0x12 + ( 0x80 * (ch % 2)), 0x00 );
		 gpio_i2c_write(client, 0x13 + ( 0x80 * (ch % 2)), 0x20 );
		 gpio_i2c_write(client, 0x14 + ( 0x80 * (ch % 2)), 0x0d );
		 gpio_i2c_write(client, 0x15 + ( 0x80 * (ch % 2)), 0x80 );
		 gpio_i2c_write(client, 0x16 + ( 0x80 * (ch % 2)), 0x54 );
		 gpio_i2c_write(client, 0x17 + ( 0x80 * (ch % 2)), 0xb1 );
		 gpio_i2c_write(client, 0x18 + ( 0x80 * (ch % 2)), 0x91 );
		 gpio_i2c_write(client, 0x19 + ( 0x80 * (ch % 2)), 0x1c );
		 gpio_i2c_write(client, 0x1a + ( 0x80 * (ch % 2)), 0x87 );
		 gpio_i2c_write(client, 0x1b + ( 0x80 * (ch % 2)), 0x92 );
		 gpio_i2c_write(client, 0x1c + ( 0x80 * (ch % 2)), 0xe2 );
		 gpio_i2c_write(client, 0x1d + ( 0x80 * (ch % 2)), 0x20 );
		 gpio_i2c_write(client, 0x1e + ( 0x80 * (ch % 2)), 0xd0 );
		 ret = gpio_i2c_write(client, 0x1f + ( 0x80 * (ch % 2)), 0xcc );
	 }
	// common_setting
	raptor3_def_set(client);

	for(i=0; i<2; i++)
	{
		// video format setting
		raptor3_on_video_set(client, i, def_fmt);
		// video output port setting
		if(i==0)
			raptor3_output_set(client, i, 1);	//vin1 -- vdo2->vdo1 (color)
		else
			raptor3_output_set(client, i, 2);	//vin2 -- vdo1->vdo2 (IR)
	}
}

void raptor3_def_set(struct i2c_client *client)
{
	int i;
	video_input_auto_detect vin_auto_det;

	for(i=0; i<4 ; i++)
	{
		memset(&vin_auto_det, 0x00, sizeof(video_input_auto_detect));
		vin_auto_det.ch = i;
		video_input_auto_detect_set(client, &vin_auto_det);
	}
}

void video_input_auto_detect_set(struct i2c_client *client, video_input_auto_detect *vin_auto_det)
{
	unsigned char val_0x30;
	unsigned char val_0x31;
	unsigned char val_0x32;

	vin_auto_det->vafe.powerdown 		= 0x00;
	vin_auto_det->vafe.gain		 		= 0x01;
	vin_auto_det->vafe.spd		 		= 0x0d;
	vin_auto_det->vafe.ctrlreg 	 		= 0x01;
	vin_auto_det->vafe.ctrlibs	 		= 0x02;
	vin_auto_det->vafe.adcspd	 		= 0x00;
	vin_auto_det->vafe.clplevel  		= 0x02;
	vin_auto_det->vafe.eq_band	 		= 0x00;
	vin_auto_det->vafe.lpf_front_band 	= 0x07;
	vin_auto_det->vafe.clpmode   		= 0x00;
	vin_auto_det->vafe.f_lpf_bypass 	= 0x01;
	vin_auto_det->vafe.clproff 			= 0x00;
	vin_auto_det->vafe.b_lpf_bypass 	= 0x00;
	vin_auto_det->vafe.duty				= 0x04;
	vin_auto_det->vafe.ref_vol			= 0x03;
	vin_auto_det->vafe.lpf_back_band	= 0x07;
	vin_auto_det->vafe.clk_sel			= 0x01;
	vin_auto_det->vafe.eq_gainsel		= 0x07;

	vin_auto_det->d_cmp					= 0x3f;
	vin_auto_det->slice_level			= 0x5a;
	vin_auto_det->stable_mode_1			= 0x04;
	//vin_auto_det->stable_mode_2			= 0x04;
	vin_auto_det->stable_mode_2			= 0x00;
	vin_auto_det->novid_det				= 0x43;


	_video_input_auto_detect_vafe_set(client, vin_auto_det);

	gpio_i2c_write(client, 0xFF, 0x05 + vin_auto_det->ch);

	//B5/6/7/8 0x03 Digital Clamp
	gpio_i2c_write(client, 0x03, vin_auto_det->d_cmp);
	//B5/6/7/8 0x08 Slice Level
	gpio_i2c_write(client, 0x08, vin_auto_det->slice_level);
	//B5/6/7/8 0xB9 HAFC_LPF_SEL[7:6] GAIN1[5:4] GAIN2[3:0]
	gpio_i2c_write(client, 0xB9, 0x72);

	//B5/6/7/8 0xCA ADV_V_DELAY_AD[4] ADV_V_DELAY_ON[0]
	gpio_i2c_write(client, 0xCA, 0x10);

	//B13 0x30 AUTO_FMT_SET_EN_2[3:0], AUTO_FMT_SET_EN    [3:0]
	//B13 0x31 AUTO_FMT_SET_EN_4[3:0], AUTO_FMT_SET_EN_3  [3:0]
	//B13 0x32 [	  RESERVED  	], NOVIDEO_VFC_INIT_EN[3:0]

	gpio_i2c_write(client, 0xFF, 0x13);
	gpio_i2c_read(client, 0x30, &val_0x30);
	gpio_i2c_read(client, 0x31, &val_0x31);
	gpio_i2c_read(client, 0x32, &val_0x32);
	val_0x30 |= ((1 << (vin_auto_det->ch + 4)) | (1 << vin_auto_det->ch));
	val_0x31 |= ((1 << (vin_auto_det->ch + 4)) | (1 << vin_auto_det->ch));
	val_0x32 |= ((1 << vin_auto_det->ch) & 0xF);
	gpio_i2c_write(client, 0x30, val_0x30);
	gpio_i2c_write(client, 0x31, val_0x31);
	gpio_i2c_write(client, 0x32, val_0x32);
	gpio_i2c_write(client, 0x36, 0x0A);
	gpio_i2c_write(client, 0x37, 0x82);

	gpio_i2c_write(client, 0xFF, 0x00);
	gpio_i2c_write(client, 0x81+vin_auto_det->ch, 0x0A);
	gpio_i2c_write(client, 0x85+vin_auto_det->ch, 0x02);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//B13
	gpio_i2c_write(client, 0xFF, 0x13);
	//B13 0x00  Stable Mode set
	gpio_i2c_write(client, 0x00, vin_auto_det->stable_mode_1);
	//B13 0x01  Stable Mode Set
	gpio_i2c_write(client, 0x01, ((vin_auto_det->stable_mode_2) & 0x3));
	//B13 0x40 VFC_EQ_BAND_SEL[7:4] VFC_LPF_F_SEL[1:0]
	gpio_i2c_write(client, 0x40, 0x07);
	//B13 0x41 VFC_REF_VTG
	gpio_i2c_write(client, 0x41, 0x01);
	//B13 0x42 VFC_D_CMP_SET
	gpio_i2c_write(client, 0x42, 0x3F);
	//B13 0x43 VFC_SLICE_VALUE
	gpio_i2c_write(client, 0x43, 0x5A);
	//B13 0x44 VFC_SLICE_MD2
	gpio_i2c_write(client, 0x44, 0x30);
	//B13 0x45 VFC_CONTROL_MODES
	gpio_i2c_write(client, 0x45, 0xEE);
	//B13 0x46 VFC_GDF_FIX_COEFF
	gpio_i2c_write(client, 0x46, 0xC6);
	//B13 0x47 VFC_DFE_REF_SEL_OLD[4] VFC_DFE_REF_SEL_NEW[0]
	gpio_i2c_write(client, 0x47, 0x00);
	//B13 0x48 VFC_D_BLK_CNT_NEW[[7:4] VFC_HAFC_BYPASS_NEW[1] VFC_UPDN_SEL[0]
	gpio_i2c_write(client, 0x48, 0x80);
	//B13 0x49 VFC_OLD_WPD_ON[4] VFC_NEW_WPD_ON[0]
	gpio_i2c_write(client, 0x49, 0x00);
	//B13 0x4A VFC_D_CMP_FZ_OLD[4] VFC_D_CMP_FZ_NEW[1]
	gpio_i2c_write(client, 0x4A, 0x11);
	//B13 0x4B VFC_AUTO_GNOS_MODE
	gpio_i2c_write(client, 0x4B, 0x7F);
	//B13 0x4C VFC_AUTO_SYNC_MODE
	gpio_i2c_write(client, 0x4C, 0x00);
	//B13 0x4D VFC_HAFC_BYPASS[7] ??? [6:0]
	gpio_i2c_write(client, 0x4D, 0xB9);
	//B13 0x4E VFC_VAFE_B_LPF_SEL[6:4] VFC_VAFE_CKSEL[3] VFC_VAFE_EQ_GAIN_SEL[2:0]
	gpio_i2c_write(client, 0x4E, 0x78);
	//B13 0x4F VFC_VAFE_CTRL_RES[7:6] VFC_VAFE_IBS_CTRL[5:4] VFC_VAFE_SPD[2] VFC_VAFE_CLP_LEVEL[1:0]
	gpio_i2c_write(client, 0x4F, 0x62);

	//B0  0x23/0x27/0x2B/0x2F No Video Detect
	gpio_i2c_write(client, 0xFF, 0x0);
	gpio_i2c_write(client, 0x23 + ((vin_auto_det->ch) * 4), vin_auto_det->novid_det);

	/* clock set */
	gpio_i2c_write(client, 0xFF, 0x1);
    //gpio_i2c_write(client, 0x84 + vin_auto_det->ch, 0x04);
	gpio_i2c_write(client, 0x84 + vin_auto_det->ch, 0x00);
    gpio_i2c_write(client, 0x8c + vin_auto_det->ch, 0x55);

//	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0xFF, 0xa + (vin_auto_det->ch / 2));
//	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x74 + ((vin_auto_det->ch) * 0x80), 0x02); // y_slope_input_sel
//	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0x75 + ((vin_auto_det->ch % 2) * 0x80), 0x03); // frame starting point 3
//
//	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0xFF, 0x05 + vin_auto_det->ch);
//	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0xc0, 0x16);	// get slope data start v count
//	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0xc1, 0x05);	// get slope data width v count
//															// Check video signal 6 line
//	gpio_i2c_write(raptor3_i2c_addr[vin_auto_det->devnum], 0xc8, 0x04);	// get slope avg 1 frame
}

void _video_input_auto_detect_vafe_set(struct i2c_client *client, video_input_auto_detect *vin_auto_det)
{
	unsigned char val_1x7A;
	unsigned char val_5678x00;
	unsigned char val_5678x01;
	unsigned char val_5678x58;
	unsigned char val_5678x59;
	unsigned char val_5678x5B;
	unsigned char val_5678x5C;

	gpio_i2c_write(client, 0xFF, 0x01);
	gpio_i2c_read(client, 0x7A, &val_1x7A);
	val_1x7A |= (1 << vin_auto_det->ch);
	gpio_i2c_write(client, 0x7A, val_1x7A);

	gpio_i2c_write(client, 0xFF, 0x00);
	//B0 0x00/1/2/3 gain[4], powerdown[0]
	gpio_i2c_write(client, 0x00 + vin_auto_det->ch, ((vin_auto_det->vafe.gain & 0x01) << 4) |
												  (vin_auto_det->vafe.powerdown & 0x01));

	gpio_i2c_write(client, 0xFF, 0x01);
	gpio_i2c_write(client, 0x84 + vin_auto_det->ch, 0x00);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	//B5/6/7/8
	gpio_i2c_write(client, 0xFF, 0x05 + vin_auto_det->ch);

	//B5/6/7/8 0x01 spd[2], lpf_back_band[1:0]
	gpio_i2c_read(client, 0x00, &val_5678x00);
	val_5678x00 &= ~(0xF << 4);
	val_5678x00 |= vin_auto_det->vafe.spd << 4;

	gpio_i2c_write(client, 0x00, val_5678x00);

	val_5678x01 = ((vin_auto_det->vafe.ctrlreg << 6) | (vin_auto_det->vafe.ctrlibs << 4) | (vin_auto_det->vafe.adcspd << 2) | (vin_auto_det->vafe.clplevel));
	gpio_i2c_write(client, 0x01, val_5678x01 );

	//B5/6/7/8 0x58 eq_band[7:4], lpf_front_band[1:0]
	val_5678x58 = ((vin_auto_det->vafe.eq_band << 4) | (vin_auto_det->vafe.lpf_front_band));
	gpio_i2c_write(client, 0x58, val_5678x58);

	//B5/6/7/8 0x5B ref_vol[1:0]
	val_5678x59 = ((vin_auto_det->vafe.clpmode << 7) | (vin_auto_det->vafe.f_lpf_bypass << 4) | (vin_auto_det->vafe.clproff << 3) | (vin_auto_det->vafe.b_lpf_bypass));
	gpio_i2c_write(client, 0x59, val_5678x59);

	val_5678x5B = ((vin_auto_det->vafe.duty << 4) | (vin_auto_det->vafe.ref_vol));
	gpio_i2c_write(client, 0x5B, val_5678x5B);

	val_5678x5C = ((vin_auto_det->vafe.lpf_back_band << 4) | (vin_auto_det->vafe.clk_sel << 3) | (vin_auto_det->vafe.eq_gainsel));
	gpio_i2c_write(client, 0x5C, val_5678x5C);
}

void raptor3_on_video_set(struct i2c_client *client, int ch, unsigned char fmt)
{
	decoder_dev_ch_info_s DEV_CH_INFO;
	video_equalizer_info_s sEQInfo;

	DEV_CH_INFO.ch = ch;
	DEV_CH_INFO.devnum = 0;
	DEV_CH_INFO.fmt_def = fmt;

	//ioctl(fd, IOC_VDEC_AUTO_ONVIDEO_SET, &DEV_CH_INFO);
	video_input_onvideo_set(client, &DEV_CH_INFO);
	//ioctl(fd, IOC_VDEC_INPUT_H_TIMING_SET, &DEV_CH_INFO);
	video_input_h_timing_set(client, &DEV_CH_INFO);
	//ioctl(fd, IOC_VDEC_INPUT_COLOR_SET, &DEV_CH_INFO);
	video_input_color_set(client, &DEV_CH_INFO);
	//ioctl(fd, IOC_VDEC_INPUT_AFE_INIT, &DEV_CH_INFO);
	video_input_vafe_init(client, &DEV_CH_INFO);
	//ioctl(fd, IOC_VDEC_NEW_FORMAT_SET, &DEV_CH_INFO);
	video_input_new_format_set(client, &DEV_CH_INFO);

	sEQInfo.Ch = ch;
    sEQInfo.devnum = 0;
	if(fmt == TVI_FHD_30P)
		sEQInfo.distance = 2; // YH: stage0 -> 2
	else
		sEQInfo.distance = 0; // YH: stage0 -> 2
		
    sEQInfo.FmtDef = fmt;

	//ioctl(fd, IOC_VDEC_MANUAL_EQ_DIST_SET, &sEQInfo);
	video_input_eq_val_set(client, &sEQInfo);
}

void raptor3_output_set(struct i2c_client *client, int input_ch, int out_port)
{
	video_output_sequence VOutSeq;
	video_output_data_out_mode DataOutMode;
	dprintk("%s()\n", __func__);

	VOutSeq.port = out_port;
	VOutSeq.fmt = __fmtdef[input_ch];
	VOutSeq.ch01 = ((input_ch & 0x0f) | ((input_ch & 0xf)<<4)); // [7:4] Sequence2 or 4, [3:0] Sequence1 or 3
	VOutSeq.ch23 = ((input_ch & 0x0f) | ((input_ch & 0xf)<<4)); // [7:4] Sequence2 or 4, [3:0] Sequence1 or 3

	//ioctl(fd, IOC_VDEC_OUTPUT_CHANNEL_SEQUENCE_SET, &VOutSeq);
	video_output_channel_sequence_set(client, &VOutSeq);

	DataOutMode.ch = input_ch;
    DataOutMode.devnum = 0;
    DataOutMode.set_val = 0x01;

	//ioctl(fd, IOC_VDEC_AUTO_DATA_OUT_MODE_SET, &DataOutMode);
	video_output_data_out_mode_set(client, &DataOutMode);
}

unsigned char s_only_onetime_run[32] = {0, };

void video_input_onvideo_set(struct i2c_client *client, decoder_dev_ch_info_s *decoder_info)
{
	unsigned char format_3M_RT;

	dprintk("onvideo_set dev_num[%x] ch_num[%x] fmt_def[%d]", decoder_info->devnum, decoder_info->ch, decoder_info->fmt_def);


	/* after 09/12 */
	format_3M_RT = __IsOver3MRTVideoFormat(decoder_info);

	if(format_3M_RT)
	{
		/* DECI_FILTER_ON */
		gpio_i2c_write(client, 0xFF, 0x05 + decoder_info->ch);
		gpio_i2c_write(client, 0x50, 0x76);
	}
	else
	{
		/* DECI_FILTER_OFF */
		gpio_i2c_write(client, 0xFF, 0x05 + decoder_info->ch);
		gpio_i2c_write(client, 0x50, 0xc6);
	}


	if(	decoder_info->fmt_def == CVI_HD_30P 		||
		decoder_info->fmt_def == CVI_HD_30P_EX		||
		decoder_info->fmt_def == AHD20_720P_30P		||
		decoder_info->fmt_def == AHD20_720P_30P_EX	||
		decoder_info->fmt_def == AHD20_720P_30P_EX_Btype)
	{
		//meant to remove pre-connection issue. 07.31
		if( s_only_onetime_run[decoder_info->ch * decoder_info->devnum] == 0)
		{
			video_input_vafe_reset(client, decoder_info);
			s_only_onetime_run[decoder_info->ch * decoder_info->devnum] = 1;
		}
	}
	else
	{
		if( s_only_onetime_run[decoder_info->ch * decoder_info->devnum] == 0)
		{
			s_only_onetime_run[decoder_info->ch * decoder_info->devnum] = 1;
		}
	}

}

unsigned char __IsOver3MRTVideoFormat( const char *poFmtName )
{
	unsigned char ret = 1; //

	if((strcmp(poFmtName, "AHD30_3M_30P") == 0) ||
	   (strcmp(poFmtName, "AHD30_3M_25P") == 0) ||
	   (strcmp(poFmtName, "AHD30_4M_30P") == 0) ||
	   (strcmp(poFmtName, "AHD30_4M_25P") == 0) ||
	   (strcmp(poFmtName, "AHD30_5M_20P") == 0) ||
	   (strcmp(poFmtName, "AHD30_5_3M_20P") == 0) ||
	   (strcmp(poFmtName, "AHD30_6M_18P") == 0) ||
	   (strcmp(poFmtName, "AHD30_6M_20P") == 0) ||
	   (strcmp(poFmtName, "AHD30_8M_12_5P") == 0) ||
	   (strcmp(poFmtName, "AHD30_8M_15P") == 0) ||
	   (strcmp(poFmtName, "TVI_4M_30P") == 0) ||
	   (strcmp(poFmtName, "TVI_4M_25P") == 0) ||
	   (strcmp(poFmtName, "TVI_5M_20P") == 0) ||
	   (strcmp(poFmtName, "CVI_4M_25P") == 0) ||
	   (strcmp(poFmtName, "CVI_4M_30P") == 0) ||
	   (strcmp(poFmtName, "CVI_8M_15P") == 0) ||
	   (strcmp(poFmtName, "CVI_8M_12_5P") == 0))
	{
		ret = 0;
	}
	return ret; // 0:Over 3M RT, 1:other formation
}

void video_input_vafe_reset(struct i2c_client *client, decoder_dev_ch_info_s *decoder_info)
{
	unsigned char val_0x00;
	gpio_i2c_write(client, 0xFF, 0x00);
	gpio_i2c_read(client, 0x00 + decoder_info->ch, &val_0x00);
	_SET_BIT(val_0x00, 0);
	gpio_i2c_write(client, 0x00 + decoder_info->ch, val_0x00);
	msleep(10);
	_CLE_BIT(val_0x00, 0);
	gpio_i2c_write(client, 0x00 + decoder_info->ch, val_0x00);
	dprintk("[DRV] AFE CH:[%d] Reset done\n", decoder_info->ch);
}

void video_input_h_timing_set(struct i2c_client *client, decoder_dev_ch_info_s *pDevChInfo)
{
	unsigned char val_0x54;
	dprintk("%s()\n", __func__);

	video_input_basic_timing_init_s h_timing = (video_input_basic_timing_init_s)decoder_basic_timing_fmtdef[ pDevChInfo->fmt_def ];

	if(pDevChInfo->ch>3)
	{
		dprintk("[DRV] %s CHID Error\n", __func__);
		return;
	}


	//B0
	gpio_i2c_write(client, 0xFF, 0x00);
	//H_DELAY_LSB B0 0x58/9/a/b
	gpio_i2c_write(client, 0x58 + pDevChInfo->ch, h_timing.h_delay_lsb);
	//H_MASK_OB B0 0x89/a/b/c
	gpio_i2c_write(client, 0x89 + pDevChInfo->ch, h_timing.h_mask_on);
	//H_MASK_SEL B0 0x8E/F/90/91
	gpio_i2c_write(client, 0x8e + pDevChInfo->ch, h_timing.h_mask_sel);

	gpio_i2c_write(client, 0xA0 + pDevChInfo->ch, h_timing.v_blk_end_b);

	gpio_i2c_read(client, 0x54, &val_0x54);
	val_0x54 &= ~((0x1) << (pDevChInfo->ch + 4));
	val_0x54 |= ((h_timing.fld_inv & 0x1) << (pDevChInfo->ch + 4));

	gpio_i2c_write(client, 0x54, val_0x54);

	//B5/6/7/8
	gpio_i2c_write(client, 0xFF, 0x05 + pDevChInfo->ch);
	//SYNC_RS B5/6/7/8 0x47
	gpio_i2c_write(client, 0x47, h_timing.sync_rs);
	//MEM_RDP B5/6/7/8 0x64
	gpio_i2c_write(client, 0x64, h_timing.mem_rdp);

	gpio_i2c_write(client, 0xA9, h_timing.v_blk_end_b);
}

void video_input_color_set(struct i2c_client *client, decoder_dev_ch_info_s *decoder_info)
{
	dprintk("%s()\n", __func__);
	//unsigned char val_9x44; // This IF sentense
	if(decoder_info->fmt_def == AHD20_1080P_30P || decoder_info->fmt_def == AHD20_1080P_25P ||
		decoder_info->fmt_def == CVI_FHD_30P || decoder_info->fmt_def == CVI_FHD_25P ||
		decoder_info->fmt_def == TVI_FHD_30P || decoder_info->fmt_def == TVI_FHD_25P ||
	   decoder_info->fmt_def == AHD30_4M_30P 	|| decoder_info->fmt_def == AHD30_4M_25P 	|| decoder_info->fmt_def == AHD30_4M_15P ||
	   decoder_info->fmt_def == CVI_4M_30P 		|| decoder_info->fmt_def == CVI_4M_25P 		||
	   decoder_info->fmt_def == TVI_4M_30P 		|| decoder_info->fmt_def == TVI_4M_25P
	   || decoder_info->fmt_def == TVI_5M_20P
	)
	{
		video_input_color_init_s color_init = (video_input_color_init_s)decoder_color_fmtdef[decoder_info->fmt_def];

		gpio_i2c_write(client, 0xff, 0x00 );
		gpio_i2c_write(client, 0x0c + decoder_info->ch, color_init.brightnees);
		gpio_i2c_write(client, 0x10 + decoder_info->ch, color_init.contrast );
		gpio_i2c_write(client, 0x22 + (decoder_info->ch*4), 0x0B );				// FIxed Value
		gpio_i2c_write(client, 0x3c + decoder_info->ch, color_init.saturation_a );
		gpio_i2c_write(client, 0x40 + decoder_info->ch, color_init.hue      );
		gpio_i2c_write(client, 0x44 + decoder_info->ch, color_init.u_gain   );
		gpio_i2c_write(client, 0x48 + decoder_info->ch, color_init.v_gain   );
		gpio_i2c_write(client, 0x4c + decoder_info->ch, color_init.u_offset );
		gpio_i2c_write(client, 0x50 + decoder_info->ch, color_init.v_offset );

		gpio_i2c_write(client, 0xff, 0x05 + decoder_info->ch);
		gpio_i2c_write(client, 0x2b, color_init.saturation_b);
		gpio_i2c_write(client, 0x20, color_init.black_level);
		gpio_i2c_write(client, 0x24, color_init.burst_dec_a);
		gpio_i2c_write(client, 0x5f, color_init.burst_dec_b);
		gpio_i2c_write(client, 0xd1, color_init.burst_dec_c);
	}
	else
	{
		dprintk("NOT_YET_SUPPORT_COLOR_SET_FORMAT:[%d]",decoder_info->fmt_def);
	}


	gpio_i2c_write(client, 0xff, 0x05 + decoder_info->ch);

	if(decoder_info->fmt_def == TVI_5M_12_5P)
		gpio_i2c_write(client, 0x26,0x20);
	else
		gpio_i2c_write(client, 0x26,0x40);


	gpio_i2c_write(client, 0xFF, 0x05 + decoder_info->ch);

	if(decoder_info->fmt_def == AHD20_SD_H960_2EX_Btype_NT || decoder_info->fmt_def == AHD20_SD_H960_2EX_Btype_PAL)
	{
		gpio_i2c_write(client, 0xB8, 0xB8);	// SD Rees Only
		gpio_i2c_write(client, 0xFF, 0x09);
		gpio_i2c_write(client, 0x40 + decoder_info->ch, 0x60);
	}
	else
	{
		gpio_i2c_write(client, 0xB8, 0x39); // Other Format
		gpio_i2c_write(client, 0xFF, 0x09);
		gpio_i2c_write(client, 0x40 + decoder_info->ch, 0x00);
	}
}

void video_input_vafe_init(struct i2c_client *client, decoder_dev_ch_info_s *decoder_info)
{
	unsigned char val_5678x00;
	unsigned char val_5678x01;
	unsigned char val_5678x58;
	unsigned char val_5678x59;
	unsigned char val_5678x5B;
	unsigned char val_5678x5C;

	dprintk("%s()\n", __func__);
	video_input_vafe_init_s afe = (video_input_vafe_init_s) decoder_afe_fmtdef [decoder_info->fmt_def];

	gpio_i2c_write(client, 0xFF, 0x00);

	//B0 0x00/1/2/3 gain[4], powerdown[0]
	gpio_i2c_write(client, 0x00 + decoder_info->ch, ((afe.gain & 0x01) << 4) | (afe.powerdown & 0x01));

	gpio_i2c_write(client, 0xFF, 0x01);
	gpio_i2c_write(client, 0x84 + decoder_info->ch, 0x00);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	//B5/6/7/8
	gpio_i2c_write(client, 0xFF, 0x05 + decoder_info->ch);

	//B5/6/7/8 0x01 spd[2], lpf_back_band[1:0]
	gpio_i2c_read(client, 0x00, &val_5678x00);
	val_5678x00 |= (afe.spd << 4);

	gpio_i2c_write(client, 0x00, val_5678x00);

	val_5678x01 = ((afe.ctrlreg << 6) | (afe.ctrlibs << 4) | (afe.adcspd << 2) | (afe.clplevel));
	gpio_i2c_write(client, 0x01, val_5678x01 );

	//B5/6/7/8 0x58 eq_band[7:4], lpf_front_band[1:0]
	val_5678x58 = ((afe.eq_band << 4) | (afe.lpf_front_band));
	gpio_i2c_write(client, 0x58, val_5678x58);

		//B5/6/7/8 0x5B ref_vol[1:0]
	val_5678x59 = ((afe.clpmode << 7) | (afe.f_lpf_bypass << 4) | (afe.clproff << 3) | (afe.b_lpf_bypass));
	gpio_i2c_write(client, 0x59, val_5678x59);

	val_5678x5B = ((afe.duty << 4) | (afe.ref_vol));
	gpio_i2c_write(client, 0x5B, val_5678x5B);

	val_5678x5C = ((afe.lpf_back_band << 4) | (afe.clk_sel << 3) | (afe.eq_gainsel));
	gpio_i2c_write(client, 0x5C, val_5678x5C);
}

void video_input_new_format_set(struct i2c_client *client, decoder_dev_ch_info_s *decoder_info)
{
	unsigned char ch = decoder_info->ch % 4;
	unsigned char devnum = decoder_info->devnum;
	//unsigned char fmtdef = decoder_info->fmt_def;
	unsigned char val_9x44;
	dprintk("%s()\n", __func__);

	gpio_i2c_write(client, 0xFF,0x09);
	gpio_i2c_read(client, 0x44, &val_9x44);
	val_9x44 &= ~(1 << ch);
	gpio_i2c_write(client, 0x44, val_9x44);

	/* CVI HD 30P PN Value Set */
	gpio_i2c_write(client, 0x50 + ( ch * 4 ) , 0x30);
	gpio_i2c_write(client, 0x51 + ( ch * 4 ) , 0x6F);
	gpio_i2c_write(client, 0x52 + ( ch * 4 ) , 0x67);
	gpio_i2c_write(client, 0x53 + ( ch * 4 ) , 0x48);

	gpio_i2c_write(client, 0xFF, 0x11);
	gpio_i2c_write(client, 0x00 + ( ch * 0x20 ), 0x00);

#ifdef FRAME_RATE_15	
	if(decoder_info->fmt_def == TVI_FHD_30P)
	{
		gpio_i2c_write(client, 0x18 + ( ch * 0x20 ), 0x11);
	}
#endif	
}

void video_input_eq_val_set(struct i2c_client *client, video_equalizer_info_s *pvin_eq_set)
{
	unsigned char val_13x30;
	unsigned char val_13x31;
	unsigned char val_0x54;
	unsigned char val_5678x69;
	unsigned char val_9x44;

	unsigned char ch = pvin_eq_set->Ch;
	unsigned char devnum = pvin_eq_set->devnum;

	if( pvin_eq_set->FmtDef == CVI_4M_25P  || pvin_eq_set->FmtDef == CVI_4M_30P  ||
	    pvin_eq_set->FmtDef == CVI_FHD_25P || pvin_eq_set->FmtDef == CVI_FHD_30P ||
	    pvin_eq_set->FmtDef == CVI_8M_12_5P			   || pvin_eq_set->FmtDef == CVI_8M_15P  			||
	    pvin_eq_set->FmtDef == TVI_4M_25P  || pvin_eq_set->FmtDef == TVI_4M_30P  ||
		pvin_eq_set->FmtDef == AHD30_3M_18P			   || pvin_eq_set->FmtDef == AHD30_3M_25P 			||
		pvin_eq_set->FmtDef == AHD30_3M_30P			   || pvin_eq_set->FmtDef == AHD30_4M_15P 		    ||
	    pvin_eq_set->FmtDef == AHD30_4M_25P			   || pvin_eq_set->FmtDef == AHD30_4M_30P 			||
		pvin_eq_set->FmtDef == AHD30_5M_12_5P		   || pvin_eq_set->FmtDef == AHD30_5M_20P			   ||
		pvin_eq_set->FmtDef == TVI_5M_12_5P			   || pvin_eq_set->FmtDef == TVI_3M_18P 			||
		pvin_eq_set->FmtDef == AHD20_1080P_30P         || pvin_eq_set->FmtDef == AHD20_1080P_25P 		||
		pvin_eq_set->FmtDef == TVI_FHD_30P             || pvin_eq_set->FmtDef == TVI_FHD_25P			||
		pvin_eq_set->FmtDef == AHD20_720P_30P_EX_Btype || pvin_eq_set->FmtDef == AHD20_720P_25P_EX_Btype ||
	    pvin_eq_set->FmtDef == CVI_HD_30P_EX           || pvin_eq_set->FmtDef == CVI_HD_25P_EX			||
		pvin_eq_set->FmtDef == CVI_HD_30P              || pvin_eq_set->FmtDef == CVI_HD_25P  			||
		pvin_eq_set->FmtDef == CVI_HD_60P              || pvin_eq_set->FmtDef == CVI_HD_50P   			||
	    pvin_eq_set->FmtDef == TVI_HD_30P			   || pvin_eq_set->FmtDef == TVI_HD_25P			    ||
	    pvin_eq_set->FmtDef == TVI_HD_30P_EX		   || pvin_eq_set->FmtDef == TVI_HD_25P_EX			||
	    pvin_eq_set->FmtDef == TVI_HD_B_30P			   || pvin_eq_set->FmtDef == TVI_HD_B_25P 			||
	    pvin_eq_set->FmtDef == TVI_HD_B_30P_EX		   || pvin_eq_set->FmtDef == TVI_HD_B_25P_EX		||
		pvin_eq_set->FmtDef == AHD20_SD_H960_2EX_Btype_NT || pvin_eq_set->FmtDef == AHD20_SD_H960_2EX_Btype_PAL ||
		pvin_eq_set->FmtDef == AHD20_SD_H960_NT || pvin_eq_set->FmtDef == AHD20_SD_H960_PAL ||

		pvin_eq_set->FmtDef == AHD20_1080P_60P         || pvin_eq_set->FmtDef == AHD20_1080P_50P		||

		 pvin_eq_set->FmtDef == AHD30_8M_12_5P			   || pvin_eq_set->FmtDef == AHD30_8M_15P  			||
		 pvin_eq_set->FmtDef == AHD30_8M_7_5P			   ||

		pvin_eq_set->FmtDef == TVI_5M_20P				  || pvin_eq_set->FmtDef == AHD30_5_3M_20P		||
		pvin_eq_set->FmtDef == TVI_4M_15P
		/* and all format */
		)
	{
		/* cable type => 0:coaxial, 1:utp, 2:reserved1, 3:reserved2 */
		video_equalizer_value_table_s eq_value = (video_equalizer_value_table_s)equalizer_value_fmtdef[pvin_eq_set->FmtDef];

                /* for verification by edward */

		if(pvin_eq_set->FmtDef == AHD20_720P_30P_EX_Btype || pvin_eq_set->FmtDef == AHD20_720P_25P_EX_Btype ||
		   pvin_eq_set->FmtDef == CVI_HD_30P_EX           || pvin_eq_set->FmtDef == CVI_HD_25P_EX			||
		   pvin_eq_set->FmtDef == CVI_HD_30P              || pvin_eq_set->FmtDef == CVI_HD_25P  			||
		   pvin_eq_set->FmtDef == TVI_HD_30P			  || pvin_eq_set->FmtDef == TVI_HD_25P			    ||
		   pvin_eq_set->FmtDef == TVI_HD_30P_EX			  || pvin_eq_set->FmtDef == TVI_HD_25P_EX			||
		   pvin_eq_set->FmtDef == TVI_HD_B_30P			  || pvin_eq_set->FmtDef == TVI_HD_B_25P 			||
		   pvin_eq_set->FmtDef == TVI_HD_B_30P_EX		  || pvin_eq_set->FmtDef == TVI_HD_B_25P_EX   	    
		   
		  )
		{
			dprintk("DRV >> This Format Support Maximum EQ Stage 10\n");
			dprintk("DRV >> Now Select EQ Stage %d\n", pvin_eq_set->distance);
		}
		else
		{
			if(pvin_eq_set->distance > 5)
			{
				dprintk("DRV >> This Format Only Support Maximum EQ Stage 5\n");
				dprintk("DRV >> Now Select EQ Stage %d\n", pvin_eq_set->distance);
				pvin_eq_set->distance = 5;
			}
		}

		/* set eq value */
		__eq_base_set_value(client, pvin_eq_set, &eq_value.eq_base );
		__eq_coeff_set_value(client, pvin_eq_set, &eq_value.eq_coeff );
		__eq_color_set_value(client, pvin_eq_set, &eq_value.eq_color);
		__eq_timing_a_set_value(client, pvin_eq_set, &eq_value.eq_timing_a );
		__eq_clk_set_value(client, pvin_eq_set, &eq_value.eq_clk );
		__eq_timing_b_set_value(client, pvin_eq_set, &eq_value.eq_timing_b );

		if( pvin_eq_set->FmtDef == AHD20_SD_H960_2EX_Btype_NT || pvin_eq_set->FmtDef == AHD20_SD_H960_2EX_Btype_PAL ||  pvin_eq_set->FmtDef == AHD20_SD_H960_NT || pvin_eq_set->FmtDef == AHD20_SD_H960_PAL )
		{
			gpio_i2c_write(client, 0xff, 0x00);

			gpio_i2c_write(client, 0x34 + ch, 0x01);		/* line_mem_mode Enable */

			if(( pvin_eq_set->FmtDef == AHD20_SD_H960_2EX_Btype_NT )
				|| ( pvin_eq_set->FmtDef == AHD20_SD_H960_NT))
			{
				gpio_i2c_read(client, 0x54, &val_0x54);
				val_0x54 &= ~((0x1 << (ch+4)));
				val_0x54 |= ((0x1 << (ch+4)));
				gpio_i2c_write(client, 0x54, val_0x54);  /* Enable FLD_INV for CVBS NT format */

				gpio_i2c_write(client, 0x08 + ch, 0xa0);
				gpio_i2c_write(client, 0x5c + ch, 0xd0); /* Set V_Delay */
			}
			else if(( pvin_eq_set->FmtDef == AHD20_SD_H960_2EX_Btype_PAL )
				|| ( pvin_eq_set->FmtDef == AHD20_SD_H960_PAL))
			{
				gpio_i2c_read(client, 0x54, &val_0x54);
				val_0x54 &= ~((0x1 << (ch+4)));
				gpio_i2c_write(client, 0x54, val_0x54);  /* Disable FLD_INV for CVBS PAL format */

				gpio_i2c_write(client, 0x08 + ch, 0xdd);
				gpio_i2c_write(client, 0x5c + ch, 0xbf);  /* Set V_Delay */

			}

			gpio_i2c_write( client, 0xff, 0x05 + ch );

			if( pvin_eq_set->FmtDef == AHD20_SD_H960_2EX_Btype_NT || pvin_eq_set->FmtDef == AHD20_SD_H960_2EX_Btype_PAL)
			gpio_i2c_write( client, 0x64, 0x01 );         /* Enable Mem_Path */
			else
			gpio_i2c_write( client, 0x64, 0x00 );         /* Disable Mem_Path */

			gpio_i2c_read(client, 0x69, &val_5678x69);
			val_5678x69 &= ~(0x1);
			val_5678x69 |= 0x1;
			gpio_i2c_write( client, 0x69, val_5678x69 );	/* Enable sd_freq_sel */
		}
		else
		{
			gpio_i2c_write(client, 0xff, 0x00);
			gpio_i2c_write(client, 0x34 + ch, 0x00);		/* line_mem_mode Disable */
			gpio_i2c_read(client, 0x54, &val_0x54);
			val_0x54 &= ~((0x1 << (ch+4)));
			gpio_i2c_write(client, 0x54, val_0x54);	/* Disable FLD_INV */

			gpio_i2c_write(client, 0x08 + ch, 0x00);
			gpio_i2c_write(client, 0x5c + ch, 0x80);	/* Recovery V_Delay */

			gpio_i2c_write( client, 0xff, 0x05 + ch );
			gpio_i2c_write( client, 0x64, 0x00 );        /* Disable Mem_Path */

			gpio_i2c_read(client, 0x69, &val_5678x69);
			val_5678x69 &= ~(0x1);
			gpio_i2c_write( client, 0x69, val_5678x69 );	/* Disable sd_freq_sel */
		}

		if( 	pvin_eq_set->FmtDef == CVI_4M_25P  			   || pvin_eq_set->FmtDef == CVI_4M_30P  			||
		   pvin_eq_set->FmtDef == CVI_FHD_25P || pvin_eq_set->FmtDef == CVI_FHD_30P ||
			pvin_eq_set->FmtDef == CVI_8M_12_5P			   || pvin_eq_set->FmtDef == CVI_8M_15P  			||
		   pvin_eq_set->FmtDef == TVI_4M_25P  || pvin_eq_set->FmtDef == TVI_4M_30P  ||
				pvin_eq_set->FmtDef == AHD30_3M_18P			   || pvin_eq_set->FmtDef == AHD30_3M_25P 			||
				pvin_eq_set->FmtDef == AHD30_3M_30P			   || pvin_eq_set->FmtDef == AHD30_4M_15P 		    ||
			pvin_eq_set->FmtDef == AHD30_4M_25P			   || pvin_eq_set->FmtDef == AHD30_4M_30P 			||
				pvin_eq_set->FmtDef == AHD30_5M_12_5P		   || pvin_eq_set->FmtDef == AHD30_5M_20P			   ||
			pvin_eq_set->FmtDef == TVI_5M_12_5P			   || pvin_eq_set->FmtDef == TVI_3M_18P 			||
			pvin_eq_set->FmtDef == AHD20_1080P_30P         || pvin_eq_set->FmtDef == AHD20_1080P_25P 		||
			pvin_eq_set->FmtDef == TVI_FHD_30P             || pvin_eq_set->FmtDef == TVI_FHD_25P			||
			pvin_eq_set->FmtDef == AHD20_720P_30P_EX_Btype || pvin_eq_set->FmtDef == AHD20_720P_25P_EX_Btype ||
			pvin_eq_set->FmtDef == CVI_HD_30P_EX           || pvin_eq_set->FmtDef == CVI_HD_25P_EX			||
			pvin_eq_set->FmtDef == CVI_HD_30P              || pvin_eq_set->FmtDef == CVI_HD_25P  			||
			pvin_eq_set->FmtDef == CVI_HD_60P              || pvin_eq_set->FmtDef == CVI_HD_50P   			||
			pvin_eq_set->FmtDef == TVI_HD_30P			   || pvin_eq_set->FmtDef == TVI_HD_25P			    ||
			pvin_eq_set->FmtDef == TVI_HD_30P_EX		   || pvin_eq_set->FmtDef == TVI_HD_25P_EX			||
			pvin_eq_set->FmtDef == TVI_HD_B_30P			   || pvin_eq_set->FmtDef == TVI_HD_B_25P 			||
			pvin_eq_set->FmtDef == TVI_HD_B_30P_EX		   || pvin_eq_set->FmtDef == TVI_HD_B_25P_EX		||
			pvin_eq_set->FmtDef == AHD20_SD_H960_2EX_Btype_NT || pvin_eq_set->FmtDef == AHD20_SD_H960_2EX_Btype_PAL ||
			pvin_eq_set->FmtDef == AHD20_SD_H960_NT || pvin_eq_set->FmtDef == AHD20_SD_H960_PAL ||
		
	pvin_eq_set->FmtDef == AHD20_1080P_60P         || pvin_eq_set->FmtDef == AHD20_1080P_50P ||

			 pvin_eq_set->FmtDef == AHD30_8M_12_5P		   || pvin_eq_set->FmtDef == AHD30_8M_15P  			||
			 pvin_eq_set->FmtDef == AHD30_8M_7_5P		   || pvin_eq_set->FmtDef == TVI_5M_20P				||
			pvin_eq_set->FmtDef == AHD30_5_3M_20P		   || pvin_eq_set->FmtDef == TVI_4M_15P
		   )
		{	/* Auto Mode Off */
			gpio_i2c_write(client, 0xff, 0x13 );
			gpio_i2c_read(client, 0x30, &val_13x30);
			val_13x30 &= ~(0x11 << pvin_eq_set->Ch);
			gpio_i2c_write(client, 0x30, val_13x30 );

			gpio_i2c_write(client, 0xff, 0x13 );
			gpio_i2c_read(client, 0x31, &val_13x31);
			val_13x31 &= ~(0x11 << pvin_eq_set->Ch);
			gpio_i2c_write(client, 0x31, val_13x31 );

			gpio_i2c_write(client, 0xff, 0x05 + ch);
			gpio_i2c_write(client, 0x59, 0x00 );

		}
		else
		{   /* Auto Mode ON */
			gpio_i2c_write(client, 0xff, 0x13 );
			gpio_i2c_read(client, 0x30, &val_13x30);
			val_13x30 |= (0x11 << pvin_eq_set->Ch);
			gpio_i2c_write(client, 0x30, val_13x30 );

			gpio_i2c_write(client, 0xff, 0x13 );
			gpio_i2c_read(client, 0x31, &val_13x31);
			val_13x31 |= (0x11 << pvin_eq_set->Ch);
			gpio_i2c_write(client, 0x31, val_13x31 );
		}

		gpio_i2c_write(client, 0xff, 0x00);
		gpio_i2c_write(client, 0x23 + (pvin_eq_set->Ch * 4), 0x41);
	}

	if( pvin_eq_set->FmtDef == TVI_5M_20P || pvin_eq_set->FmtDef == TVI_5M_12_5P ||
			pvin_eq_set->FmtDef == TVI_4M_30P || pvin_eq_set->FmtDef == TVI_4M_25P		)
	{

		gpio_i2c_write(client, 0xFF,0x09);
		gpio_i2c_read(client, 0x44, &val_9x44);
		val_9x44 &= ~(1 << ch);
		val_9x44 |= (1 << ch);
		gpio_i2c_write(client, 0x44 , val_9x44);

		if( pvin_eq_set->FmtDef == TVI_5M_20P)
		{
			/* TVI 5M 20P PN Value Set */
			gpio_i2c_write(client, 0x50 + ( ch * 4 ) , 0x36);
			gpio_i2c_write(client, 0x51 + ( ch * 4 ) , 0x40);
			gpio_i2c_write(client, 0x52 + ( ch * 4 ) , 0xa7);
			gpio_i2c_write(client, 0x53 + ( ch * 4 ) , 0x74);

			gpio_i2c_write(client, 0xFF, 0x11);
			gpio_i2c_write(client, 0x02 + ( ch * 0x20 ), 0xdb);
			gpio_i2c_write(client, 0x03 + ( ch * 0x20 ), 0x0a);
			gpio_i2c_write(client, 0x05 + ( ch * 0x20 ), 0x0e);
			gpio_i2c_write(client, 0x06 + ( ch * 0x20 ), 0xa6);
			gpio_i2c_write(client, 0x08 + ( ch * 0x20 ), 0x96);
			gpio_i2c_write(client, 0x0a + ( ch * 0x20 ), 0x07);
			gpio_i2c_write(client, 0x0b + ( ch * 0x20 ), 0x98);
			gpio_i2c_write(client, 0x0c + ( ch * 0x20 ), 0x07);
			gpio_i2c_write(client, 0x0d + ( ch * 0x20 ), 0xbc);
			gpio_i2c_write(client, 0x11 + ( ch * 0x20 ), 0xa0);
			gpio_i2c_write(client, 0x13 + ( ch * 0x20 ), 0xfa);
			gpio_i2c_write(client, 0x15 + ( ch * 0x20 ), 0x65);
			gpio_i2c_write(client, 0x00 + ( ch * 0x20 ), 0x0f);
		}
		else if( pvin_eq_set->FmtDef == TVI_5M_12_5P)
		{
			/* TVI 5M 12_5P PN Value Set */
			gpio_i2c_write(client, 0x50 + ( ch * 4 ) , 0x8b);
			gpio_i2c_write(client, 0x51 + ( ch * 4 ) , 0xae);
			gpio_i2c_write(client, 0x52 + ( ch * 4 ) , 0xbb);
			gpio_i2c_write(client, 0x53 + ( ch * 4 ) , 0x48);
		}
		else if( pvin_eq_set->FmtDef == TVI_4M_30P || pvin_eq_set->FmtDef == TVI_4M_25P )
		{
			/* TVI 4M 30P PN Value Set */
			gpio_i2c_write(client, 0x50 + ( ch * 4 ) , 0x9e);
			gpio_i2c_write(client, 0x51 + ( ch * 4 ) , 0x48);
			gpio_i2c_write(client, 0x52 + ( ch * 4 ) , 0x59);
			gpio_i2c_write(client, 0x53 + ( ch * 4 ) , 0x74);
		}
	}
	else if( pvin_eq_set->FmtDef == AHD20_960P_60P || pvin_eq_set->FmtDef == AHD20_960P_50P ||
			pvin_eq_set->FmtDef == AHD20_960P_30P || pvin_eq_set->FmtDef == AHD20_960P_25P )

	{
		gpio_i2c_write(client, 0xFF,0x09);
		gpio_i2c_read(client, 0x44, &val_9x44);
		val_9x44 &= ~(1 << ch);
		val_9x44 |= (1 << ch);
		gpio_i2c_write(client, 0x44 , val_9x44);
	}
	else
	{
		gpio_i2c_write(client, 0xFF,0x09);
		gpio_i2c_read(client, 0x44, &val_9x44);
		val_9x44 &= ~(1 << ch);
		gpio_i2c_write(client, 0x44 , val_9x44);
	}

#ifdef __FOR_DEMO_171024

	if( pvin_eq_set->FmtDef == AHD20_720P_30P )
	{
		gpio_i2c_write(client, 0xff, 0x00 );
		gpio_i2c_write(client, 0x3c + ch, 0xa0 );
	}
	else
	{
		gpio_i2c_write(client, 0xff, 0x00 );
		gpio_i2c_write(client, 0x3c + ch, 0x80 );
	}
#endif

#ifdef __FOR_CHINA_HYUNDAI_180319
	gpio_i2c_write(client, 0xff, (ch < 2 ? 0x0a : 0x0b) );
	gpio_i2c_write(client, 0x77 + (ch%2 * 0x80), 0x8f );

	printk(">>>>>> DRV[%s:%d] agc gain turn off : CH:%d\n", __func__, __LINE__, ch);
#endif

#ifdef __FOR_DEMO_180307_FUJITSU

	if( pvin_eq_set->FmtDef == AHD20_720P_30P_EX_Btype )
	{
		gpio_i2c_write(client, 0xff, 0x05 + ch );
		gpio_i2c_write(client, 0x1b, 0x20 );
	}
	else
	{
		gpio_i2c_write(client, 0xff, 0x05 + ch );
		gpio_i2c_write(client, 0x1b, 0x08 ); /* Decoder Default Setting */
	}

#endif

}

void __eq_base_set_value(struct i2c_client *client, video_equalizer_info_s *pvin_eq_set, video_equalizer_base_s *pbase )
{
	unsigned char devnum = pvin_eq_set->devnum;
	unsigned char ch = pvin_eq_set->Ch;
	unsigned char dist = pvin_eq_set->distance;

	gpio_i2c_write(client, 0xFF, 0x05 + ch );
	gpio_i2c_write(client, 0x01, pbase->eq_bypass[dist] );
	gpio_i2c_write(client, 0x58, pbase->eq_band_sel[dist] );
	gpio_i2c_write(client, 0x5C, pbase->eq_gain_sel[dist] );

	gpio_i2c_write(client, 0xff, (ch < 2 ? 0x0a : 0x0b) );
	gpio_i2c_write(client, 0x3d + (ch%2 * 0x80), pbase->deq_a_on[dist] );
	gpio_i2c_write(client, 0x3c + (ch%2 * 0x80), pbase->deq_a_sel[dist] );

	gpio_i2c_write(client, 0xFF, 0x09 );
	gpio_i2c_write(client, 0x80 + (ch * 0x20), pbase->deq_b_sel[dist] );

#if 0 //test
	printk("ch[%d]: BASE, dist:%d, eq_bypass[%02x]\n", ch, dist, pbase->eq_bypass[dist] );
	printk("ch[%d]: BASE, dist:%d, eq_band_sel[%02x]\n", ch, dist, pbase->eq_band_sel[dist] );
	printk("ch[%d]: BASE, dist:%d, eq_gain_sel[%02x]\n", ch, dist, pbase->eq_gain_sel[dist] );
	printk("ch[%d]: BASE, dist:%d, deq_a_on[%02x]\n", ch, dist, pbase->deq_a_on[dist] );
	printk("ch[%d]: BASE, dist:%d, deq_a_sel[%02x]\n", ch, dist, pbase->deq_a_sel[dist] );
	printk("ch[%d]: BASE, dist:%d, deq_b_sel[%02x]\n", ch, dist, pbase->deq_b_sel[dist] );
#endif
}

void __eq_coeff_set_value(struct i2c_client *client, video_equalizer_info_s *pvin_eq_set, video_equalizer_coeff_s *pcoeff )
{
	unsigned char devnum = pvin_eq_set->devnum;
	unsigned char ch = pvin_eq_set->Ch;
	unsigned char dist = pvin_eq_set->distance;

//	unsigned char val_0x30;
//	unsigned char val_0x31;
//	unsigned char val_0x32;

	gpio_i2c_write(client, 0xff, (ch < 2 ? 0x0a : 0x0b) );
	gpio_i2c_write(client, 0x30 + (ch%2 * 0x80), pcoeff->deqA_01[dist] );
	gpio_i2c_write(client, 0x31 + (ch%2 * 0x80), pcoeff->deqA_02[dist] );
	gpio_i2c_write(client, 0x32 + (ch%2 * 0x80), pcoeff->deqA_03[dist] );
	gpio_i2c_write(client, 0x33 + (ch%2 * 0x80), pcoeff->deqA_04[dist] );
	gpio_i2c_write(client, 0x34 + (ch%2 * 0x80), pcoeff->deqA_05[dist] );
	gpio_i2c_write(client, 0x35 + (ch%2 * 0x80), pcoeff->deqA_06[dist] );
	gpio_i2c_write(client, 0x36 + (ch%2 * 0x80), pcoeff->deqA_07[dist] );
	gpio_i2c_write(client, 0x37 + (ch%2 * 0x80), pcoeff->deqA_08[dist] );
	gpio_i2c_write(client, 0x38 + (ch%2 * 0x80), pcoeff->deqA_09[dist] );
	gpio_i2c_write(client, 0x39 + (ch%2 * 0x80), pcoeff->deqA_10[dist] );
	gpio_i2c_write(client, 0x3a + (ch%2 * 0x80), pcoeff->deqA_11[dist] );
	gpio_i2c_write(client, 0x3b + (ch%2 * 0x80), pcoeff->deqA_12[dist] );

#if 0
	printk("ch[%d]: COEFF, dist:%d, deqA_01[%02x]\n", ch, dist, pcoeff->deqA_01[dist] );
	printk("ch[%d]: COEFF, dist:%d, deqA_02[%02x]\n", ch, dist, pcoeff->deqA_02[dist] );
	printk("ch[%d]: COEFF, dist:%d, deqA_03[%02x]\n", ch, dist, pcoeff->deqA_03[dist] );
	printk("ch[%d]: COEFF, dist:%d, deqA_04[%02x]\n", ch, dist, pcoeff->deqA_04[dist] );
	printk("ch[%d]: COEFF, dist:%d, deqA_05[%02x]\n", ch, dist, pcoeff->deqA_05[dist] );
	printk("ch[%d]: COEFF, dist:%d, deqA_06[%02x]\n", ch, dist, pcoeff->deqA_06[dist] );
	printk("ch[%d]: COEFF, dist:%d, deqA_07[%02x]\n", ch, dist, pcoeff->deqA_07[dist] );
	printk("ch[%d]: COEFF, dist:%d, deqA_08[%02x]\n", ch, dist, pcoeff->deqA_08[dist] );
	printk("ch[%d]: COEFF, dist:%d, deqA_09[%02x]\n", ch, dist, pcoeff->deqA_09[dist] );
	printk("ch[%d]: COEFF, dist:%d, deqA_10[%02x]\n", ch, dist, pcoeff->deqA_10[dist] );
	printk("ch[%d]: COEFF, dist:%d, deqA_11[%02x]\n", ch, dist, pcoeff->deqA_11[dist] );
	printk("ch[%d]: COEFF, dist:%d, deqA_12[%02x]\n", ch, dist, pcoeff->deqA_12[dist] );
#endif

//	gpio_i2c_write(client, 0xff, 0x13 );
//	gpio_i2c_read(client, 0x30, &val_0x30);
//	gpio_i2c_read(client, 0x31, &val_0x31);
//	gpio_i2c_read(client, 0x32, &val_0x32);
//	val_0x30 |= ((1 << (ch + 4)) | (1 << ch));
//	val_0x31 |= ((1 << (ch + 4)) | (1 << ch));
//	val_0x32 |= ((1 << ch) & 0xF);
//	gpio_i2c_write(client, 0x30, val_0x30);
//	gpio_i2c_write(client, 0x31, val_0x31);
//	gpio_i2c_write(client, 0x32, val_0x32);
}

void __eq_color_set_value(struct i2c_client *client, video_equalizer_info_s *pvin_eq_set, video_equalizer_color_s *pcolor )
{
	unsigned char devnum = pvin_eq_set->devnum;
	unsigned char ch = pvin_eq_set->Ch;
	unsigned char dist = pvin_eq_set->distance;

	gpio_i2c_write(client, 0xff, 0x00 );
	gpio_i2c_write(client, 0x10 + ch, pcolor->contrast[dist] );
	gpio_i2c_write(client, 0x18 + ch, pcolor->h_peaking[dist] );
	gpio_i2c_write(client, 0x21 + ch*4, pcolor->c_filter[dist] );

	gpio_i2c_write(client, 0x40 + ch, pcolor->hue[dist] );
	gpio_i2c_write(client, 0x44 + ch, pcolor->u_gain[dist] );
	gpio_i2c_write(client, 0x48 + ch, pcolor->v_gain[dist] );
	gpio_i2c_write(client, 0x4C + ch, pcolor->u_offset[dist] );
	gpio_i2c_write(client, 0x50 + ch, pcolor->v_offset[dist] );

	gpio_i2c_write(client, 0xff, 0x05 + ch);
	gpio_i2c_write(client, 0x20, pcolor->black_level[dist] );
	gpio_i2c_write(client, 0x27, pcolor->acc_ref[dist] );
	gpio_i2c_write(client, 0x28, pcolor->cti_delay[dist] );
	gpio_i2c_write(client, 0x2b, pcolor->sub_saturation[dist] );

	gpio_i2c_write(client, 0x24, pcolor->burst_dec_a[dist] );
	gpio_i2c_write(client, 0x5f, pcolor->burst_dec_b[dist] );
	gpio_i2c_write(client, 0xd1, pcolor->burst_dec_c[dist] );

	gpio_i2c_write(client, 0xd5, pcolor->c_option[dist] );

	gpio_i2c_write(client, 0xff, (ch < 2 ? 0x0a : 0x0b) );
	gpio_i2c_write(client, 0x25 + (ch%2 * 0x80), pcolor->y_filter_b[dist] );
	gpio_i2c_write(client, 0x27 + (ch%2 * 0x80), pcolor->y_filter_b_sel[dist] );

	//YH : color tune	
	if(pvin_eq_set->FmtDef == TVI_FHD_25P || pvin_eq_set->FmtDef == TVI_FHD_30P)
	{
		gpio_i2c_write(client, 0xff, 0x00 );

		gpio_i2c_write(client, 0x0c + ch, 0x12 );
		switch(dist)
		{
		case 0 :  gpio_i2c_write(client, 0x3c + ch, 0x90 );
			break;
		case 1 : gpio_i2c_write(client, 0x3c + ch, 0xa0 );
			break;
		case 2 : gpio_i2c_write(client, 0x3c + ch, 0xb0 );
			break;
		case 3 : gpio_i2c_write(client, 0x3c + ch, 0xb0 );
			break;
		case 4 : gpio_i2c_write(client, 0x3c + ch, 0x90 );
			break;
		case 5 : gpio_i2c_write(client, 0x3c + ch, 0x80 );
			break;

		default : gpio_i2c_write(client, 0x3c + ch, 0x90 );
			break;
		}
	}
	else
	{
		gpio_i2c_write(client, 0xff, 0x00 );

		gpio_i2c_write(client, 0x0c + ch, 0x00 );
		gpio_i2c_write(client, 0x3c + ch, 0x80 );
	}
#if 0
#ifdef __FOR_IDIS_TVI_2M
	if(pvin_eq_set->FmtDef == TVI_FHD_25P || pvin_eq_set->FmtDef == TVI_FHD_30P)
	{
		gpio_i2c_write(client, 0xff, 0x00 );

		gpio_i2c_write(client, 0x0c + ch, 0x12 );
		switch(dist)
		{
		case 0 :  gpio_i2c_write(client, 0x3c + ch, 0x90 );
			break;
		case 1 : gpio_i2c_write(client, 0x3c + ch, 0xa0 );
			break;
		case 2 : gpio_i2c_write(client, 0x3c + ch, 0xb0 );
			break;
		case 3 : gpio_i2c_write(client, 0x3c + ch, 0xb0 );
			break;
		case 4 : gpio_i2c_write(client, 0x3c + ch, 0x90 );
			break;
		case 5 : gpio_i2c_write(client, 0x3c + ch, 0x80 );
			break;

		default : gpio_i2c_write(client, 0x3c + ch, 0x90 );
			break;
		}
	}
	else
	{
		gpio_i2c_write(client, 0xff, 0x00 );

		gpio_i2c_write(client, 0x0c + ch, 0x00 );
		gpio_i2c_write(client, 0x3c + ch, 0x80 );
	}
#elif defined(__FOR_HIK_DEMO_180208)

	if( pvin_eq_set->FmtDef == TVI_4M_25P )
	{
		gpio_i2c_write(client, 0xff, 0x00 );

		gpio_i2c_write(client, 0x0c + ch, 0x00 );
		gpio_i2c_write(client, 0x3c + ch, 0x80 );
	}
	else if(pvin_eq_set->FmtDef == TVI_FHD_25P )
	{
		gpio_i2c_write(client, 0xff, 0x00 );

		gpio_i2c_write(client, 0x3c + ch, 0x80 );

		switch(dist)
		{
			case 0 :
			case 1 :
			case 2 :
			case 3 : gpio_i2c_write(client, 0x0c + ch, 0x00 );
				break;
			case 4 :
			case 5 : gpio_i2c_write(client, 0x0c + ch, 0xf0 );
				break;
			default : gpio_i2c_write(client, 0x0c + ch, 0x00 );
				break;
		}
	}
	else if( pvin_eq_set->FmtDef == TVI_HD_B_25P_EX )
	{
		gpio_i2c_write(client, 0xff, 0x00 );

		gpio_i2c_write(client, 0x0c + ch, 0xf0 );
		gpio_i2c_write(client, 0x3c + ch, 0x90 );
	}
	else
	{
		gpio_i2c_write(client, 0xff, 0x00 );

		gpio_i2c_write(client, 0x0c + ch, 0x00 );
		gpio_i2c_write(client, 0x3c + ch, 0x80 );
	}

#else

#endif
#endif
#if 0
	printk("ch[%d]: COLOR, dist:%d, contrast[%02x]\n", ch, dist, pcolor->contrast[dist] );
	printk("ch[%d]: COLOR, dist:%d, h_peaking[%02x]\n", ch, dist, pcolor->h_peaking[dist] );
	printk("ch[%d]: COLOR, dist:%d, c_filter[%02x]\n", ch, dist, pcolor->c_filter[dist] );

	printk("ch[%d]: COLOR, dist:%d, hue[%02x]\n", ch, dist, pcolor->hue[dist] );
	printk("ch[%d]: COLOR, dist:%d, u_gain[%02x]\n", ch, dist, pcolor->u_gain[dist] );
	printk("ch[%d]: COLOR, dist:%d, v_gain[%02x]\n", ch, dist, pcolor->v_gain[dist] );
	printk("ch[%d]: COLOR, dist:%d, u_offset[%02x]\n", ch, dist, pcolor->u_offset[dist] );
	printk("ch[%d]: COLOR, dist:%d, v_offset[%02x]\n", ch, dist, pcolor->v_offset[dist] );

	printk("ch[%d]: COLOR, dist:%d, black_level[%02x]\n", ch, dist, pcolor->black_level[dist] );
	printk("ch[%d]: COLOR, dist:%d, cti_delay[%02x]\n", ch, dist, pcolor->cti_delay[dist] );
	printk("ch[%d]: COLOR, dist:%d, sub_saturation[%02x]\n", ch, dist, pcolor->sub_saturation[dist] );

	printk("ch[%d]: COLOR, dist:%d, burst_dec_a[%02x]\n", ch, dist, pcolor->burst_dec_a[dist] );
	printk("ch[%d]: COLOR, dist:%d, burst_dec_b[%02x]\n", ch, dist, pcolor->burst_dec_b[dist] );
	printk("ch[%d]: COLOR, dist:%d, burst_dec_c[%02x]\n", ch, dist, pcolor->burst_dec_c[dist] );

	printk("ch[%d]: COLOR, dist:%d, c_option[%02x]\n", ch, dist, pcolor->c_option[dist] );
#endif
}

void __eq_timing_a_set_value(struct i2c_client *client, video_equalizer_info_s *pvin_eq_set, video_equalizer_timing_a_s *ptiming_a )
{
	unsigned char devnum = pvin_eq_set->devnum;
	unsigned char ch = pvin_eq_set->Ch;
	unsigned char dist = pvin_eq_set->distance;

	gpio_i2c_write(client, 0xFF, 0x00 );
	gpio_i2c_write(client, 0x58 + ch, ptiming_a->h_delay_a[dist] );
	gpio_i2c_write(client, 0x89 + ch, ptiming_a->h_delay_b[dist] );
	gpio_i2c_write(client, 0x8e + ch, ptiming_a->h_delay_c[dist] );
	gpio_i2c_write(client, 0xa0 + ch, ptiming_a->y_delay[dist] );

#if 0
	printk("ch[%d]: TIMING_A, dist:%d, h_delay_a[%02x]\n", ch, dist, ptiming_a->h_delay_a[dist] );
	printk("ch[%d]: TIMING_A, dist:%d, h_delay_b[%02x]\n", ch, dist, ptiming_a->h_delay_b[dist] );
	printk("ch[%d]: TIMING_A, dist:%d, h_delay_c[%02x]\n", ch, dist, ptiming_a->h_delay_c[dist] );
	printk("ch[%d]: TIMING_A, dist:%d, y_delay[%02x]\n", ch, dist, ptiming_a->y_delay[dist] );
#endif
}

void __eq_clk_set_value(struct i2c_client *client, video_equalizer_info_s *pvin_eq_set, video_equalizer_clk_s *pclk )
{
	unsigned char devnum = pvin_eq_set->devnum;
	unsigned char ch = pvin_eq_set->Ch;
	unsigned char dist = pvin_eq_set->distance;

	gpio_i2c_write(client, 0xFF, 0x01 );
	gpio_i2c_write(client, 0x84 + ch, pclk->clk_adc[dist] );
	gpio_i2c_write(client, 0x8C + ch, pclk->clk_dec[dist] );
}
void __eq_timing_b_set_value(struct i2c_client *client, video_equalizer_info_s *pvin_eq_set, video_equalizer_timing_b_s *ptiming_b )
{
	unsigned char devnum = pvin_eq_set->devnum;
	unsigned char ch = pvin_eq_set->Ch;
	unsigned char dist = pvin_eq_set->distance;

	gpio_i2c_write(client, 0xff, 0x09 );
	gpio_i2c_write(client, 0x96 + (ch * 0x20), ptiming_b->h_scaler1[dist] );
	gpio_i2c_write(client, 0x97 + (ch * 0x20), ptiming_b->h_scaler2[dist] );
	gpio_i2c_write(client, 0x98 + (ch * 0x20), ptiming_b->h_scaler3[dist] );
	gpio_i2c_write(client, 0x99 + (ch * 0x20), ptiming_b->h_scaler4[dist] );
	gpio_i2c_write(client, 0x9A + (ch * 0x20), ptiming_b->h_scaler5[dist] );
	gpio_i2c_write(client, 0x9B + (ch * 0x20), ptiming_b->h_scaler6[dist] );
	gpio_i2c_write(client, 0x9C + (ch * 0x20), ptiming_b->h_scaler7[dist] );
	gpio_i2c_write(client, 0x9D + (ch * 0x20), ptiming_b->h_scaler8[dist] );
	gpio_i2c_write(client, 0x9E + (ch * 0x20), ptiming_b->h_scaler9[dist] );

	gpio_i2c_write(client, 0x40 + ch , 		 ptiming_b->pn_auto[dist] );

	gpio_i2c_write(client, 0xff, 0x05 + ch );
	gpio_i2c_write(client, 0x90, ptiming_b->comb_mode[dist] );
	gpio_i2c_write(client, 0xb9, ptiming_b->h_pll_op_a[dist] );
	gpio_i2c_write(client, 0x57, ptiming_b->mem_path[dist] );
	gpio_i2c_write(client, 0x25, ptiming_b->fsc_lock_speed[dist] );


	gpio_i2c_write(client, 0xff, 0x00 );
	gpio_i2c_write(client, 0x81 + ch, ptiming_b->format_set1[dist] );
	gpio_i2c_write(client, 0x85 + ch, ptiming_b->format_set2[dist] );
	gpio_i2c_write(client, 0x64 + ch, ptiming_b->v_delay[dist] );

#if 0
	printk("ch[%d]: TIMING_B, dist:%d, h_scaler1[%02x]\n", ch, dist, ptiming_b->h_scaler1[dist] );
	printk("ch[%d]: TIMING_B, dist:%d, h_scaler2[%02x]\n", ch, dist, ptiming_b->h_scaler2[dist] );
	printk("ch[%d]: TIMING_B, dist:%d, h_scaler3[%02x]\n", ch, dist, ptiming_b->h_scaler3[dist] );
	printk("ch[%d]: TIMING_B, dist:%d, h_scaler4[%02x]\n", ch, dist, ptiming_b->h_scaler4[dist] );

	printk("ch[%d]: TIMING_B, dist:%d, pn_auto[%02x]\n", ch, dist, ptiming_b->pn_auto[dist] );
	printk("ch[%d]: TIMING_B, dist:%d, comb_mode[%02x]\n", ch, dist, ptiming_b->comb_mode[dist] );
	printk("ch[%d]: TIMING_B, dist:%d, h_pll_op_a[%02x]\n", ch, dist, ptiming_b->h_pll_op_a[dist] );
	printk("ch[%d]: TIMING_B, dist:%d, mem_path[%02x]\n", ch, dist, ptiming_b->mem_path[dist] );
	printk("ch[%d]: TIMING_B, dist:%d, format_set1[%02x]\n", ch, dist, ptiming_b->format_set1[dist] );
	printk("ch[%d]: TIMING_B, dist:%d, format_set2[%02x]\n", ch, dist, ptiming_b->format_set2[dist] );
	printk("ch[%d]: TIMING_B, dist:%d, v_delay[%02x]\n", ch, dist, ptiming_b->v_delay[dist] );
#endif

}

void video_output_channel_sequence_set(struct i2c_client *client, video_output_sequence *vout_seq)
{
	unsigned char vport_out_sel;

	gpio_i2c_write(client, 0xff, 0x01);

	#if 0
	printk("[DRV] vout_seq->port = %x\n", vout_seq->port);
	printk("[DRV] vout_seq->ch01 = %x\n", vout_seq->ch01);
	printk("[DRV] vout_seq->ch23 = %x\n", vout_seq->ch23);
	#endif

	gpio_i2c_write(client, 0xc0 + (vout_seq->port * 2), vout_seq->ch01);
	gpio_i2c_write(client, 0xc1 + (vout_seq->port * 2), vout_seq->ch23);

	if((vout_seq->fmt == AHD20_SD_H960_NT) || (vout_seq->fmt == AHD20_SD_H960_NT))
	{
		vport_out_sel = 0xa0;
	}
	else
	{
		vport_out_sel = 0x58;
	}
	gpio_i2c_write(client, 0xcc + vout_seq->port, vport_out_sel);
}

void video_output_data_out_mode_set(struct i2c_client *client, video_output_data_out_mode *vo_data_out_mode)
{
	unsigned char temp_val = 0x0;

	//  Show/Hide mode is using register Bank 0 0x7A, 7B
	// 		   CH2	  CH1		    CH4    CH3
	//	0x7A [7 : 4][3 : 0]  0x7B [7 : 4][3 : 0]
	gpio_i2c_write(client, 0xFF, 0x00);

	switch(vo_data_out_mode -> ch)
	{
		case CH1 :
		case CH2 :  gpio_i2c_read(client, 0x7A, &temp_val);
					break;
		case CH3 :
		case CH4 :  gpio_i2c_read(client, 0x7B, &temp_val);
					break;
	}

	switch(vo_data_out_mode -> ch)
	{
		case CH1 :
		case CH3 :	temp_val = ((temp_val & 0xF0) | (vo_data_out_mode -> set_val & 0xF));
					break;
		case CH2 :
		case CH4 :  temp_val = ((temp_val & 0x0F) | ((vo_data_out_mode -> set_val & 0xF) << 4));
					break;
	}

	// printk("[%s:%s] : %s >>>> temp_val [ %x ]\n", __FILE__, __LINE__, __FUNCTION__,temp_val);
	switch(vo_data_out_mode -> ch)
	{
		case CH1 :
		case CH2 : gpio_i2c_write(client, 0x7A, temp_val);
				   break;
		case CH3 :
		case CH4 : gpio_i2c_write(client, 0x7B, temp_val);
				   break;
	}
}

void video_output_colorbar_set(struct i2c_client *client)
{
	gpio_i2c_write(client, 0xff, 0x00);
	// colorbar off
	gpio_i2c_write(client, 0x78, 0x88);
	gpio_i2c_write(client, 0x79, 0x88);
	// colorbar on
//	gpio_i2c_write(client, 0x78, 0xab);
//	gpio_i2c_write(client, 0x79, 0xcd);

	gpio_i2c_write(client, 0x68, 0x00);
	gpio_i2c_write(client, 0x69, 0x00);
	gpio_i2c_write(client, 0x6a, 0x00);
	gpio_i2c_write(client, 0x6b, 0x00);

	//  Colorbar on
//	gpio_i2c_write(client, 0xff, 0x05);
//	gpio_i2c_write(client, 0x2c, 0x08);
//	gpio_i2c_write(client, 0xff, 0x06);
//	gpio_i2c_write(client, 0x2c, 0x08);
//	gpio_i2c_write(client, 0xff, 0x07);
//	gpio_i2c_write(client, 0x2c, 0x08);
//	gpio_i2c_write(client, 0xff, 0x08);
//	gpio_i2c_write(client, 0x2c, 0x08);
	// Colorbar off
	gpio_i2c_write(client, 0xff, 0x05);
	gpio_i2c_write(client, 0x2c, 0x00);
	gpio_i2c_write(client, 0xff, 0x06);
	gpio_i2c_write(client, 0x2c, 0x00);
	gpio_i2c_write(client, 0xff, 0x07);
	gpio_i2c_write(client, 0x2c, 0x00);
	gpio_i2c_write(client, 0xff, 0x08);
	gpio_i2c_write(client, 0x2c, 0x00);

	// moving cursor
//	gpio_i2c_write(client, 0xff, 0x05);
//	gpio_i2c_write(client, 0x6a, 0xb0);
//	gpio_i2c_write(client, 0xff, 0x06);
//	gpio_i2c_write(client, 0x6a, 0xb0);
//	gpio_i2c_write(client, 0xff, 0x07);
//	gpio_i2c_write(client, 0x6a, 0xb0);
//	gpio_i2c_write(client, 0xff, 0x08);
//	gpio_i2c_write(client, 0x6a, 0xb0);
}

static int sensor_nvp6158c_s_stream(struct v4l2_subdev *subdev,
	int enable)
{
	int ret = 0;
	struct i2c_client *client = to_client(subdev);

	dprintk("%s(): enable(%d)\n", __func__, enable);
	//dev_info(&client->dev, "%s %d\n", __func__, enable);

	if (enable) {
		ret = sensor_nvp6158c_init(subdev, 1);
		if (ret) {
			dev_err(&client->dev, "stream_on is fail(%d)", ret);
			goto p_err;
		}
	}
	else {
		ret = sensor_nvp6158c_init(subdev, 0);
		if (ret) {
			dev_err(&client->dev, "stream_off is fail(%d)", ret);
			goto p_err;
		}
	}
	return ret;
p_err:
	pr_err("error [%s] enable:%d\n", __func__, enable);
	return ret;
}

static int sensor_nvp6158c_subdev_open(struct v4l2_subdev *sd,
	struct v4l2_subdev_fh *fh)
{
	dprintk("%s()\n", __func__);
	return 0;
}

static int sensor_nvp6158c_subdev_close(struct v4l2_subdev *sd,
	struct v4l2_subdev_fh *fh)
{
	dprintk("%s()\n", __func__);
	return 0;
}

static int sensor_nvp6158c_subdev_registered(struct v4l2_subdev *sd)
{
	dprintk("%s()\n", __func__);
	return 0;
}

static void sensor_nvp6158c_subdev_unregistered(struct v4l2_subdev *sd)
{
	dprintk("%s()\n", __func__);
}

static int sensor_nvp6158c_link_setup(struct media_entity *entity,
		const struct media_pad *local,
		const struct media_pad *remote, u32 flags)
{
	return 0;
}

static int sensor_nvp6158c_s_fmt(struct v4l2_subdev *sd,
			struct v4l2_subdev_pad_config *cfg,
			struct v4l2_subdev_format *fmt)
{
	struct v4l2_mbus_framefmt *mf = &fmt->format;
	dprintk("%s() %dx%d (0x%x) \n", __func__, mf->width, mf->height, mf->code);
	return 0;
}

static int sensor_nvp6158c_enum_fsize(struct v4l2_subdev *sd,
		struct v4l2_subdev_pad_config *cfg,
		struct v4l2_subdev_frame_size_enum *frame)
{
	//YH : IR/Color Sensor 구분
	struct i2c_client *client = to_client(sd); 
	struct nvp6158c_state *state = to_state(sd);
	struct i2c_info *host = v4l2_get_subdev_hostdata(sd);

	dprintk("%s()\n", __func__);
	/*
	//YH : 
	
	if (frame->index >= ARRAY_SIZE(supported_resolutions))
		return -ENODEV;
		
	*/
	//frame->max_width = supported_resolutions[frame->index].width;
  //frame->max_height = supported_resolutions[frame->index].height;

	if (frame->index >= ARRAY_SIZE(sensor_sizes_nvp6158c))
		return -ENODEV;

	frame->max_width = sensor_sizes_nvp6158c[frame->index].width;
	frame->max_height = sensor_sizes_nvp6158c[frame->index].height;

	return 0;
}

static int sensor_nvp6158c_enum_finterval(struct v4l2_subdev *sd,
		struct v4l2_subdev_pad_config *cfg,
		struct v4l2_subdev_frame_interval_enum *frame)
{
	int i;

	dprintk("%s()\n", __func__);
	/*
	for (i = 0; i < ARRAY_SIZE(sensor_sizes_nvp6158c); i++) {
		if ((frame->width == sensor_sizes_nvp6158c[i].width) &&
		    (frame->height == sensor_sizes_nvp6158c[i].height)) {
			frame->interval.numerator = 1;
			//frame->interval.denominator = CM130PC20_FRAMERATE;
			frame->interval.denominator = 30;
			return false;
		}
	}
	*/
	
	for (i = 0; i < ARRAY_SIZE(supported_resolutions); i++) {
		if ((frame->width == supported_resolutions[i].width) &&
		    (frame->height == supported_resolutions[i].height)) {
			frame->interval.numerator = 1;
			frame->interval.denominator =
				supported_resolutions[i].interval[frame->index];
			return false;
		}
	}
	/*
	// YH : 해상도 고정
	frame->interval.numerator = 1;
	frame->interval.denominator = 30;
	return false;
	*/
	return -EINVAL;
}

static int sensor_nvp6158c_s_param(struct v4l2_subdev *sd,
	struct v4l2_streamparm *param)
{
	dprintk("%s()\n", __func__);
	return 0;
}
static struct v4l2_subdev_pad_ops pad_ops = {
	.set_fmt		= sensor_nvp6158c_s_fmt,
	.enum_frame_size	= sensor_nvp6158c_enum_fsize,
	.enum_frame_interval	= sensor_nvp6158c_enum_finterval,
};

static const struct v4l2_subdev_core_ops core_ops = {
	.init		= sensor_nvp6158c_init,
};

static const struct v4l2_subdev_video_ops video_ops = {
	.s_stream = sensor_nvp6158c_s_stream,
	.s_parm = sensor_nvp6158c_s_param,
};

static const struct v4l2_subdev_ops subdev_ops = {
	.core = &core_ops,
	.video = &video_ops,
	.pad	= &pad_ops,
};

static const struct v4l2_subdev_internal_ops internal_ops = {
	.open = sensor_nvp6158c_subdev_open,
	.close = sensor_nvp6158c_subdev_close,
	.registered = sensor_nvp6158c_subdev_registered,
	.unregistered = sensor_nvp6158c_subdev_unregistered,
};

static const struct media_entity_operations media_ops = {
	.link_setup = sensor_nvp6158c_link_setup,
};

int sensor_nvp6158c_probe(struct i2c_client *client,
	const struct i2c_device_id *id)
{
	dprintk("%s(): start\n", __func__);
	int ret, err = 0;
	struct v4l2_subdev *subdev_module;
	struct nvp6158c_state *nvp6158c_state;

	nvp6158c_state = devm_kzalloc(&client->dev, sizeof(struct nvp6158c_state),
		GFP_KERNEL);
	if (!nvp6158c_state) {
		return -ENOMEM;
	}
	
	subdev_module = &nvp6158c_state->subdev;
	snprintf(subdev_module->name, V4L2_SUBDEV_NAME_SIZE,
		"%s", SENSOR_NAME);

	v4l2_i2c_subdev_init(subdev_module, client, &subdev_ops);

	nvp6158c_state->pad.flags = MEDIA_PAD_FL_SOURCE;

	subdev_module->entity.type = MEDIA_ENT_T_V4L2_SUBDEV_SENSOR;
	subdev_module->flags = V4L2_SUBDEV_FL_HAS_DEVNODE;
	subdev_module->internal_ops = &internal_ops;
	subdev_module->entity.ops = &media_ops;

	ret = media_entity_init(&subdev_module->entity, 1,
		&nvp6158c_state->pad, 0);
	if (ret < 0) {
		dev_err(&client->dev, "%s, failed\n", __func__);
		return ret;
	}

	nvp6158c_state->client = client;
	//mutex_init(&nvp6158c_state->i2c_lock);

	dev_info(&client->dev, "(%d)\n", ret);
	return ret;
}

static int sensor_nvp6158c_remove(struct i2c_client *client)
{
	int ret = 0;
	struct v4l2_subdev *subdev = i2c_get_clientdata(client);

	v4l2_device_unregister_subdev(subdev);
	media_entity_cleanup(&subdev->entity);

	return ret;
}

static const struct i2c_device_id sensor_nvp6158c_idt[] = {
	{ SENSOR_NAME, 0 },
	{ }
};

static struct i2c_driver sensor_nvp6158c_driver = {
	.driver = {
		.name	= SENSOR_NAME,
	},
	.probe	= sensor_nvp6158c_probe,
	.remove	= sensor_nvp6158c_remove,
	.id_table = sensor_nvp6158c_idt
};

module_i2c_driver(sensor_nvp6158c_driver);

MODULE_AUTHOR("Younghee Lee <yh202.lee@samsung.com>");
MODULE_DESCRIPTION("Sensor nvp6158c driver");
MODULE_LICENSE("GPL v2");
