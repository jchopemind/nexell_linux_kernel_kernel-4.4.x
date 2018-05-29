/*
* ALSA SoC CX2070X codec driver
*
* Copyright:   (C) 2009/2010 Conexant Systems
*
* Based on sound/soc/codecs/tlv320aic2x.c by Vladimir Barinov
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 as
* published by the Free Software Foundation.
*
* 
*      
*************************************************************************
*  Modified Date:  09/14/12
*  File Version:   3.1.10.13
*************************************************************************
*/

#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/pm.h>
#include <linux/platform_device.h>
#include <sound/core.h>
#include <sound/pcm.h>
#include <sound/pcm_params.h>
#include <sound/soc.h>
#include <sound/soc-dapm.h>
#include <sound/initval.h>
#include <sound/tlv.h>
#include <linux/gpio.h>
#include <sound/jack.h>
#include <linux/slab.h>
#include <linux/i2c.h>

#include "cx2070x.h"

#if defined(CONFIG_SND_CXLIFEGUARD)
#include "cxdebug.h"
#endif 

#ifdef CONFIG_SND_CX2070X_LOAD_FW
#include <linux/firmware.h>
#include "cxpump.h" 
#endif

#define CX2070X_DRIVER_VERSION AUDDRV_VERSION( 3, 1 ,0x10 ,0x13) 

#define CX2070X_REG_NAMES	1
#define CX2070X_REG_WIDE	1

#define AUDIO_NAME	"cx2070x"

#define CX2070X_RATES	( \
       SNDRV_PCM_RATE_8000  \
    | SNDRV_PCM_RATE_11025 \
    | SNDRV_PCM_RATE_16000 \
    | SNDRV_PCM_RATE_22050 \
    | SNDRV_PCM_RATE_32000 \
    | SNDRV_PCM_RATE_44100 \
    | SNDRV_PCM_RATE_48000 \
    | SNDRV_PCM_RATE_88200 \
    | SNDRV_PCM_RATE_96000 )
    
#if defined(CONFIG_SND_DIGICOLOR_SOC_CHANNEL_VER_4_30F)

#define CX2070X_FORMATS ( SNDRV_PCM_FMTBIT_S16_LE \
    | SNDRV_PCM_FMTBIT_S16_BE \
    | SNDRV_PCM_FMTBIT_MU_LAW \
    | SNDRV_PCM_FMTBIT_A_LAW )
#else
#define CX2070X_FORMATS ( SNDRV_PCM_FMTBIT_S16_LE \
    | SNDRV_PCM_FMTBIT_S16_BE )
#endif



#define noof(a) (sizeof(a)/sizeof(a[0]))
#define NOINLINE __attribute__((__noinline__))

// SKJ_DEBUG
static int debug	   = 0;
# define INFO(fmt,...)	if (debug) printk(KERN_ERR fmt, ##__VA_ARGS__)
# define _INFO(fmt,...)	if (debug) printk(KERN_ERR fmt, ##__VA_ARGS__)
# define _INFO_		1

#define MSG(fmt,...)	  printk(KERN_ERR fmt, ##__VA_ARGS__)
#define ERROR(fmt,...)	printk(KERN_ERR fmt, ##__VA_ARGS__)

//SKJ 20180501 : must be change (long -> int)
//               because long is 8byte in 64bit enviroment (long is 4byte in TCC)

enum {
    b_00000000,b_00000001,b_00000010,b_00000011, b_00000100,b_00000101,b_00000110,b_00000111,
    b_00001000,b_00001001,b_00001010,b_00001011, b_00001100,b_00001101,b_00001110,b_00001111,
    b_00010000,b_00010001,b_00010010,b_00010011, b_00010100,b_00010101,b_00010110,b_00010111,
    b_00011000,b_00011001,b_00011010,b_00011011, b_00011100,b_00011101,b_00011110,b_00011111,
    b_00100000,b_00100001,b_00100010,b_00100011, b_00100100,b_00100101,b_00100110,b_00100111,
    b_00101000,b_00101001,b_00101010,b_00101011, b_00101100,b_00101101,b_00101110,b_00101111,
    b_00110000,b_00110001,b_00110010,b_00110011, b_00110100,b_00110101,b_00110110,b_00110111,
    b_00111000,b_00111001,b_00111010,b_00111011, b_00111100,b_00111101,b_00111110,b_00111111,
    b_01000000,b_01000001,b_01000010,b_01000011, b_01000100,b_01000101,b_01000110,b_01000111,
    b_01001000,b_01001001,b_01001010,b_01001011, b_01001100,b_01001101,b_01001110,b_01001111,
    b_01010000,b_01010001,b_01010010,b_01010011, b_01010100,b_01010101,b_01010110,b_01010111,
    b_01011000,b_01011001,b_01011010,b_01011011, b_01011100,b_01011101,b_01011110,b_01011111,
    b_01100000,b_01100001,b_01100010,b_01100011, b_01100100,b_01100101,b_01100110,b_01100111,
    b_01101000,b_01101001,b_01101010,b_01101011, b_01101100,b_01101101,b_01101110,b_01101111,
    b_01110000,b_01110001,b_01110010,b_01110011, b_01110100,b_01110101,b_01110110,b_01110111,
    b_01111000,b_01111001,b_01111010,b_01111011, b_01111100,b_01111101,b_01111110,b_01111111,
    b_10000000,b_10000001,b_10000010,b_10000011, b_10000100,b_10000101,b_10000110,b_10000111,
    b_10001000,b_10001001,b_10001010,b_10001011, b_10001100,b_10001101,b_10001110,b_10001111,
    b_10010000,b_10010001,b_10010010,b_10010011, b_10010100,b_10010101,b_10010110,b_10010111,
    b_10011000,b_10011001,b_10011010,b_10011011, b_10011100,b_10011101,b_10011110,b_10011111,
    b_10100000,b_10100001,b_10100010,b_10100011, b_10100100,b_10100101,b_10100110,b_10100111,
    b_10101000,b_10101001,b_10101010,b_10101011, b_10101100,b_10101101,b_10101110,b_10101111,
    b_10110000,b_10110001,b_10110010,b_10110011, b_10110100,b_10110101,b_10110110,b_10110111,
    b_10111000,b_10111001,b_10111010,b_10111011, b_10111100,b_10111101,b_10111110,b_10111111,
    b_11000000,b_11000001,b_11000010,b_11000011, b_11000100,b_11000101,b_11000110,b_11000111,
    b_11001000,b_11001001,b_11001010,b_11001011, b_11001100,b_11001101,b_11001110,b_11001111,
    b_11010000,b_11010001,b_11010010,b_11010011, b_11010100,b_11010101,b_11010110,b_11010111,
    b_11011000,b_11011001,b_11011010,b_11011011, b_11011100,b_11011101,b_11011110,b_11011111,
    b_11100000,b_11100001,b_11100010,b_11100011, b_11100100,b_11100101,b_11100110,b_11100111,
    b_11101000,b_11101001,b_11101010,b_11101011, b_11101100,b_11101101,b_11101110,b_11101111,
    b_11110000,b_11110001,b_11110010,b_11110011, b_11110100,b_11110101,b_11110110,b_11110111,
    b_11111000,b_11111001,b_11111010,b_11111011, b_11111100,b_11111101,b_11111110,b_11111111,
};

