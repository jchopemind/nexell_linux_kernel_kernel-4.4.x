/*
* ALSA SoC CX20709 Channel codec driver
*
* Copyright:   (C) 2009/2010 Conexant Systems
*
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 as
* published by the Free Software Foundation.
*
*
*
*************************************************************************
*  Modified Date:  12/01/11
*  File Version:   2.26.35.11
*************************************************************************
*/

#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/module.h>	/* Specifically, a module */
#include <linux/fs.h>
#include <asm/uaccess.h>	/* for get_user and put_user */
//#include <sound/core.h>
//#include <sound/pcm.h>
//#include <sound/pcm_params.h>
#include <sound/soc.h>
//#include <sound/soc-dapm.h>
#include <linux/gpio.h>
#include <linux/slab.h>
#include <linux/delay.h>

//#define DEBUG 1

#include "cxdebug.h"

#if defined(CONFIG_SPI_MASTER)
#include <linux/spi/spi.h>
#endif

// cx2070x ioctl command
#define CX2070X_DEVICE_GAIN_DAC1_LEFT       0x10
#define CX2070X_DEVICE_GAIN_DAC2_RIGHT      0x11
#define CX2070X_DEVICE_GAIN_CLASS_D         0x20
#define CX2070X_DEVICE_GAIN_LINE_ADC1_LEFT  0x30
#define CX2070X_DEVICE_GAIN_LINE_ADC1_RIGHT 0x31
#define CX2070X_DEVICE_GAIN_MIC_ADC2_LEFT   0x32
#define CX2070X_DEVICE_GAIN_MIC_ADC2_RIGHT  0x33
#define CX2070X_DEVICE_GAIN_VOLUME_MUTE     0x34
#define CX2070X_DEVICE_OUTPUT_CONTROL       0x35
#define CX2070X_DEVICE_INPUT_CONTROL        0x36
#define CX2070X_DEVICE_GAIN_LINE1           0x40
#define CX2070X_DEVICE_GAIN_LINE2           0x41
#define CX2070X_DEVICE_GAIN_LINE3           0x42
#define CX2070X_DEVICE_MIC_CONTROL          0x50
#define CX2070X_DEVICE_ROUTE_STREAM3        0x60
#define CX2070X_DEVICE_DSP_INIT             0x70
#define CX2070X_DEVICE_MIX1_IN0_SOURCE      0x80
#define CX2070X_DEVICE_MIX1_IN1_SOURCE      0x81
#define CX2070X_DEVICE_MIX1_IN2_SOURCE      0x82
#define CX2070X_DEVICE_DAC_IN_SOURCE        0x83
#define CX2070X_DEVICE_DSP_PROCESS_EABLE    0x84
#define CX2070X_DEVICE_DEBUG_MSG            0x99

// cx2070x register address
#define REG_GAIN_DAC1_LEFT                  0x100D
#define REG_GAIN_DAC2_RIGHT                 0x100E
#define REG_GAIN_CLASS_D                    0x1011
#define REG_GAIN_LINE_ADC1_LEFT             0x1013
#define REG_GAIN_LINE_ADC1_RIGHT            0x1014
#define REG_GAIN_MIC_ADC2_LEFT              0x1015
#define REG_GAIN_MIC_ADC2_RIGHT             0x1016
#define REG_GAIN_VOLUME_MUTE                0x1018
#define REG_OUTPUT_CONTROL                  0x1019
#define REG_INPUT_CONTROL                   0x101A
#define REG_GAIN_LINE1                      0x101B
#define REG_GAIN_LINE2                      0x101C
#define REG_GAIN_LINE3                      0x101D
#define REG_MIC_CONTROL                     0x101E
#define REG_ROUTE_STREAM3                   0x116E
#define REG_DSP_INIT                        0x117D
#define REG_MIX1_IN0_SOURCE                 0x1188
#define REG_MIX1_IN1_SOURCE                 0x1189
#define REG_MIX1_IN2_SOURCE                 0x118A
#define REG_DAC_IN_SOURCE                   0x117F
#define REG_DSP_PROCESS_EABLE               0x117A

