#include <linux/module.h>
#include <linux/init.h>
#include <linux/err.h>
#include <linux/slab.h>
#include <linux/mutex.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/err.h>
#include <linux/of.h>
#include <linux/sec_sysfs.h>
#include <linux/of_gpio.h>
#include <linux/gpio.h>
#include <linux/delay.h>

#include <linux/miscdevice.h>
#include <linux/types.h>
#include <linux/ioctl.h>
#include <linux/input.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/workqueue.h>

#include <asm/uaccess.h>

#define RELEASED      0
#define PRESSED       1

#define TCHKEY_CHECK_COUNT 15
#define DETSIG_CHECK_COUNT 15

#define TCHKEY_CHECK_DELAY 10
#define DETSIG_CHECK_DELAY 10

// HA, Zigbee
#define MISC_SET_SLAVE_BOOT_OUT    		0x10
#define MISC_CTL_SLAVE_RST_OUT     		0x11
#define MISC_SET_ZIGBEE_BOOT_OUT   		0x12
#define MISC_SET_ZIGBEE_RST_OUT    		0x13

// ETC Device
#define MISC_SET_TOUCH_RST_OUT     		0x20
#define MISC_SET_CAMERA_RST_OUT    		0x21
#define MISC_SET_TVP5150_RST_OUT   		0x22

// Sound
#define MISC_CTL_ZARLINK_RST_OUT   		0x30
#define	MISC_CTL_ZARLINK_CLK			0x31
#define MISC_SET_PCM_SELECT        		0x32

// Door
#define	MISC_SET_DOOR_POWER_ENABLE		0x40
#define	MISC_GET_DOOR_CALL_DET			0x41
#define	MISC_GET_DOOR_IR_DET			0x42

// USB, Uart
#define MISC_SET_USB_MODE				0x50
#define MISC_GET_USB_MODE				0x51
#define MISC_CTL_UART_DEBUG_ENABLE		0x52

// Interrupt
#define MISC_GET_GPIO_DOOR_CALL_DET		0x60
#define MISC_GET_GPIO_DOOR_IR_DET		0x61

// Debug, Test
#define MISC_TEST_DEBUG_MSG				0x90
#define MISC_TEST_SET					0x9E	// KJW only for test
#define MISC_TEST_GET					0x9F	// KJW only for test


#define SLAVE_BOOT_NORMAL		0
#define SLAVE_BOOT_UPGRADE		1
#define SLAVE_RESET_HOLD		0
#define SLAVE_RESET_RELEASE		1

#define ZIGBEE_BOOT_NORMAL		1
#define ZIGBEE_BOOT_UPGRADE		0
#define ZIGBEE_RESET_HOLD		0
#define ZIGBEE_RESET_RELEASE	1

static irqreturn_t call_key_irq_handler(int irq, void *dev_id);
static irqreturn_t det_ir_irq_handler(int irq, void *dev_id);

struct sds_misc_platform_data {
	struct device *sec_sysfs;
	/*
	struct gpio_desc *gpio_haReset;
	*/
	int gpio_haReset;
	int gpio_haBootSel;
	int gpio_zbReset;
	int gpio_zbBootSel;
	int gpio_pcmSelect;
	int gpio_doorPowerEnable;
	int gpio_doorCallDet;
	int gpio_doorIrDet;
	int gpio_tspReset;
	int gpio_zarlinkMode;
	int gpio_zarlinkReset;
	int gpio_powerSwHold;
};

struct input_dev *input_dev;

struct sds_misc_platform_data *pdata;
static int g_is_device_open = 0;
static int testValue = -1;
static int sds_misc_debug = 0;
static int is_call_key_processing = 0;
static int is_ir_det_processing = 0;

void func_workqueue_det_ir(struct work_struct *data);
DECLARE_WORK(det_ir_wq, func_workqueue_det_ir);

void func_workqueue_call_key(struct work_struct *data);
DECLARE_WORK(call_key_wq, func_workqueue_call_key);

//SKJ 20180501 : for Door long-run test
enum { AUTO_CALL_STOP = 0, AUTO_CALL_START = 1, AUTO_CALL_RUN = 2 };