#define REG_TYPE_RO	0	// read only,  read during initialization
#define REG_TYPE_RW	1	// read/write, read during initialization
#define REG_TYPE_WI	2	// write only, written during initialization
#define REG_TYPE_WC	3	// write/init, needs NEWC to be set when written
#define REG_TYPE_DM	4	// dummy register, read/write to cache only
#if CX2070X_REG_WIDE
# define REG_TYPE_MASK	0x0F
# define REG_WIDTH_B	0x00	//  8-bit data
# define REG_WIDTH_W	0x10	// 16-bit data
# define REG_WIDTH_MASK	0xF0
#endif
enum {
#define __REG(a,b2,b1,c,d,e,f) a,
#include "cx2070x-i2c.h"
#undef __REG
};

#if 1 /* MYSEO */
struct cx20703_reg
{
	unsigned short reg;
	unsigned char val;
};

void *glp_reg_cache;

static struct cx20703_reg cx2070x_initialize_register[] = {
	/* Org inital value
	{0x0F50, 0xFF}, // Slave mode for both DP1 & DP2
	{0x0F51, 0xB0}, // Port 1 Control , Rx/Tx Enable , Left justified , 1-bit delay
	{0x0F52, 0x03}, // 32 Clocks / Tx Clocks per Frame;
	{0x0F53, 0x03}, // 32 Clocks / Rx Clocks per Frame;
	{0x0F54, 0x0F}, // Port 1, Tx Sync Width , 16
	{0x0F55, 0x0F}, // Port 1, Rx Sync Width , 16
	{0x0F56, 0x05}, // Port 1 Control2 , Sample Width , 16bit 
	{0x100D, 0x00}, // DAC1 Left Gain
	{0x100E, 0x00}, // DAC2 Right Gain
	{0x100F, 0x4F}, // DSP Max Volume
	{0x1010, 0x4A}, // DSP Hardware DAC setting
	{0x1011, 0x00}, // Class-D Gain
	{0x1012, 0x00}, // DAC3 Sub Gain
	{0x1013, 0x00}, // Line In ADC1 Gain Left
	{0x1014, 0x00}, // Line In ADC1 Gain Right
	{0x1015, 0x00}, // Mic Gain Left
	{0x1016, 0x00}, // Mic Gain Right
	{0x1017, 0x4A}, // DSP Max Microphone Gain
	{0x1018, 0x03}, // Volume Mutes
	{0x1019, 0x04}, // Output Control , Class D Enable
	{0x101A, 0x01}, // Input Control, Auto -> Manual
	{0x101B, 0x17}, // Line 1 Gain
	{0x101C, 0x17}, // Line 2 Gain
	{0x101D, 0x17}, // Line 3 Gain
	{0x101E, 0x00}, // Mic Control
	{0x101F, 0x00}, // Mix0 Input 0
	{0x1020, 0x00}, // Mix0 Input 1
	{0x1021, 0x00}, // Mix0 Input 2
	{0x1022, 0x00}, // Mix0 Input 3
	{0x1023, 0x00}, // Mix1 Input 0
	{0x1024, 0x00}, // Mix1 Input 1
	{0x1025, 0x00}, // Mix1 Input 2
	{0x1026, 0x00}, // Mix1 Input 3
	{0x116A, 0xA7}, // ADC Port Input Rate
	{0x116B, 0xA7}, // Microphne Port Input Rate , 16bit, Stereo,16KHz
	{0x116C, 0x22}, // Mic and ADC Routing Destinations
	{0x116D, 0xA6}, // Stream3 Input Rate , 16bit, Stereo , 44.1KHz->48KHz
	{0x116E, 0x02}, // Stream3 Routing , Digital Port1
	{0x116F, 0xA7}, // Stream4 Input Rate , 16bit, Stereo , 48KHz->48KHz
	{0x1170, 0x12}, // Stream4 Routing , USB
	{0x1171, 0x26}, // Stream5 Output Rate to Digital1 , 16bit , 16KHz -> 44.1KHz
	{0x1172, 0x2D}, // Stream6 Output Rate to Digital1 , 16bit , 48KHz -> 48KHz
	{0x1173, 0x07}, // Stream7 Output Rate to DAC , 48K
	{0x1174, 0x02}, // DAC Routing Register
	{0x1176, 0x60}, // Miscellaneous2 Routing Register
	{0x1177, 0x42}, // USB Routing Register
	{0x117A, 0x45}, // DSP Processing Enable , In Nound NR//AEC/NR Enable : bit[6] => 1 : MIC_R, 0 : MIC_L
	{0x117B, 0x00}, // DSP Processing Enable Register , EQ Disable
	{0x117C, 0x00}, // DSP Init , Stream8 Disable
	{0x117E, 0x00}, // Low Power
	{0x117F, 0x09}, // DAC Source , Scale Out
	{0x1180, 0x00}, // Sub(Stream8) Source , None
	{0x1181, 0x00}, // Digital out1(Stream5) Source , Voice Out0
	{0x1182, 0x00}, // Digital out2(Stream6) Source , None
	{0x1183, 0x00}, // USBoutinSource , Sclae Out
	{0x1184, 0x01}, // Mixer0 Input0 Source , None
	{0x1185, 0x01}, // Mixer0 Input1 Source , Stream3 Out
	{0x1186, 0x01}, // Mixer0 Input2 Source , Stream4 Out
	{0x1187, 0x03}, // Mixer0 Input3 Source , None
	{0x1188, 0x01}, // Mix1in0Source 0x1188 = 0x01
	{0x1189, 0x02}, // Mix1in1Source 0x1189 = 0x03
	{0x118A, 0x03}, // Mix1in2Source 0x118A = 0x00
	{0x118B, 0x00}, // Mix1in3Source 0x118B = 0x00
	{0x118C, 0x00}, // Voice Processing input Source , Stream2 Out
	{0x118D, 0x00}, // USBoutin2Source 0x118D = 0x00
	{0x118E, 0x00}, // I2S1outin2Source 0x118E = 0x00
	{0x118F, 0x00}, // I2S2outin2Source 0x118F = 0x00
	{0x11B1, 0x00}, // Voice Output0 Selection , 16K
	{0x117D, 0x8B}, // DSP Init 0x117D = 0x84 : must be last order and +1
	{0x0000, 0x00}
	*/
// Test initialvalue by KJW
{0x100D, 0x00},
{0x100E, 0x00},
{0x1011, 0x00},
{0x1012, 0x00},
{0x1013, 0x05},
{0x1014, 0x05},
{0x1015, 0x00},
{0x1017, 0x4A},
{0x101A, 0x01},
{0x101B, 0x17},
{0x101C, 0x17},
{0x101D, 0x17},
{0x1018, 0x00},
{0x1019, 0x04},
{0x112A, 0x00},
{0x112B, 0xF4},
{0x112C, 0x80},
{0x1133, 0xFE},
{0x10D1, 0x00},
{0x10D2, 0x00},
{0x10E1, 0x32},
{0x10E2, 0x00},
{0x10E3, 0x00},
{0x10E4, 0x08},
{0x10E5, 0x00},
{0x1136, 0x00},
{0x1137, 0x08},
{0x1138, 0x00},
{0x100F, 0x4F},
{0x1016, 0x00},
{0x113A, 0x00},
{0x1165, 0x10},
{0x1010, 0x4A},
{0x1007, 0xE0},
{0x1008, 0x1F},
{0x100C, 0x18},
{0x1006, 0x0F},
{0x101E, 0x00},
{0x101F, 0x00},
{0x1020, 0x00},
{0x112F, 0x00},
{0x1130, 0x50},
{0x1132, 0x00},
{0x1131, 0x00},
{0x112D, 0x00},
{0x112E, 0x20},
{0x10FA, 0x00},
{0x10FB, 0x08},
{0x1112, 0xEA},
{0x1113, 0xFF},
{0x1114, 0x00},
{0x1115, 0x00},
{0x111A, 0xC4},
{0x111B, 0x09},
{0x111C, 0x00},
{0x111D, 0x01},
{0x111E, 0xA8},
{0x111F, 0x16},
{0x1120, 0x00},
{0x1121, 0x08},
{0x1122, 0x14},
{0x1123, 0x28},
{0x1124, 0x60},
{0x1125, 0x09},
{0x1126, 0x2C},
{0x1127, 0x01},
{0x1128, 0x00},
{0x1129, 0x20},
{0x1009, 0x00},
{0x1166, 0x7D},
{0x1167, 0x00},
{0x1000, 0x01},
{0x117F, 0x09}, // DAC Source , Scale Out
{0x1188, 0x01}, // Mix1in0Source 0x1188 = 0x01
{0x117D, 0x8B}, // DSP Init 0x117D = 0x84 : must be last order and +1
{0x0000, 0x00}
};