//SKJ 20180501 : must be change (long -> int)
//               because long is 8byte in 64bit enviroment (long is 4byte in TCC)

/*
*
 * Is the device open right now? Used to prevent
 * concurent access into the same device
 */
static int Device_Open = 0;
extern int CX_AUDDRV_VERSION;
struct i2c_client *g_codec = NULL;

// SKJ_DEBUG
static int debug_cx2070x	   = 0;
#define dprintk(msg...)	if(debug_cx2070x) { printk( "cx2070x> " msg); }

/*
 * This is called whenever a process attempts to open the device file
 */
static int cxdbg_dev_open(struct inode *inode, struct file *file)
{
    dprintk(KERN_INFO "%s(): (%p)\n",__func__, file);

    /*
    * We don't want to talk to two processes at the same time
    */
#if 0 //SKJ 20150908 : permit multi open    
    if (Device_Open)
        return -EBUSY;
#endif        

    Device_Open++;
    /*
    * Initialize the message
    */

   // try_module_get(THIS_MODULE);
    return 0;
}

/*
 * This is called whenever a process attempts to open the device file
 */
static int cxdbg_dev_release(struct inode *inode, struct file *file)
{
    dprintk(KERN_INFO "%s(): (%p)\n",__func__, file);

    Device_Open--;
    /*
    * Initialize the message
    */

    return 0;
}

static ssize_t cxdbg_dev_read(struct file *file, char __user * buffer, size_t length, loff_t * offset)
{
    dprintk(KERN_INFO "%s()\n",__func__);
	  return 0;
}

static ssize_t cxdbg_dev_write(struct file *file, const char __user * buffer, size_t length, loff_t * offset)
{
    char *reg_buf;
	  unsigned char val;
  	unsigned char data[3] = {0, 0, 0};

    if(length > 3)
    {
        printk(KERN_ERR "\n%s(): over length = %d!\n", __func__, length);
        return -EINVAL;
    }

    reg_buf = kmalloc(length, GFP_KERNEL);
    if (!reg_buf)
    {
        printk(KERN_ERR "\n%s(): kmalloc() failed!\n",__func__);
        return -EINVAL;
    }

		if(copy_from_user(reg_buf, buffer, length))
		{
        printk(KERN_ERR "\n%s(): copy from user\n",__func__);
    		kfree(reg_buf);
  			return -EINVAL;
		}

    memcpy(data, reg_buf, length);
  	kfree(reg_buf);
    if(length == 2)
    {
      	if(i2c_master_send(g_codec, data, 2) != 2)
      	{
           printk(KERN_ERR "\n%s(): write error for read!!!! \n",__func__);
           return -EINVAL;
      	}

      	if(i2c_master_recv(g_codec, &val, 1) != 1)
      	{
      		printk(KERN_ERR "\n%s(): read error!!!! \n",__func__);
      		return -EINVAL;
      	}

        printk(KERN_INFO "\n%s(): read 0x%04x = 0x%02x\n\n",__func__, (data[0]<<8 | data[1]), val);
    }
    else
    {
    		if(i2c_master_send(g_codec, data, 3) !=3)
      	{
           printk(KERN_ERR "\n%s(): write error!!!! \n",__func__);
           return -EINVAL;
      	}

        printk(KERN_INFO "\n%s(): write 0x%04x = 0x%02x\n\n",__func__, (data[0]<<8 | data[1]), data[2]);
    }

	  return length;
}

static int codec_reg_write(unsigned short reg_addr, unsigned char reg_val)
{
  	unsigned char data[3] = {0, 0, 0};

    dprintk(KERN_INFO "%s(): codec_reg_write\n",__func__);

    BUG_ON(!g_codec);

		data[0] = reg_addr>>8;
		data[1] = (unsigned char)reg_addr&0xff;
		data[2] = reg_val;

    dprintk(KERN_INFO "%s(): 0x%04x = 0x%02x\n\n",__func__, (data[0]<<8 | data[1]), data[2]);

		if(i2c_master_send(g_codec, data, 3) != 3)
  	{
       printk(KERN_ERR "\n%s(): write error!!!! \n",__func__);
       return -EINVAL;
  	}

    return 0;
}