static int gndoor_call_state = AUTO_CALL_STOP;
static int gndoor_call_count = 0;
static struct timer_list door_call_wakeup_timer;
void func_door_call_wakeup_timer(unsigned long arg)
{
  int door_call_gpio_value = 0;
  
  door_call_gpio_value = gpio_get_value(pdata->gpio_doorCallDet);
	printk("%s(): Call gpio value = %d... 25s period\n",__func__, door_call_gpio_value);

  if(door_call_gpio_value == 1)
  {
  	schedule_work(&call_key_wq);
	printk("%s(): auto test count = %d\n",__func__, ++gndoor_call_count);
  }

  if(gndoor_call_state == AUTO_CALL_RUN)
  {
  	door_call_wakeup_timer.expires = get_jiffies_64() + (25*HZ);
  	add_timer(&door_call_wakeup_timer);
  }
}

// call key
static irqreturn_t call_key_irq_handler(int irq, void *dev_id){

	if(!is_call_key_processing)
	{
		is_call_key_processing = 1;
		if(sds_misc_debug>0) {
			printk("\n[call_key_irq_handler] EXINT_CALL processing\n");
		}
		schedule_work(&call_key_wq);
	}
	
	return IRQ_HANDLED;
}

void func_workqueue_call_key(struct work_struct *data)
{	
	int initial_gpio_det, cur_gpio_det = -1;
	int i = 0;
		
	if(sds_misc_debug>1) {
		printk("[func_workqueue_call_key] func_workqueue_call_key\n");
	}
	
	mdelay(1);
	
	initial_gpio_det = gpio_get_value(pdata->gpio_doorCallDet);
	if(sds_misc_debug>1) {
		printk("[func_workqueue_call_key] initial_gpio_det = %d\n", initial_gpio_det);
	}
	for(i=0; i<TCHKEY_CHECK_COUNT; i++)
	{
		mdelay(TCHKEY_CHECK_DELAY);
		cur_gpio_det = gpio_get_value(pdata->gpio_doorCallDet);
		if(sds_misc_debug>1) {
			printk("[func_workqueue_call_key] [try:%d] cur_gpio_det = %d\n", i, cur_gpio_det);
		}
		if(cur_gpio_det != initial_gpio_det)
		{
			if(sds_misc_debug>1) {
				printk("[func_workqueue_call_key] cur_gpio_det != initial_gpio_det -> stop process\n");
			}
			break;
		}
	}
	
	if(i >= TCHKEY_CHECK_COUNT)
	{
		if(initial_gpio_det == 1)
		{
			if(sds_misc_debug>0) {
				printk("[func_workqueue_call_key] call key pressed\n");
			}
			input_report_key(input_dev, KEY_F1, PRESSED);
			input_sync(input_dev);
			input_report_key(input_dev, KEY_F1, RELEASED);
			input_sync(input_dev);
		}
	}
	
	is_call_key_processing = 0;
}

// ir key
static irqreturn_t det_ir_irq_handler(int irq, void *dev_id){

	if(!is_ir_det_processing)
	{
		is_ir_det_processing = 1;
		if(sds_misc_debug>0) {
			printk("\n[det_ir_irq_handler] EXINT_IR processing\n");
		}
		schedule_work(&det_ir_wq);
	}
	
	return IRQ_HANDLED;
}