static void write_regs_cx2070x(struct i2c_client *i2c)
{
	unsigned char data[3] = {0, 0, 0};
	const struct cx20703_reg *next = &cx2070x_initialize_register;

	while (!((next->reg == 0x0) && (next->val == 0x0))) {
		data[0] = next->reg>>8;
		data[1] = (unsigned char)next->reg&0xff;
		data[2] = next->val;

    INFO("%s(): 0x%04X = 0x%02X\n",__func__, (data[0]<<8 | data[1]), data[2]);
		i2c_master_send(i2c, data, 3);
		msleep (1);

		next++;
	}
}
#endif

#if CX2070X_REG_WIDE
typedef u16 cx2070x_reg_t;
#else
typedef u8 cx2070x_reg_t;
#endif
static const cx2070x_reg_t cx2070x_data[]=
{
#define __REG(a,b2,b1,c,d,e,f) c,
#include "cx2070x-i2c.h"
#undef __REG
};

struct cx2070x_reg
{
#if CX2070X_REG_NAMES
    char *name;
#endif
    u16   addr;
    u8    bias;
    u8    type;
};

static const struct cx2070x_reg cx2070x_regs[]=
{
#if defined(CONFIG_SND_DIGICOLOR_SOC_CHANNEL_VER_3_13E)
# if CX2070X_REG_NAMES
#  define __REG(a,b2,b1,c,d,e,f) { #a,b1,d,REG_TYPE_##e|REG_WIDTH_##f },
# else
#  define __REG(a,b2,b1,c,d,e,f) { b1,d,REG_TYPE_##e|REG_WIDTH_##f },
# endif
#elif defined(CONFIG_SND_DIGICOLOR_SOC_CHANNEL_VER_4_30F)
# if CX2070X_REG_NAMES
#  define __REG(a,b2,b1,c,d,e,f) { #a,b2,d,REG_TYPE_##e|REG_WIDTH_##f },
# else
#  define __REG(a,b2,b1,c,d,e,f) { b2,d,REG_TYPE_##e|REG_WIDTH_##f },
# endif
#else
# if CX2070X_REG_NAMES
#  define __REG(a,b2,b1,c,d,e,f) { #a,b2,d,REG_TYPE_##e|REG_WIDTH_##f },
# else
#  define __REG(a,b2,b1,c,d,e,f) { b2,d,REG_TYPE_##e|REG_WIDTH_##f },
# endif
#endif
#include "cx2070x-i2c.h"
#undef __REG
};