long cxdbg_dev_ioctl(struct file * file, unsigned int cmd, unsigned long arg)
{
  	int val=0;
    long err = 0;

    dprintk(KERN_INFO "%s(): ioctl, cmd=0x%02x, arg=0x%02lx\n",__func__, cmd, arg);

    /*
    * Switch according to the ioctl called
    */
	switch (cmd) {
  	case CX2070X_DEVICE_GAIN_DAC1_LEFT:
  	{
  		if (copy_from_user((void *)&val, (void __user *)arg, sizeof(int)))
  		{
    		pr_err(KERN_ERR "\n%s(): [ERR] invalid val(%d)\n\n",__func__, _IOC_NR(cmd));
				return -EINVAL;
  		}

  		if(val>=0x00 && val<=0xFF)
  		{
       	dprintk(KERN_INFO "\n%s(): GAIN_DAC1_LEFT - 0x%x\n\n",__func__,val);
       	codec_reg_write(REG_GAIN_DAC1_LEFT, val);
      }
  		else
  		{
       	printk(KERN_ERR "\n%s(): [ERR] GAIN_DAC1_LEFT - val(0x%x) over range\n\n",__func__,val);
				return -EINVAL;
      }
  	  break;
  	}
  	case CX2070X_DEVICE_GAIN_DAC2_RIGHT:
  	{
  		if (copy_from_user((void *)&val, (void __user *)arg, sizeof(int)))
  		{
    		pr_err("\n%s(): [ERR] invalid val(%d)\n\n",__func__, _IOC_NR(cmd));
				return -EINVAL;
  		}

  		if(val>=0x00 && val<=0xFF)
  		{
       	dprintk(KERN_INFO "\n%s(): GAIN_DAC2_RIGHT - 0x%x\n\n",__func__,val);
       	codec_reg_write(REG_GAIN_DAC2_RIGHT, val);
      }
  		else
  		{
       	printk(KERN_ERR "\n%s(): [ERR] GAIN_DAC2_RIGHT - val(0x%x) over range\n\n",__func__,val);
				return -EINVAL;
      }
  		break;
 		}
  	case CX2070X_DEVICE_GAIN_CLASS_D:
  	{
  		if (copy_from_user((void *)&val, (void __user *)arg, sizeof(int)))
  		{
    		pr_err("\n%s(): [ERR] invalid val(%d)\n\n",__func__, _IOC_NR(cmd));
				return -EINVAL;
  		}

  		if(val>=0x00 && val<=0xFF)
  		{
       	dprintk(KERN_INFO "\n%s(): GAIN_CLASS_D - 0x%x\n\n",__func__,val);
       	codec_reg_write(REG_GAIN_CLASS_D, val);
      }
      else
  		{
       	printk(KERN_ERR "\n%s(): [ERR] GAIN_CLASS_D - val(0x%x) over range\n\n",__func__,val);
				return -EINVAL;
      }
  		break;
 		}
  	case CX2070X_DEVICE_GAIN_LINE_ADC1_LEFT:
  	{
  		if (copy_from_user((void *)&val, (void __user *)arg, sizeof(int)))
  		{
    		pr_err("\n%s(): [ERR] invalid val(%d)\n\n",__func__, _IOC_NR(cmd));
				return -EINVAL;
  		}

  		if(val>=0x00 && val<=0xFF)
  		{
       	dprintk(KERN_INFO "\n%s(): GAIN_LINE_ADC1_LEFT - 0x%x\n\n",__func__,val);
       	codec_reg_write(REG_GAIN_LINE_ADC1_LEFT, val);
      }
      else
  		{
       	printk(KERN_ERR "\n%s(): [ERR] GAIN_LINE_ADC1_LEFT - val(0x%x) over range\n\n",__func__,val);
				return -EINVAL;
      }
  	  break;
  	}
  	case CX2070X_DEVICE_GAIN_LINE_ADC1_RIGHT:
  	{
  		if (copy_from_user((void *)&val, (void __user *)arg, sizeof(int)))
  		{
    		pr_err("\n%s(): [ERR] invalid val(%d)\n\n",__func__, _IOC_NR(cmd));
				return -EINVAL;
  		}

  		if(val>=0x00 && val<=0xFF)
  		{
       	dprintk(KERN_INFO "\n%s(): GAIN_LINE_ADC1_RIGHT - 0x%x\n\n",__func__,val);
       	codec_reg_write(REG_GAIN_LINE_ADC1_RIGHT, val);
      }
      else
  		{
       	printk(KERN_ERR "\n%s(): [ERR] GAIN_LINE_ADC1_RIGHT - val(0x%x) over range\n\n",__func__,val);
				return -EINVAL;
      }
  		break;
 		}
  	case CX2070X_DEVICE_GAIN_MIC_ADC2_LEFT:
  	{
  		if (copy_from_user((void *)&val, (void __user *)arg, sizeof(int)))
  		{
    		pr_err("\n%s(): [ERR] invalid val(%d)\n\n",__func__, _IOC_NR(cmd));
				return -EINVAL;
  		}

  		if(val>=0x00 && val<=0xFF)
  		{
       	dprintk(KERN_INFO "\n%s(): GAIN_MIC_ADC2_LEFT - 0x%x\n\n",__func__,val);
       	codec_reg_write(REG_GAIN_MIC_ADC2_LEFT, val);
      }
      else
  		{
       	printk(KERN_ERR "\n%s(): [ERR] GAIN_MIC_ADC2_LEFT - val(0x%x) over range\n\n",__func__,val);
				return -EINVAL;
      }
  		break;
 		}
  	case CX2070X_DEVICE_GAIN_MIC_ADC2_RIGHT:
  	{
  		if (copy_from_user((void *)&val, (void __user *)arg, sizeof(int)))
  		{
    		pr_err("\n%s(): [ERR] invalid val(%d)\n\n",__func__, _IOC_NR(cmd));
				return -EINVAL;
  		}

  		if(val>=0x00 && val<=0xFF)
  		{
       	dprintk(KERN_INFO "\n%s(): GAIN_MIC_ADC2_RIGHT - 0x%x\n\n",__func__,val);
       	codec_reg_write(REG_GAIN_MIC_ADC2_RIGHT, val);
      }
      else
  		{
       	printk(KERN_ERR "\n%s(): [ERR] GAIN_MIC_ADC2_RIGHT - val(0x%x) over range\n\n",__func__,val);
				return -EINVAL;
      }
  		break;
 		}
  	case CX2070X_DEVICE_GAIN_VOLUME_MUTE:
  	{
  		if (copy_from_user((void *)&val, (void __user *)arg, sizeof(int)))
  		{
    		pr_err("\n%s(): [ERR] invalid val(%d)\n\n",__func__, _IOC_NR(cmd));
				return -EINVAL;
  		}

  		if(val>=0x00 && val<=0xFF)
  		{
       	dprintk(KERN_INFO "\n%s(): GAIN_VOLUME_MUTE - 0x%x\n\n",__func__,val);
       	codec_reg_write(REG_GAIN_VOLUME_MUTE, val);
      }
      else
  		{
       	printk(KERN_ERR "\n%s(): [ERR] GAIN_VOLUME_MUTE - val(0x%x) over range\n\n",__func__,val);
				return -EINVAL;
      }
  		break;
 		}
  	case CX2070X_DEVICE_OUTPUT_CONTROL:
  	{
  		if (copy_from_user((void *)&val, (void __user *)arg, sizeof(int)))
  		{
    		pr_err("\n%s(): [ERR] invalid val(%d)\n\n",__func__, _IOC_NR(cmd));
				return -EINVAL;
  		}

  		if(val>=0x00 && val<=0xFF)
  		{
       	dprintk(KERN_INFO "\n%s(): OUTPUT_CONTROL - 0x%x\n\n",__func__,val);
       	codec_reg_write(REG_OUTPUT_CONTROL, val);
      }
      else
  		{
       	printk(KERN_ERR "\n%s(): [ERR] OUTPUT_CONTROL- val(0x%x) over range\n\n",__func__,val);
				return -EINVAL;
      }
  		break;
 		}
  	case CX2070X_DEVICE_INPUT_CONTROL:
  	{
  		if (copy_from_user((void *)&val, (void __user *)arg, sizeof(int)))
  		{
    		pr_err("\n%s(): [ERR] invalid val(%d)\n\n",__func__, _IOC_NR(cmd));
				return -EINVAL;
  		}

  		if(val>=0x00 && val<=0xFF)
  		{
       	dprintk(KERN_INFO "\n%s(): INPUT_CONTROL - 0x%x\n\n",__func__,val);
       	codec_reg_write(REG_INPUT_CONTROL, val);
      }
      else
  		{
       	printk(KERN_ERR "\n%s(): [ERR] INPUT_CONTROL- val(0x%x) over range\n\n",__func__,val);
				return -EINVAL;
      }
  		break;
 		}
  	case CX2070X_DEVICE_GAIN_LINE1:
  	{
  		if (copy_from_user((void *)&val, (void __user *)arg, sizeof(int)))
  		{
    		pr_err("\n%s(): [ERR] invalid val(%d)\n\n",__func__, _IOC_NR(cmd));
				return -EINVAL;
  		}

  		if(val>=0x00 && val<=0xFF)
  		{
       	dprintk(KERN_INFO "\n%s(): GAIN_LINE1 - 0x%x\n\n",__func__,val);
       	codec_reg_write(REG_GAIN_LINE1, val);
      }
      else
  		{
       	printk(KERN_ERR "\n%s(): [ERR] GAIN_LINE1 - val(0x%x) over range\n\n",__func__,val);
				return -EINVAL;
      }
  		break;
 		}
  	case CX2070X_DEVICE_GAIN_LINE2:
  	{
  		if (copy_from_user((void *)&val, (void __user *)arg, sizeof(int)))
  		{
    		pr_err("\n%s(): [ERR] invalid val(%d)\n\n",__func__, _IOC_NR(cmd));
				return -EINVAL;
  		}

  		if(val>=0x00 && val<=0xFF)
  		{
       	dprintk(KERN_INFO "\n%s(): GAIN_LINE2 - 0x%x\n\n",__func__,val);
       	codec_reg_write(REG_GAIN_LINE2, val);
      }
      else
  		{
       	printk(KERN_ERR "\n%s(): [ERR] GAIN_LINE2 - val(0x%x) over range\n\n",__func__,val);
				return -EINVAL;
      }
  		break;
 		}
  	case CX2070X_DEVICE_GAIN_LINE3:
  	{
  		if (copy_from_user((void *)&val, (void __user *)arg, sizeof(int)))
  		{
    		pr_err("\n%s(): [ERR] invalid val(%d)\n\n",__func__, _IOC_NR(cmd));
				return -EINVAL;
  		}

  		if(val>=0x00 && val<=0xFF)
  		{
       	dprintk(KERN_INFO "\n%s(): GAIN_LINE3 - 0x%x\n\n",__func__,val);
       	codec_reg_write(REG_GAIN_LINE3, val);
      }
      else
  		{
       	printk(KERN_ERR "\n%s(): [ERR] GAIN_LINE3 - val(0x%x) over range\n\n",__func__,val);
				return -EINVAL;
      }
  		break;
 		}
  	case CX2070X_DEVICE_MIC_CONTROL:
  	{
  		if (copy_from_user((void *)&val, (void __user *)arg, sizeof(int)))
  		{
    		pr_err("\n%s(): [ERR] invalid val(%d)\n\n",__func__, _IOC_NR(cmd));
				return -EINVAL;
  		}

  		if(val>=0x00 && val<=0xFF)
  		{
       	dprintk(KERN_INFO "\n%s(): MIC_CONTROL - 0x%x\n\n",__func__,val);
       	codec_reg_write(REG_MIC_CONTROL, val);
      }
      else
  		{
       	printk(KERN_ERR "\n%s(): [ERR] MIC_CONTROL - val(0x%x) over range\n\n",__func__,val);
				return -EINVAL;
      }
  		break;
 		}
  	case CX2070X_DEVICE_ROUTE_STREAM3:
  	{
  		if (copy_from_user((void *)&val, (void __user *)arg, sizeof(int)))
  		{
    		pr_err("\n%s(): [ERR] invalid val(%d)\n\n",__func__, _IOC_NR(cmd));
				return -EINVAL;
  		}

  		if(val>=0x00 && val<=0xFF)
  		{
       	dprintk(KERN_INFO "\n%s(): ROUTE_STREAM3 - 0x%x\n\n",__func__,val);
       	codec_reg_write(REG_ROUTE_STREAM3, val);
      }
      else
  		{
       	printk(KERN_ERR "\n%s(): [ERR] ROUTE_STREAM3 - val(0x%x) over range\n\n",__func__,val);
				return -EINVAL;
      }
  		break;
 		}
  	case CX2070X_DEVICE_DSP_INIT:
  	{
  		if (copy_from_user((void *)&val, (void __user *)arg, sizeof(int)))
  		{
    		pr_err("\n%s(): [ERR] invalid val(%d)\n\n",__func__, _IOC_NR(cmd));
				return -EINVAL;
  		}

  		if(val>=0x00 && val<=0xFF)
  		{
       	dprintk(KERN_INFO "\n%s(): DSP_INIT - 0x%x\n\n",__func__,val);
       	codec_reg_write(REG_DSP_INIT, val);
      }
      else
  		{
       	printk(KERN_ERR "\n%s(): [ERR] DSP_INIT - val(0x%x) over range\n\n",__func__,val);
				return -EINVAL;
      }
  		break;
 		}
  	case CX2070X_DEVICE_MIX1_IN0_SOURCE:
  	{
  		if (copy_from_user((void *)&val, (void __user *)arg, sizeof(int)))
  		{
    		pr_err("\n%s(): [ERR] invalid val(%d)\n\n",__func__, _IOC_NR(cmd));
				return -EINVAL;
  		}

  		if(val>=0x00 && val<=0xFF)
  		{
       	dprintk(KERN_INFO "\n%s(): MIX1_IN0_SOURCE - 0x%x\n\n",__func__,val);
      	codec_reg_write(REG_MIX1_IN0_SOURCE, val);
      }
      else
  		{
       	printk(KERN_ERR "\n%s(): [ERR] MIX0_IN0_SOURCE - val(0x%x) over range\n\n",__func__,val);
				return -EINVAL;
      }
  		break;
 		}
  	case CX2070X_DEVICE_MIX1_IN1_SOURCE:
  	{
  		if (copy_from_user((void *)&val, (void __user *)arg, sizeof(int)))
  		{
    		pr_err("\n%s(): [ERR] invalid val(%d)\n\n",__func__, _IOC_NR(cmd));
				return -EINVAL;
  		}

  		if(val>=0x00 && val<=0xFF)
  		{
       	dprintk(KERN_INFO "\n%s(): MIX1_IN1_SOURCE - 0x%x\n\n",__func__,val);
       	codec_reg_write(REG_MIX1_IN1_SOURCE, val);
      }
      else
  		{
       	printk(KERN_ERR "\n%s(): [ERR] MIX0_IN1_SOURCE - val(0x%x) over range\n\n",__func__,val);
				return -EINVAL;
      }
  		break;
 		}
  	case CX2070X_DEVICE_MIX1_IN2_SOURCE:
  	{
  		if (copy_from_user((void *)&val, (void __user *)arg, sizeof(int)))
  		{
    		pr_err("\n%s(): [ERR] invalid val(%d)\n\n",__func__, _IOC_NR(cmd));
				return -EINVAL;
  		}

  		if(val>=0x00 && val<=0xFF)
  		{
       	dprintk(KERN_INFO "\n%s(): MIX1_IN2_SOURCE - 0x%x\n\n",__func__,val);
       	codec_reg_write(REG_MIX1_IN2_SOURCE, val);
      }
      else
  		{
       	printk(KERN_ERR "\n%s(): [ERR] MIX0_IN2_SOURCE - val(0x%x) over range\n\n",__func__,val);
				return -EINVAL;
      }
  		break;
 		}
  	case CX2070X_DEVICE_DAC_IN_SOURCE:
  	{
  		if (copy_from_user((void *)&val, (void __user *)arg, sizeof(int)))
  		{
    		pr_err("\n%s(): [ERR] invalid val(%d)\n\n",__func__, _IOC_NR(cmd));
				return -EINVAL;
  		}

  		if(val>=0x00 && val<=0xFF)
  		{
       	dprintk(KERN_INFO "\n%s(): DAC_IN_SOURCE - 0x%x\n\n",__func__,val);
       	codec_reg_write(REG_DAC_IN_SOURCE, val);
      }
      else
  		{
       	printk(KERN_ERR "\n%s(): [ERR] DAC_IN_SOURCE - val(0x%x) over range\n\n",__func__,val);
				return -EINVAL;
      }
  		break;
 		}
  	case CX2070X_DEVICE_DSP_PROCESS_EABLE:
  	{
  		if (copy_from_user((void *)&val, (void __user *)arg, sizeof(int)))
  		{
    		pr_err("\n%s(): [ERR] invalid val(%d)\n\n",__func__, _IOC_NR(cmd));
				return -EINVAL;
  		}

  		if(val>=0x00 && val<=0xFF)
  		{
       	dprintk(KERN_INFO "\n%s(): DSP_PROCESS_EABLE - 0x%x\n\n",__func__,val);
       	codec_reg_write(REG_DSP_PROCESS_EABLE, val);
      }
      else
  		{
       	printk(KERN_ERR "\n%s(): [ERR] DSP_PROCESS_EABLE - val(0x%x) over range\n\n",__func__,val);
				return -EINVAL;
      }
  		break;
 		}
  	case CX2070X_DEVICE_DEBUG_MSG:
  	{
  		if (copy_from_user((void *)&val, (void __user *)arg, sizeof(int)))
  		{
    		pr_err("\n%s(): [ERR] invalid val(%d)\n\n",__func__, _IOC_NR(cmd));
				return -EINVAL;
  		}

     	dprintk(KERN_INFO "%s(): Debug msg (%d)\n\n",__func__,val);
			debug_cx2070x = val;
  		break;
 		}
  	default:
  		pr_err("\n%s(): [ERR] invalid cmd(%d)\n\n",__func__, _IOC_NR(cmd));
			return -EINVAL;
	}

    return err;
}