void func_workqueue_det_ir(struct work_struct *data)
{	
	int initial_gpio_det, cur_gpio_det = -1;
	int i = 0;
		
	if(sds_misc_debug>1) {
		printk("[func_workqueue_det_ir] func_workqueue_det_ir\n");
	}
	
	mdelay(1);
	
	initial_gpio_det = gpio_get_value(pdata->gpio_doorIrDet);
	if(sds_misc_debug>1) {
		printk("[func_workqueue_det_ir] initial_gpio_det = %d\n", initial_gpio_det);
	}
	for(i=0; i<TCHKEY_CHECK_COUNT; i++)
	{
		mdelay(TCHKEY_CHECK_DELAY);
		cur_gpio_det = gpio_get_value(pdata->gpio_doorIrDet);
		if(sds_misc_debug>1) {
			printk("[func_workqueue_det_ir] [try:%d] cur_gpio_det = %d\n", i, cur_gpio_det);
		}
		if(cur_gpio_det != initial_gpio_det)
		{
			if(sds_misc_debug>1) {
				printk("[func_workqueue_det_ir] cur_gpio_det != initial_gpio_det -> stop process\n");
			}
			break;
		}
	}
	
	if(i >= TCHKEY_CHECK_COUNT)
	{
		if(initial_gpio_det == 1)
		{
			if(sds_misc_debug>0) {
				printk("[func_workqueue_det_ir] door ir key pressed\n");
			}
			input_report_key(input_dev, KEY_F2, PRESSED);
			input_sync(input_dev);
			input_report_key(input_dev, KEY_F2, RELEASED);
			input_sync(input_dev);
		}
	}
	
	is_ir_det_processing = 0;
}

static int device_open(struct inode *inode, struct file *file)
{
  if(sds_misc_debug>1) printk("%s(): (%p)\n",__func__, file);

	g_is_device_open++;

	return 0;
}

static int device_release(struct inode *inode, struct file *file)
{
  if(sds_misc_debug>1) printk("%s(): (%p,%p)\n",__func__, inode, file);

	g_is_device_open--;

	return 0;
}

static ssize_t device_read(struct file *file, char * buffer, size_t length, loff_t * offset)
{
	return 0;
}

static ssize_t device_write(struct file *file, const char * buffer, size_t length, loff_t * offset)
{
	return 0;
}