// codec private data
struct cx2070x_priv
{
  //enum snd_soc_control_type control_type;	// KJW
  void *control_data;
  unsigned int sysclk;
  int	       master;
  enum Cx_INPUT_SEL input_sel;
  enum Cx_OUTPUT_SEL output_sel;
  unsigned int mute;
  struct gpio_desc *reset_gpio;
};

#define get_cx2070x_priv(_codec_) ((struct cx2070x_priv *)snd_soc_codec_get_drvdata(codec))

#if defined(CONFIG_CXNT_SOFTWOARE_SIMULATION)
static int bNoHW = 1;
#else
static int bNoHW = 0;
#endif 


/*
 * Playback Volume 
 *
 * max : 0x00 : 0 dB
 *       ( 1 dB step )
 * min : 0xB6 : -74 dB
 */
static const DECLARE_TLV_DB_SCALE(dac_tlv, -7400 , 100, 0);


/*
 * Capture Volume 
 *
 * max : 0x00 : 0 dB
 *       ( 1 dB step )
 * min : 0xB6 : -74 dB
 */
static const DECLARE_TLV_DB_SCALE(adc_tlv, -7400 , 100, 0);



#if defined(CONFIG_SND_CX2070X_LOAD_FW)
int I2cWrite( struct i2c_client *i2c, unsigned char ChipAddr, unsigned int cbBuf, unsigned char* pBuf);
int I2cWriteThenRead( struct i2c_client *i2c, unsigned char ChipAddr, unsigned int cbBuf,
    unsigned char* pBuf, unsigned int cbReadBuf, unsigned char*pReadBuf);
#endif 

#define GET_REG_CACHE(_codec_) (cx2070x_reg_t *) (_codec_)
static inline unsigned int cx2070x_read_reg_cache(void *lp_reg_cache, unsigned int reg)
{
    cx2070x_reg_t *reg_cache;
    INFO("%s()\n",__func__);
    if (reg >= noof(cx2070x_regs))
        return (unsigned int)0;
    reg_cache  =  GET_REG_CACHE(lp_reg_cache);
    return reg_cache[reg];
}

static inline void cx2070x_write_reg_cache(void *lp_reg_cache, unsigned int reg, unsigned int value)
{
    cx2070x_reg_t *reg_cache;
    INFO("%s()\n",__func__);
    if (reg >= noof(cx2070x_regs))
        return;
    reg_cache=GET_REG_CACHE(lp_reg_cache);
    reg_cache[reg] = value;
}