static const struct file_operations cxdbg_dev_fops = {
    .owner          = THIS_MODULE,
  	.read           = cxdbg_dev_read,
  	.write          = cxdbg_dev_write,
    //.unlocked_ioctl = cxdbg_dev_ioctl,
	.compat_ioctl = cxdbg_dev_ioctl,
    .open           = cxdbg_dev_open,
    .release        = cxdbg_dev_release,
};

static struct miscdevice cxdbg_dev_device =
{
  MISC_DYNAMIC_MINOR,
  CXDBG_DEVICE_NAME,
  &cxdbg_dev_fops,
};

/*
* Initialize the module - Register the character device
*/
int cxdbg_dev_init(struct i2c_client *i2c)
{
    int err;

    dprintk(KERN_INFO "%s()\n",__func__);

    g_codec = i2c;

  	err = misc_register(&cxdbg_dev_device);
    if (err < 0) {
        printk(KERN_ERR "%s(): Driver Initialisation failed\n",__func__);
        return err;
    }

    return 0;
}

void cxdbg_dev_exit(void)
{
    dprintk(KERN_INFO "%s()\n",__func__);
  	misc_deregister(&cxdbg_dev_device);
}


MODULE_AUTHOR("Simon Ho<simon.ho@conexant.com");
MODULE_DESCRIPTION("debug driver");
MODULE_LICENSE("GPL");