static long device_ioctl (struct file *filp, unsigned int cmd, unsigned long arg)
{
	int ret=0, val=0;

  if(sds_misc_debug>1) printk("%s(): cmd %d\n",__func__,_IOC_NR(cmd));
	
	switch (cmd) {

  	case MISC_SET_SLAVE_BOOT_OUT:
  	{
  		if (copy_from_user((void *)&val, (void __user *)arg, sizeof(int)))
  		{
    		printk("%s(): [ERR] invalid val %d\n",__func__, _IOC_NR(cmd));
			return -EINVAL;
  		}
		//if (!IS_ERR(pdata->gpio_haBootSel))
		if (pdata->gpio_haBootSel >= 0)
		{
		  if(sds_misc_debug>0) printk("%s(): Slave boot set(%d)\n",__func__,val);
			//gpiod_set_value(pdata->gpio_haBootSel, val);
			gpio_set_value(pdata->gpio_haBootSel, val);
		}
		else
			printk("%s(): gpio configure error\n",__func__);
  	  break;
  	}

  	case MISC_CTL_SLAVE_RST_OUT:
  	{
  		if (copy_from_user((void *)&val, (void __user *)arg, sizeof(int)))
  		{
    		printk("%s(): [ERR] invalid val %d\n",__func__, _IOC_NR(cmd));
			return -EINVAL;
  		}
		//if (!IS_ERR(pdata->gpio_haReset))
		if (pdata->gpio_haReset >= 0)
		{
		  if(sds_misc_debug>0) printk("%s(): Slave reset(%d)\n",__func__,val);
			//gpiod_set_value(pdata->gpio_haReset, SLAVE_RESET_HOLD);
			gpio_set_value(pdata->gpio_haReset, SLAVE_RESET_HOLD);
			mdelay(100);
			//gpiod_set_value(pdata->gpio_haReset, SLAVE_RESET_RELEASE);
			gpio_set_value(pdata->gpio_haReset, SLAVE_RESET_RELEASE);
		}
		else
			printk("%s(): gpio configure error\n",__func__);
  		break;
 	}
	
	case MISC_SET_ZIGBEE_BOOT_OUT:
  	{
  		if (copy_from_user((void *)&val, (void __user *)arg, sizeof(int)))
  		{
    		printk("%s(): [ERR] invalid val %d\n",__func__, _IOC_NR(cmd));
			return -EINVAL;
  		}
		if (pdata->gpio_zbBootSel >= 0)
		{
		  if(sds_misc_debug>0) printk("%s(): Zigbee boot set(%d)\n",__func__,val);
			gpio_set_value(pdata->gpio_zbBootSel, val);
		}
		else
			printk("%s(): gpio configure error\n",__func__);
  	  break;
  	}

  	case MISC_SET_ZIGBEE_RST_OUT:
  	{
  		if (copy_from_user((void *)&val, (void __user *)arg, sizeof(int)))
  		{
    		printk("%s(): [ERR] invalid val %d\n",__func__, _IOC_NR(cmd));
			return -EINVAL;
  		}
		if (pdata->gpio_zbReset >= 0)
		{
		  if(sds_misc_debug>0) printk("%s(): Zigbee reset(%d)\n",__func__,val);
			gpio_set_value(pdata->gpio_zbReset, ZIGBEE_RESET_HOLD);
			mdelay(100);
			gpio_set_value(pdata->gpio_zbReset, ZIGBEE_RESET_RELEASE);
		}
		else
			printk("%s(): gpio configure error\n",__func__);
  		break;
 	}
	
	case MISC_CTL_ZARLINK_RST_OUT:
  	{
  		if (copy_from_user((void *)&val, (void __user *)arg, sizeof(int)))
  		{
    		printk("%s(): [ERR] invalid val %d\n",__func__, _IOC_NR(cmd));
			return -EINVAL;
  		}
		if (pdata->gpio_zarlinkReset >= 0)
		{
		  if(sds_misc_debug>0) printk("%s(): Zarlink reset(%d)\n",__func__,val);
			
			gpio_set_value(pdata->gpio_zarlinkReset, 0);
			mdelay(100);
			gpio_set_value(pdata->gpio_zarlinkReset, 1);
			mdelay(10);

#if 1 // SKJ 20180501 : Print "sys_prop" for Wi-Fi test command
			printk("\n%s(): sys_prop: must be here...for Wi-Fi test command\n\n",__func__);
#endif       
		}
		else
			printk("%s(): gpio configure error\n",__func__);
  		break;
 	}

  	case MISC_SET_PCM_SELECT:
  	{
  		if (copy_from_user((void *)&val, (void __user *)arg, sizeof(int)))
  		{
    		printk("%s(): [ERR] invalid val %d\n",__func__, _IOC_NR(cmd));
			return -EINVAL;
  		}
		//if (!IS_ERR(pdata->gpio_pcmSelect))
		if (pdata->gpio_pcmSelect >= 0)
		{
		  if(sds_misc_debug>0) printk("%s(): PCM Select(%d)\n",__func__,val);
			//gpiod_set_value(pdata->gpio_pcmSelect, val);
			gpio_set_value(pdata->gpio_pcmSelect, val);
		}
		else
			printk("%s(): gpio configure error\n",__func__);
  		break;
 	}
	
	case MISC_SET_TOUCH_RST_OUT:
  	{
  		if (copy_from_user((void *)&val, (void __user *)arg, sizeof(int)))
  		{
    		printk("%s(): [ERR] invalid val %d\n",__func__, _IOC_NR(cmd));	return -EINVAL;
  		}
		if (pdata->gpio_tspReset >= 0)
		{
		  if(sds_misc_debug>0) printk("%s(): Touch IC Reset(%d)\n",__func__,val);
			gpio_set_value(pdata->gpio_tspReset, val);
		}
		else
			printk("%s(): gpio configure error\n",__func__);
  		break;
 	}
	
	case MISC_SET_DOOR_POWER_ENABLE:
  	{
  		if (copy_from_user((void *)&val, (void __user *)arg, sizeof(int)))
  		{
    		printk("%s(): [ERR] invalid val %d\n",__func__, _IOC_NR(cmd));	return -EINVAL;
  		}
		if (pdata->gpio_doorPowerEnable >= 0)
		{
		  if(sds_misc_debug>0) printk("%s(): Door Power Enabe(%d)\n",__func__,val);
			gpio_set_value(pdata->gpio_doorPowerEnable, val);
		}
		else
			printk("%s(): gpio configure error\n",__func__);
  		break;
 	}
	
	case MISC_GET_DOOR_CALL_DET:
  	{
		if (pdata->gpio_doorCallDet >= 0)
		{
			val = gpio_get_value(pdata->gpio_doorCallDet);
			if(copy_to_user((void __user *)arg, (void *)&val, sizeof(int)) >=0 )
			{
				printk("%s(): Door Call Det = %d\n",__func__,val);
				return 0;
			}
			else
				return -EFAULT;
		}
		else
			printk("%s(): gpio configure error\n",__func__);
  		break;
 	}
	
	case MISC_GET_GPIO_DOOR_CALL_DET:
  	{
		if (pdata->gpio_doorCallDet >= 0)
		{
			val = pdata->gpio_doorCallDet;
			if(copy_to_user((void __user *)arg, (void *)&val, sizeof(int)) >=0 )
			{
				printk("%s(): Door Call Gpio = %d\n",__func__,val);
				return 0;
			}
			else
				return -EFAULT;
		}
		else
		{
			printk("%s(): gpio configure error\n",__func__);
			return -EFAULT;
		}
 	}
	
	case MISC_GET_DOOR_IR_DET:
  	{
		if (pdata->gpio_doorIrDet >= 0)
		{
			val = gpio_get_value(pdata->gpio_doorIrDet);
			if(copy_to_user((void __user *)arg, (void *)&val, sizeof(int)) >=0 )
			{
				printk("%s(): Door Ir Det = %d\n",__func__,val);
				return 0;
			}
			else
				return -EFAULT;
		}
		else
			printk("%s(): gpio configure error\n",__func__);
  		break;
 	}
	
	case MISC_GET_GPIO_DOOR_IR_DET:
  	{
		if (pdata->gpio_doorIrDet >= 0)
		{
			val = pdata->gpio_doorIrDet;
			if(copy_to_user((void __user *)arg, (void *)&val, sizeof(int)) >=0 )
			{
				printk("%s(): Door Ir Gpio = %d\n",__func__,val);
				return 0;
			}
			else
				return -EFAULT;
		}
		else
		{
			printk("%s(): gpio configure error\n",__func__);
			return -EFAULT;
		}
 	}
	case MISC_TEST_DEBUG_MSG:
  {
		if (copy_from_user((void *)&val, (void __user *)arg, sizeof(int)))
		{
  		printk("%s(): [ERR] invalid val %d\n",__func__, _IOC_NR(cmd));
  		return -EINVAL;
		}

    if(val == 3)
    {  	
		if(gndoor_call_state == AUTO_CALL_STOP) {
			printk("%s(): AUTO_CALL_START = %d (25sec period)\n",__func__,val);

			gndoor_call_state = AUTO_CALL_RUN;
			door_call_wakeup_timer.expires = get_jiffies_64() + (1*HZ);
			add_timer(&door_call_wakeup_timer);
		}
		else
			printk("%s(): auto call mode = %d\n",__func__, gndoor_call_state);
	}
    else
    {
  		sds_misc_debug = val;
      gndoor_call_state = AUTO_CALL_STOP;
  		printk("%s(): debug level = %d\n",__func__,val);
    }
    break;
 	}
	
  	{
		if (pdata->gpio_doorIrDet >= 0)
		{
			val = pdata->gpio_doorIrDet;
			if(copy_to_user((void __user *)arg, (void *)&val, sizeof(int)) >=0 )
			{
				printk("%s(): Door Ir Gpio = %d\n",__func__,val);
				return 0;
			}
			else
				return -EFAULT;
		}
		else
		{
			printk("%s(): gpio configure error\n",__func__);
			return -EFAULT;
		}
 	}
	case MISC_TEST_SET:	// KJW only for test
  	{
  		if (copy_from_user((void *)&val, (void __user *)arg, sizeof(int)))
  		{
    		printk("%s(): [ERR] invalid val %d\n",__func__, _IOC_NR(cmd));
			return -EINVAL;
  		}
		testValue = val;
     	printk("%s(): MISC Set Test : Set Value is (%d)\n",__func__,testValue);
		if(testValue == 1)
		{
			input_report_key(input_dev, KEY_F1, PRESSED);
			input_sync(input_dev);
			input_report_key(input_dev, KEY_F1, RELEASED);
			input_sync(input_dev);
		}
		else if(testValue == 2)
		{
			input_report_key(input_dev, KEY_F2, PRESSED);
			input_sync(input_dev);
			input_report_key(input_dev, KEY_F2, RELEASED);
			input_sync(input_dev);
		}
  		break;
 	}
	case MISC_TEST_GET:	// KJW only for test
  	{
		val = testValue;
		if(copy_to_user((void __user *)arg, (void *)&val, sizeof(int)) >=0 )
		{
			printk("%s(): MISC Get Test : Get Value is (%d)\n",__func__,testValue);
			return 0;
		}
		else
			return -EFAULT;
 	}
 
  	default:
  		printk("%s(): [ERR] invalid cmd %d\n",__func__, _IOC_NR(cmd));
		return -EINVAL;
	}
	
	return ret;
}