static int NOINLINE cx2070x_real_write(struct i2c_client *i2c, unsigned int reg, unsigned int value)
{
    struct i2c_msg      msg[2];
    u8                  data[4];
    const struct cx2070x_reg *ri;

    ri=&cx2070x_regs[reg];

    switch(ri->type&REG_TYPE_MASK)
    {
    case REG_TYPE_RO:		// read only,  read during initialization
#if CX2070X_REG_NAMES
        ERROR("%s(): write to Read-only register '%s'\n",__func__,ri->name);
#endif
        break;

    case REG_TYPE_RW:		// read/write, read during initialization
    case REG_TYPE_WI:		// write only, written during initialization
    case REG_TYPE_WC:		// write/init, needs NEWC to be set when written
        msg[0].addr  = i2c->addr;
        msg[0].flags = i2c->flags & I2C_M_TEN;
        msg[0].buf   = &data[0];
        data[0]=(u8)(ri->addr>>8);
        data[1]=(u8)(ri->addr>>0);
        switch(ri->type&REG_WIDTH_MASK)
        {
        case REG_WIDTH_B:
            data[2]=(u8)(value-ri->bias);
            msg[0].len=3;
            break;
        case REG_WIDTH_W:
            data[2]=(u8)((value-ri->bias)>>0)&0xFF;
            data[3]=(u8)((value-ri->bias)>>8)&0xFF;
            msg[0].len=4;
            break;
        default:
            return -EIO;
        }
#ifdef DBG_MONITOR_REG 
        printk(KERN_ERR "Write REG %02x%02x  %02x\n",data[0],data[1],data[2]);
#endif 

    		if (i2c_master_send(i2c, msg[0].buf, msg[0].len) != msg[0].len)
            return -EIO;
        break;

#if defined(REG_TYPE_DM)
    case REG_TYPE_DM:		// dummy register, no I2C transfers
        break;
#endif
    }

    cx2070x_write_reg_cache(glp_reg_cache,reg,value);
    return 0;
}

static int NOINLINE cx2070x_real_read(struct i2c_client *i2c, unsigned int reg)
{
    struct i2c_msg	    msg[2];
    u8			            data[4];
    const struct        cx2070x_reg *ri;
    int			            dat;

    ri=&cx2070x_regs[reg];

    if ((ri->type&REG_TYPE_MASK)==REG_TYPE_DM)
        return cx2070x_read_reg_cache(glp_reg_cache,reg);

    data[0]=(u8)(ri->addr>>8);
    data[1]=(u8)(ri->addr>>0);

    msg[0].addr  = i2c->addr;
    msg[0].flags = i2c->flags & I2C_M_TEN;
    msg[0].len   = 2;
    msg[0].buf   = &data[0];

    msg[1].addr  = i2c->addr;
    msg[1].flags = (i2c->flags & I2C_M_TEN) | I2C_M_RD;
    msg[1].len   = ((ri->type&REG_WIDTH_MASK)==REG_WIDTH_W)?2:1;
    msg[1].buf   = &data[2];

#ifdef DBG_MONITOR_REG 
    printk(KERN_ERR "Read REG %02x%02x  %02x\n",data[0],data[1],data[2]);
#endif 

	if (i2c_master_send(i2c, msg[0].buf, msg[0].len) != msg[0].len)
        return -EIO;
	if (i2c_master_recv(i2c, msg[1].buf, msg[1].len) != msg[1].len)
        return -EIO;

    switch(ri->type&REG_WIDTH_MASK)
    {
    case REG_WIDTH_B:
        dat=ri->bias+data[2];
        break;
    case REG_WIDTH_W:
        dat=ri->bias+(data[2]<<0)+(data[3]<<8);
        break;
    default:
        return -EIO;
    }
    cx2070x_write_reg_cache(glp_reg_cache,reg,dat);
    return dat;
}

// reset codec via gpio pin.
#if defined(CONFIG_SND_CX2070X_GPIO_RESET)
static int cx2070x_reset_device(void)
{
	int err = 0;

	INFO("%s()\n",__func__);
  
	/* KJW
	if (cx2070x->reset_gpio) {
		gpiod_set_value(cx2070x->reset_gpio, 0);
		mdelay(10);
		gpiod_set_value(cx2070x->reset_gpio, 1);
		mdelay(100);
	}
	else
	{
		printk( KERN_ERR "cx2070x: reset pin is not valid\n");
		err = -ENODEV;
	}
	*/
	return err;
}
#endif //#if defined(CONFIG_SND_CX2070X_GPIO_RESET)


static int cx2070x_dsp_init(struct i2c_client *i2c,unsigned mode)
{
    unsigned r;

    INFO("%s()\n",__func__);
    cx2070x_real_write(i2c,DSP_INIT,mode);
    // maximum time for the NEWC to clear is about 2ms.
    for(r=1000;;) 
        if (!(cx2070x_real_read(i2c,DSP_INIT)&DSP_INIT_NEWC))
            return 0;
        else if (--r==0)
            return -EIO;
        else
            msleep(1);
}

static const char *output_select_mode[] =
{"AUTO",  "SPK" ,"LINE",  "HP" ,"PCM2"};

static const struct soc_enum output_select_enum[] = {
    SOC_ENUM_SINGLE_EXT(ARRAY_SIZE(output_select_mode),
    output_select_mode),
};

static const char *input_select_mode[] =
{"MIC",  "PCM" };
    
static const struct soc_enum input_select_enum[] = {
    SOC_ENUM_SINGLE_EXT(ARRAY_SIZE(input_select_mode),
    input_select_mode),
};

static const struct snd_kcontrol_new input_select_controls =
SOC_DAPM_ENUM("Route", input_select_enum);

static int cx2070x_hw_params(struct i2c_client *i2c)
{
  unsigned int s5,s3,i2s,dsp;
#define _3_3_f_f_5 1
#define _1_1_7_7_0 0
  int err =0;

  INFO("%lu: %s() called\n",jiffies,__func__);

  s5=STREAM5_SAMPLE_16_LIN;
  s3=STREAM5_SAMPLE_16_LIN;
  i2s=_3_3_f_f_5;
  
  s5|=STREAM5_RATE_44100;
  s3|=STREAM3_STREAM_STEREO|STREAM3_RATE_44100;
  
  cx2070x_real_write(i2c,PORT1_TX_CLOCKS_PER_FRAME_PHASE,i2s?0x03:0x01);
  cx2070x_real_write(i2c,PORT1_RX_CLOCKS_PER_FRAME_PHASE,i2s?0x03:0x01);
  cx2070x_real_write(i2c,PORT1_TX_SYNC_WIDTH,            i2s?0x0f:0x07);
  cx2070x_real_write(i2c,PORT1_RX_SYNC_WIDTH,            i2s?0x0f:0x07);
  cx2070x_real_write(i2c,PORT1_CONTROL_2,                i2s?0x05:0x00);
  cx2070x_real_write(i2c,STREAM5_RATE,s5);
  cx2070x_real_write(i2c,STREAM3_RATE,s3);// cause by incorrect parameter

  dsp=cx2070x_read_reg_cache(glp_reg_cache,DSP_INIT);

  if ((err=cx2070x_dsp_init(i2c,dsp|DSP_INIT_NEWC))<0)
      return err;

  return 0;
}

static int cx2070x_mute(struct i2c_client *i2c,int mute)
{
  INFO("%lu: %s(,%d) called\n",jiffies,__func__,mute);

#if 0 /* CONFIG_INNOPIATECH : MYSEO */
  cx2070x_real_write(i2c,VOLUME_MUTE,mute?VOLUME_MUTE_ALL:b_00000000);
#endif

  return 0;
}

static int cx2070x_set_dai_sysclk(int clk_id, unsigned int freq, int dir)
{
  INFO("%lu: %s() called\n",jiffies,__func__);
  return 0;
}

static int cx2070x_set_dai_fmt(unsigned int fmt)
{
  INFO("%lu: %s() called\n",jiffies,__func__);
  return 0;
}

int I2cWrite( struct i2c_client *i2c, unsigned char ChipAddr, unsigned int cbBuf, unsigned char* pBuf)
{
    struct i2c_msg      msg[1];

    INFO("%s()\n",__func__);

    msg[0].addr  = i2c->addr;
    msg[0].flags = i2c->flags & I2C_M_TEN;
    msg[0].buf   = pBuf;
    msg[0].len   = cbBuf;

	if (i2c_master_send(i2c, msg[0].buf, msg[0].len) != msg[0].len)
    {
        printk(KERN_ERR "cx2070x: I2cWrite failed.\n");
        return 0;
    }
    else
    {
        return 1;
    }
}

int I2cWriteThenRead( struct i2c_client *i2c, unsigned char ChipAddr, unsigned int cbBuf,
    unsigned char* pBuf, unsigned int cbReadBuf, unsigned char*pReadBuf)
{
    struct i2c_msg      msg[2];

    INFO("%s()\n",__func__);

    msg[0].addr  = i2c->addr;
    msg[0].flags = i2c->flags & I2C_M_TEN;
    msg[0].len   = cbBuf;
    msg[0].buf   = pBuf;

    msg[1].addr  = i2c->addr;
    msg[1].flags = (i2c->flags & I2C_M_TEN) | I2C_M_RD;
    msg[1].len   = cbReadBuf;
    msg[1].buf   = pReadBuf;

  	if (i2c_master_send(i2c, msg[0].buf, msg[0].len) != msg[0].len)
    {
        printk(KERN_ERR "%s(): I2cWriteThenRead write failed.\n",__func__);
        return 0;
    }
  	if (i2c_master_recv(i2c, msg[1].buf, msg[1].len) != msg[1].len)
    {
        printk(KERN_ERR "%s(): I2cWriteThenRead failed.\n",__func__);
        return 0;
    }
    else 
    {
        return 1;
    }
}


#if defined(CONFIG_SND_CX2070X_LOAD_FW)
static int cx2070x_apply_firmware_patch(struct i2c_client *i2c)
{
	int ret = 0;
    const struct firmware *fw = NULL;
    const unsigned char *dsp_code  = NULL;
    struct device dev = i2c->dev;	

    INFO("%s()\n",__func__);

    // load firmware from file.
    ret = request_firmware(&fw, CX2070X_FIRMWARE_FILENAME, &dev); 
    if (ret < 0) {
        printk( KERN_ERR "%s(): Firmware %s not available %d",__func__, CX2070X_FIRMWARE_FILENAME, ret);
    		return ret;
    }
    dsp_code = fw->data;
    
    ret = ApplyDSPChanges(dsp_code);
    if (ret) {
        printk(KERN_ERR "cx2070x: patch firmware failed, Error %d\n", ret);
    } else {
        printk(KERN_INFO "cx2070x: patch firmware successfully.\n");	
    }
    
	return ret;
}