static int sds_misc_gpio_configure(struct device *dev)
{
	dev_err(dev, "%s()",__func__);
	
	/*
	pdata->gpio_haReset = devm_gpiod_get(dev, "ha_reset", GPIOD_OUT_LOW);
	if (IS_ERR(pdata->gpio_haReset)) {
		dev_err(dev, "cannot get ha_reset-gpio %ld\n", PTR_ERR(pdata->gpio_haReset));
	}
	*/
	pdata->gpio_haReset = of_get_named_gpio(dev->of_node, "ha_reset-gpio", 0);
	if (pdata->gpio_haReset < 0) {
		dev_err(dev, "cannot get ha_reset-gpio %d\n",	pdata->gpio_haReset);
	}
	
	pdata->gpio_haBootSel = of_get_named_gpio(dev->of_node, "ha_bootsel-gpio", 0);
	if (pdata->gpio_haBootSel < 0) {
		dev_err(dev, "cannot get ha_bootsel-gpio %d\n",	pdata->gpio_haBootSel);
	}
	
	pdata->gpio_zbReset = of_get_named_gpio(dev->of_node, "zb_reset-gpio", 0);
	if (pdata->gpio_zbReset < 0) {
		dev_err(dev, "cannot get zb_reset-gpio %d\n",	pdata->gpio_zbReset);
	}
	
	pdata->gpio_zbBootSel = of_get_named_gpio(dev->of_node, "zb_bootsel-gpio", 0);
	if (pdata->gpio_zbBootSel < 0) {
		dev_err(dev, "cannot get zb_bootsel-gpio %d\n",	pdata->gpio_zbBootSel);
	}
	
	pdata->gpio_zarlinkReset = of_get_named_gpio(dev->of_node, "zarlink_reset-gpio", 0);
	if (pdata->gpio_zarlinkReset < 0) {
		dev_err(dev, "cannot get zarlink_reset-gpio %d\n",	pdata->gpio_zarlinkReset);
	}
	
	pdata->gpio_zarlinkMode = of_get_named_gpio(dev->of_node, "zarlink_mode-gpio", 0);
	if (pdata->gpio_zarlinkMode < 0) {
		dev_err(dev, "cannot get zarlink_mode-gpio %d\n",	pdata->gpio_zarlinkMode);
	}
	
	pdata->gpio_pcmSelect = of_get_named_gpio(dev->of_node, "pcm_select-gpio", 0);
	if (pdata->gpio_pcmSelect < 0) {
		dev_err(dev, "cannot get pcm_select-gpio %d\n",	pdata->gpio_pcmSelect);
	}
	
	pdata->gpio_doorPowerEnable = of_get_named_gpio(dev->of_node, "door_power_en-gpio", 0);
	if (pdata->gpio_doorPowerEnable < 0) {
		dev_err(dev, "cannot get door_power_en-gpio %d\n",	pdata->gpio_doorPowerEnable);
	}
	
	pdata->gpio_doorCallDet = of_get_named_gpio(dev->of_node, "door_call_det-gpio", 0);
	if (pdata->gpio_doorCallDet < 0) {
		dev_err(dev, "cannot get door_call_det-gpio %d\n",	pdata->gpio_doorCallDet);
	}
	
	pdata->gpio_doorIrDet = of_get_named_gpio(dev->of_node, "door_ir_det-gpio", 0);
	if (pdata->gpio_doorIrDet < 0) {
		dev_err(dev, "cannot get door_ir_det-gpio %d\n",	pdata->gpio_doorIrDet);
	}
	
	pdata->gpio_tspReset = of_get_named_gpio(dev->of_node, "tsp_reset-gpio", 0);
	if (pdata->gpio_tspReset < 0) {
		dev_err(dev, "cannot get tsp_reset-gpio %d\n",	pdata->gpio_tspReset);
	}
	
	pdata->gpio_powerSwHold = of_get_named_gpio(dev->of_node, "power_sw_hold-gpio", 0);
	if (pdata->gpio_powerSwHold < 0) {
		dev_err(dev, "cannot get power_sw_hold-gpio %d\n",	pdata->gpio_powerSwHold);
	}

	return 0;
}