static int cx2070x_download_firmware(struct i2c_client *i2c)
{
    int ret = 0;
    char *buf = NULL;
    const struct firmware *fw = NULL;
    const unsigned char *dsp_code = NULL;
    struct device dev = i2c->dev;	

    INFO("%s(): F/W Path = %s\n",__func__, CX2070X_FIRMWARE_FILENAME);

    // load firmware from file.
    ret = request_firmware(&fw, CX2070X_FIRMWARE_FILENAME, &dev); 
    if( ret < 0)
    {
        printk( KERN_ERR "%s(): Firmware %s not available %d",__func__,CX2070X_FIRMWARE_FILENAME,ret);
      	goto LEAVE;
    }
    dsp_code = fw->data;
    INFO("%s(): request_firmware Path = %s, size=%d\n",__func__, CX2070X_FIRMWARE_FILENAME, fw->size);

    //
    // Load rom data from a array.
    //
    buf = (char*)kzalloc(0x200,GFP_KERNEL);
    if (buf  == NULL)
    {
        printk(KERN_ERR "%s(): out of memory .\n",__func__);
        ret = -ENOMEM;
        goto LEAVE;
    }
    
    //
    // Setup the i2c callback function.
    //
    INFO("%s(): set up I2C .\n",__func__);
    SetupI2cWriteCallback( (void *) i2c, (fun_I2cWrite) I2cWrite,32);
    SetupI2cWriteThenReadCallback( (void *) i2c, (fun_I2cWriteThenRead) I2cWriteThenRead); 

    // download
    SetupMemoryBuffer(buf);
    
    ret = DownloadFW(dsp_code);
    if(ret)
    {
        printk(KERN_ERR "%s(): download firmware failed, Error %d\n",__func__,ret);
    }
    else
    {
        printk(KERN_INFO "%s(): download firmware successfully.\n",__func__);	
    }
    if (buf)
    {
        kfree(buf);
    }
LEAVE:

#if defined(CONFIG_SND_CX2070X_LOAD_FW)
    if(fw)
    {
        release_firmware(fw);
    }
#endif 
    return ret;

}
#endif

unsigned int (*hw_read)(struct snd_soc_codec *, unsigned int);

//
// Initialise the cx2070x  driver
// Register the mixer and dsp interfaces with the kernel
//
static int NOINLINE cx2070x_init(struct i2c_client *i2c)
{
  int                 n,vl,vh,vm,fh, fl,ret = 0;
  cx2070x_reg_t	      *reg_cache;

  INFO("%s():\n",__func__);

  glp_reg_cache = cx2070x_data;
  
#if defined(CONFIG_SND_CX2070X_GPIO_RESET)
  cx2070x_reset_device();
#endif 

#if defined(CONFIG_SND_CX2070X_LOAD_FW)
  ret = cx2070x_download_firmware(i2c);
  if( ret < 0)
  {
  	printk(KERN_ERR "%s(): failed to download firmware\n",__func__);
  	return ret;
  }
#endif

  // Verify that Channel/Balboa is ready.
  // May have to wait for ~5sec becore Channel/Balboa comes out of reset
  for(n=5000;!bNoHW;)
  {
      int abcode=cx2070x_real_read(i2c,ABORT_CODE);
      if (abcode==0x01)
          break;  // initialization done!
      if (--n==0)
      {
          printk(KERN_ERR "%s():Timeout waiting for cx2070x to come out of reset!\n",__func__);
          return -EIO;
      }
      msleep(1);
  }

  cx2070x_real_read(i2c,FIRMWARE_VERSION);
  cx2070x_real_read(i2c,PATCH_VERSION);
  cx2070x_real_read(i2c,CHIP_VERSION);
  cx2070x_real_read(i2c,RELEASE_TYPE);

  reg_cache = GET_REG_CACHE(glp_reg_cache);
  fl=(reg_cache[FIRMWARE_VERSION]>>0)&0xFF;
  fl=(fl>>4)*10+(fl&0xf);
  fh=(reg_cache[FIRMWARE_VERSION]>>8)&0xFF;
  
  // determine whether the codec is ROM version or not.
  if( fh == 5)
  {   //firmware 5.x
    	//shows the firmware patch version.
      cx2070x_real_read(i2c,ROM_PATCH_VER_HB);
      cx2070x_real_read(i2c,ROM_PATCH_VER_MB);
      cx2070x_real_read(i2c,ROM_PATCH_VER_LB);
      vh =  reg_cache[ROM_PATCH_VER_HB];
      vm =  reg_cache[ROM_PATCH_VER_MB];
      vl =  reg_cache[ROM_PATCH_VER_LB];
      printk("%s(): firmware version %u.%u, patch %u.%u.%u, chip CX2070%u (ROM)\n",__func__,fh,fl,vh,vm,vl,reg_cache[CHIP_VERSION]);
  }
  else if( fh == 4)
  {
      //firmware 4.x
      printk("%s(): firmware version %u.%u,  chip CX2070%u (RAM), ",__func__,fh,fl,reg_cache[CHIP_VERSION]);
      // shows the firmware release type.
    	switch(reg_cache[RELEASE_TYPE])
    	{
      	case 12: printk("Custom Release\n"); break;
      	case 14: printk("Engineering Release\n"); break;
      	case 15: printk("Field Release\n"); break;
      	default: printk("Release %u?\n",reg_cache[RELEASE_TYPE]); break;
    	}
  }
  else
  {
      printk("%s(): Unsupported firmware version %u.%u!!!\n",__func__,fh,fl);
      ret = -EINVAL;
    	goto card_err;
  }
  

  if (reg_cache[PATCH_VERSION])
  {
    	vl=(reg_cache[PATCH_VERSION]>>0)&0xFF;
    	vh=(reg_cache[PATCH_VERSION]>>8)&0xFF;
     	printk("%s(): CX2070X patch version %u.%u\n",__func__,vh,vl);
  }

  // Initialize the CX2070X regisers and/or read them as needed.
#if 1 /* MYSEO */
  write_regs_cx2070x (i2c);
#else
  for(n=0;n<noof(cx2070x_regs);n++)
      switch(cx2070x_regs[n].type&REG_TYPE_MASK)
  {
      case REG_TYPE_RO:
      case REG_TYPE_RW:
          cx2070x_real_read(i2c,n);
          break;
      case REG_TYPE_WI:
      case REG_TYPE_WC:
          cx2070x_real_write(i2c,n,cx2070x_data[n]);
          break;
#if defined(REG_TYPE_DM)
      case REG_TYPE_DM:
          break;
#endif
      default:
          snd_BUG();
  }
#endif

#if defined(CONFIG_SND_CX2070X_LOAD_FW)
  cx2070x_apply_firmware_patch(i2c);
#endif

#if defined(CONFIG_SND_CXLIFEGUARD)
  cxdbg_dev_init(i2c);
#endif 

  if( ret == 0)
  {
      printk(KERN_INFO "%s(): codec is ready.\n",__func__);
  }
  return ret;

card_err:
  return ret;
}