static int sds_misc_gpio_initialize(struct device *dev)
{
	int ret;
	
	dev_err(dev, "%s()",__func__);
	
	/*
	if (!IS_ERR(pdata->gpio_haReset))
	{
		gpiod_set_value(pdata->gpio_haReset, SLAVE_RESET_HOLD);
		msleep(100);
		gpiod_set_value(pdata->gpio_haReset, SLAVE_RESET_RELEASE);
	}
	*/
	
	if (pdata->gpio_powerSwHold >= 0)
	{
		gpio_direction_output(pdata->gpio_powerSwHold, 0);
		dev_err(dev, "Set power_sw_hold to 0\n");
	}
	
	if (pdata->gpio_haBootSel >= 0)
		gpio_direction_output(pdata->gpio_haBootSel, SLAVE_BOOT_NORMAL);
	
	if (pdata->gpio_haReset >= 0)
	{
		gpio_direction_output(pdata->gpio_haReset, SLAVE_RESET_HOLD);
		msleep(100);
		gpio_set_value(pdata->gpio_haReset, SLAVE_RESET_RELEASE);
	}
	
	if (pdata->gpio_zbBootSel >= 0)
		gpio_direction_output(pdata->gpio_zbBootSel, ZIGBEE_BOOT_NORMAL);
	
	if (pdata->gpio_zbReset >= 0)
	{
		gpio_direction_output(pdata->gpio_zbReset, ZIGBEE_RESET_HOLD);
		msleep(100);
		gpio_set_value(pdata->gpio_zbReset, ZIGBEE_RESET_RELEASE);
	}
	
	if (pdata->gpio_zarlinkReset >= 0)
	{
		if (pdata->gpio_zarlinkMode >= 0)
		{
			gpio_direction_output(pdata->gpio_zarlinkMode, 1);
			msleep(10);
		}
		gpio_direction_output(pdata->gpio_zarlinkReset, 0);
		msleep(100);
		gpio_direction_output(pdata->gpio_zarlinkReset, 1);
	}
	
	if (pdata->gpio_pcmSelect >= 0)
		gpio_direction_output(pdata->gpio_pcmSelect, 0);
	
	if (pdata->gpio_doorPowerEnable >= 0)
		gpio_direction_output(pdata->gpio_doorPowerEnable, 0);
	
	if (pdata->gpio_doorCallDet >= 0)
	{
		gpio_request(pdata->gpio_doorCallDet, "door_call_det");
		gpio_export(pdata->gpio_doorCallDet, false);
		gpio_direction_input(pdata->gpio_doorCallDet);		
		ret = request_irq(gpio_to_irq(pdata->gpio_doorCallDet), call_key_irq_handler, IRQF_TRIGGER_RISING | IRQF_ONESHOT, "doorcall", NULL);
		if(ret < 0){
			dev_err(dev, "err DOOR_CALL irq request failed\n");
	  }
	}
	
	if (pdata->gpio_doorIrDet >= 0)
	{
		gpio_request(pdata->gpio_doorIrDet, "door_ir_det");
		gpio_export(pdata->gpio_doorIrDet, false);
		gpio_direction_input(pdata->gpio_doorIrDet);		
		ret = request_irq(gpio_to_irq(pdata->gpio_doorIrDet), det_ir_irq_handler, IRQF_TRIGGER_RISING | IRQF_ONESHOT, "doorir", NULL);
		if(ret < 0){
			dev_err(dev, "err DOOR_CALL irq request failed\n");
	  }
	}
	
	if (pdata->gpio_tspReset >= 0)
		gpio_direction_output(pdata->gpio_tspReset, 1);
	
	return 0;
}