static int cx2070x_probe(struct i2c_client *i2c)
{
  INFO("%lu: %s() called\n",jiffies,__func__);
  printk(KERN_INFO "cx2070x codec driver version: %02x,%02x,%02x,%02x\n",(u8)((CX2070X_DRIVER_VERSION)>>24), 
    (u8)((CX2070X_DRIVER_VERSION)>>16),
    (u8)((CX2070X_DRIVER_VERSION)>>8),
    (u8)((CX2070X_DRIVER_VERSION)));
    
  return cx2070x_init(i2c);
}

static int cx2070x_i2c_probe(struct i2c_client *i2c, const struct i2c_device_id *id)
{
  struct cx2070x_priv      *cx2070x;
  struct device *dev;

  INFO("%lu: %s() called\n", jiffies, __func__);
  
  cx2070x = (struct cx2070x_priv *)kzalloc(sizeof(struct cx2070x_priv), GFP_KERNEL);
  if (cx2070x == NULL)
  {
      return -ENOMEM;
  }

  i2c_set_clientdata(i2c, cx2070x);

  cx2070x->control_data = (void*)i2c;
  //cx2070x->control_type =  SND_SOC_I2C;	// KJW

  cx2070x->input_sel = Cx_INPUT_SEL_BY_GPIO;
  cx2070x->output_sel = Cx_OUTPUT_SEL_BY_GPIO;
  
  dev = &i2c->dev;
  // KJW
	cx2070x->reset_gpio = devm_gpiod_get_optional(dev, "reset", GPIOD_OUT_LOW);				
	if (cx2070x->reset_gpio) {
		gpiod_set_value(cx2070x->reset_gpio, 0);
		mdelay(10);
		gpiod_set_value(cx2070x->reset_gpio, 1);
		mdelay(100);
	}
  cx2070x_probe(i2c);
  
  return 0;
}

static int cx2070x_i2c_remove(struct i2c_client *client)
{
#if defined(CONFIG_SND_CXLIFEGUARD)
  cxdbg_dev_exit();
#endif 
  kfree(i2c_get_clientdata(client));
  return 0;
}

static const struct i2c_device_id cx2070x_i2c_id[] = 
{
  { CX2070X_I2C_DRIVER_NAME, 0 },
  { }
};
MODULE_DEVICE_TABLE(i2c, cx2070x_i2c_id);

static const struct of_device_id cx2070x_of_match[] = {
	{ .compatible = "conexant,cx2070xctl", },
	{ }
};
MODULE_DEVICE_TABLE(of, cx2070x_of_match);
 
static struct i2c_driver cx2070x_i2c_driver = {
  .driver = {
    	.name = "cx2070xctl",
    	.owner = THIS_MODULE,
		.of_match_table = cx2070x_of_match,
   },
  .probe=cx2070x_i2c_probe,
  .remove=cx2070x_i2c_remove,
  .id_table=cx2070x_i2c_id,
};

module_i2c_driver(cx2070x_i2c_driver);

/* KJW
static  int __init cx2070x_modinit(void)
{
  int ret;

  INFO("%lu: %s() called\n",jiffies,__func__);

	ret = i2c_add_driver(&cx2070x_i2c_driver);
	if (ret != 0) {
		printk(KERN_ERR "Failed to register CX2070X I2C driver: %d\n", ret);
	}
  return ret;
}
module_init(cx2070x_modinit);

static void __exit cx2070x_exit(void)
{
  INFO("%lu: %s() called\n",jiffies,__func__);

  i2c_del_driver(&cx2070x_i2c_driver);
}
module_exit(cx2070x_exit);
*/

int CX_AUDDRV_VERSION = CX2070X_DRIVER_VERSION;
EXPORT_SYMBOL_GPL(CX_AUDDRV_VERSION);
MODULE_DESCRIPTION("ASoC cx2070x Codec Driver");
MODULE_LICENSE("GPL");