static const struct of_device_id sds_misc_match[] = {
	{
		.compatible = "sds,misc",
	},
	{ },
};
MODULE_DEVICE_TABLE(of, sds_misc_match);

static int sds_misc_probe(struct platform_device *pdev)
{
	const struct of_device_id *match;
	int ret, i;

	dev_err(&pdev->dev, "%s() Start",__func__);
	
	if (!pdev->dev.of_node) {
		dev_err(&pdev->dev, "device tree node not found\n");
		return -ENODEV;
	}

	pdata = devm_kzalloc(&pdev->dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata)
		return -ENOMEM;

	match = of_match_node(sds_misc_match, pdev->dev.of_node);
	if (!match) {
		dev_err(&pdev->dev, "Cannot match dt node\n");
		return -ENODEV;
	}
	
	sds_misc_gpio_configure(&pdev->dev);
	sds_misc_gpio_initialize(&pdev->dev);

	platform_set_drvdata(pdev, pdata);
	dev_info(&pdev->dev, "platform driver %s registered\n", pdev->name);
	
	input_dev = input_allocate_device();
	input_dev->name = "sds_key";
	input_dev->evbit[0] = BIT(EV_KEY);
	input_dev->id.version = 0.001;

	set_bit(KEY_F1 & KEY_MAX, input_dev->keybit);
	set_bit(KEY_F2 & KEY_MAX, input_dev->keybit);
	
	ret = input_register_device(input_dev);
	if (ret) 
	{
		dev_err(&pdev->dev, "Unable to register %s input device\n", input_dev->name);
	}
	
	init_timer(&door_call_wakeup_timer);	
	door_call_wakeup_timer.function = func_door_call_wakeup_timer;

	dev_err(&pdev->dev, "%s() End",__func__);
	return 0;
}

static int sds_misc_remove(struct platform_device *pdev)
{
	struct sds_misc_platform_data *pdata =
				platform_get_drvdata(pdev);

	return 0;
}

static struct platform_driver sds_misc_driver = {
	.probe	= sds_misc_probe,
	.remove = sds_misc_remove,
	.driver = {
		.name	= "sds_misc",
		.owner	= THIS_MODULE,
		.of_match_table = of_match_ptr(sds_misc_match),
	},
};

struct file_operations sds_misc_fops = {
	.read = device_read,
	.write = device_write,
	//.unlocked_ioctl = device_ioctl,
	.compat_ioctl = device_ioctl,	// kernel 64bit, usrspace 32bit compatible
	.open = device_open,
	.release = device_release,
};

static struct miscdevice sds_misc_device =
{
	MISC_DYNAMIC_MINOR,
	"sds_misc",
	&sds_misc_fops,
};

static int __init misc_init(void)
{
	int result;

	printk("%s\n", __func__);

	result = misc_register(&sds_misc_device);
	if (result < 0) {
		printk("%s(): %s failed with %d\n",__func__, result);
		return result;
	}
	
	return platform_driver_register(&sds_misc_driver);
}

static void __exit misc_exit(void)
{
	printk("%s\n", __func__);
	
	misc_deregister(&sds_misc_device);
	platform_driver_unregister(&sds_misc_driver);
}

module_init(misc_init);
module_exit(misc_exit);

MODULE_ALIAS("platform:sds_misc");
MODULE_DESCRIPTION("ARTIK Zigbee Power Control Driver");
MODULE_LICENSE("GPL");
