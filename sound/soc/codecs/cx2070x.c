/*
* ALSA SoC CX2070X codec driver
*
* Copyright:   (C) 2009/2010 Conexant Systems
* Copyright:   (C) 2017 Arcturus Networks Inc.
*                  by Oleksandr Zhadan
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 as
* published by the Free Software Foundation.
*
*************************************************************************
*  2017.08 : Linux 4.x kernel support added
*  Based on :
*    Modified Date:  12/02/13
*    File Version:   3.8.0.21
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
#include <linux/firmware.h>
#include <linux/regmap.h>

#include "cx2070x.h"

#ifdef CONFIG_SND_SOC_CX2070X_SYSFS
extern int cx2070x_sysfs_alloc(struct cx2070x_priv *cx2070x);
#endif

#define CX2070X_RATES \
	(SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_11025 | SNDRV_PCM_RATE_16000 | \
	SNDRV_PCM_RATE_22050 | SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_44100 | \
	SNDRV_PCM_RATE_48000)

#define CX2070X_FORMATS \
	( SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S8 | SNDRV_PCM_FMTBIT_U16_LE | SNDRV_PCM_FMTBIT_S16_LE )

#define get_cx2070x_priv(_codec_) ((struct cx2070x_priv *) \
			snd_soc_codec_get_drvdata(codec))

static int newc_ev(struct snd_soc_dapm_widget *w, struct snd_kcontrol *kcontrol,
		   int nevent)
{
	/* execute the DSP change */
	struct snd_soc_codec *codec = snd_soc_dapm_to_codec(w->dapm);
	return 0;
}

static int cx2070x_hw_params(struct snd_pcm_substream *substream,
			     struct snd_pcm_hw_params *params,
			     struct snd_soc_dai *dai)
{
	//dev_info(dai->dev,"%s()",__func__);
	return 0;
}

static int cx2070x_mute(struct snd_soc_dai *dai, int mute)
{
	//dev_info(dai->dev,"%s()",__func__);
	return 0;
}

static int cx2070x_set_dai_sysclk(struct snd_soc_dai *dai, int clk_id,
				  unsigned int freq, int dir)
{
	//dev_info(dai->dev,"%s()",__func__);
	return 0;
}

static int cx2070x_set_dai_fmt(struct snd_soc_dai *dai, unsigned int fmt)
{
	//dev_info(dai->dev,"%s()",__func__);
	return 0;
}

struct snd_soc_dai_ops cx2070x_dai_ops;

struct snd_soc_dai_driver soc_codec_cx2070x_dai[NUM_OF_DAI];

EXPORT_SYMBOL_GPL(soc_codec_cx2070x_dai);

static int cx2070x_set_bias_level(struct snd_soc_codec *codec,
				  enum snd_soc_bias_level level)
{
	return 0;
}

static int cx2070x_codec_probe(struct snd_soc_codec *codec)
{
	struct cx2070x_priv *cx2070x = get_cx2070x_priv(codec);

	dev_err(codec->dev, "%s()",__func__);
	
	cx2070x->codec = codec;
	codec->control_data = cx2070x->regmap;

#ifdef CONFIG_SND_SOC_CX2070X_SYSFS
	cx2070x_sysfs_alloc(cx2070x);
#endif
	return 0;
}

static int cx2070x_codec_remove(struct snd_soc_codec *codec)
{
	cx2070x_set_bias_level(codec, SND_SOC_BIAS_OFF);
	return 0;
}

#ifdef CONFIG_PM
static int cx2070x_suspend(struct snd_soc_codec *codec)
{
	cx2070x_set_bias_level(codec, SND_SOC_BIAS_OFF);
	return 0;
}

static int cx2070x_resume(struct snd_soc_codec *codec)
{
	cx2070x_set_bias_level(codec, SND_SOC_BIAS_STANDBY);
	return 0;
}
#else
#define cx2070x_suspend NULL
#define cx2070x_resume NULL
#endif

static bool cx2070x_volatile_register(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case CXREG_ABCODE:
	case CXREG_UPDATE_CTR:
	case CXREG_DSP_INIT_NEWC:
		return 1;
	default:
		return 0;
	}
}

struct snd_soc_codec_driver soc_codec_dev_cx2070x;
const struct regmap_config cx2070x_regmap_config = {
	.reg_bits = 16,
	.val_bits = 8,
	//.max_register = CX2070X_REG_MAX,
	//.reg_defaults = cx2070x_reg_defaults,
	//.num_reg_defaults = ARRAY_SIZE(cx2070x_reg_defaults),
	//.volatile_reg = cx2070x_volatile_register,
	.cache_type = REGCACHE_RBTREE,
};
EXPORT_SYMBOL(cx2070x_regmap_config);

static int cx2070x_register_codec_driver(struct cx2070x_priv *cx2070x)
{
	int i;
	int ret;
	bool continue_probe = true;;

	dev_err(cx2070x->dev, "%s() Start\n",__func__);
	/*this is nesscarry for non gcc compilier */
	memset(&cx2070x_dai_ops, 0, sizeof(cx2070x_dai_ops));
	cx2070x_dai_ops.set_sysclk = cx2070x_set_dai_sysclk;
	cx2070x_dai_ops.set_fmt = cx2070x_set_dai_fmt;
	cx2070x_dai_ops.digital_mute = cx2070x_mute;
	cx2070x_dai_ops.hw_params = cx2070x_hw_params;

	/*this is nesscarry for non gcc compilier */
	memset(soc_codec_cx2070x_dai, 0, sizeof(soc_codec_cx2070x_dai));
	for (i = 0; i < NUM_OF_DAI; i++) {
		soc_codec_cx2070x_dai[i].name =
		    i == 0 ? DAI_DP1_NAME : DAI_DP2_NAME;
		soc_codec_cx2070x_dai[i].ops = &cx2070x_dai_ops;
		soc_codec_cx2070x_dai[i].capture.stream_name =
		    i == 0 ? CAPTURE_STREAM_NAME_1 : CAPTURE_STREAM_NAME_2;
		soc_codec_cx2070x_dai[i].capture.formats = CX2070X_FORMATS;
		soc_codec_cx2070x_dai[i].capture.rates = CX2070X_RATES;
		soc_codec_cx2070x_dai[i].capture.channels_min = 1;
		soc_codec_cx2070x_dai[i].capture.channels_max = 2;
		soc_codec_cx2070x_dai[i].playback.stream_name =
		    i == 0 ? PLAYBACK_STREAM_NAME_1 : PLAYBACK_STREAM_NAME_2;
		soc_codec_cx2070x_dai[i].playback.formats = CX2070X_FORMATS;
		soc_codec_cx2070x_dai[i].playback.rates = CX2070X_RATES;
		soc_codec_cx2070x_dai[i].playback.channels_min = 1;
		soc_codec_cx2070x_dai[i].playback.channels_max = 2;
		soc_codec_cx2070x_dai[i].symmetric_rates = 1;
	}
	/*this is nesscarry for non gcc compilier */
	memset(&soc_codec_dev_cx2070x, 0, sizeof(soc_codec_dev_cx2070x));
	soc_codec_dev_cx2070x.probe = cx2070x_codec_probe;
	soc_codec_dev_cx2070x.remove = cx2070x_codec_remove;
	soc_codec_dev_cx2070x.suspend = cx2070x_suspend;
	soc_codec_dev_cx2070x.resume = cx2070x_resume;

	/*
	soc_codec_dev_cx2070x.controls = cx2070x_snd_controls;
	soc_codec_dev_cx2070x.num_controls = ARRAY_SIZE(cx2070x_snd_controls);
	soc_codec_dev_cx2070x.dapm_widgets = cx2070x_dapm_widgets;
	soc_codec_dev_cx2070x.num_dapm_widgets =
	    ARRAY_SIZE(cx2070x_dapm_widgets);
	soc_codec_dev_cx2070x.dapm_routes = cx2070x_routes;
	soc_codec_dev_cx2070x.num_dapm_routes = ARRAY_SIZE(cx2070x_routes);
	soc_codec_dev_cx2070x.set_bias_level = cx2070x_set_bias_level;
	*/

	if (continue_probe) {
		ret =
		    snd_soc_register_codec(cx2070x->dev, &soc_codec_dev_cx2070x,
					   soc_codec_cx2070x_dai, NUM_OF_DAI);
		if (ret < 0)
			dev_err(cx2070x->dev, "Failed to register codec: %d\n",
				ret);
		else
			dev_dbg(cx2070x->dev, "%s: Register codec.\n",
				__func__);
	}
	dev_err(cx2070x->dev, "%s() End\n",__func__);
	return ret;
}

int cx2070x_probe(struct device *dev, struct regmap *regmap)
{
	struct cx2070x_priv *cx2070x;

	dev_err(dev, "%s()",__func__);
	
	cx2070x =
	    (struct cx2070x_priv *)devm_kzalloc(dev,
						sizeof(struct cx2070x_priv),
						GFP_KERNEL);
	if (cx2070x == NULL) {
		dev_err(dev, "Out of memory!\n");
		return -ENOMEM;
	}

	cx2070x->dev = dev;
	cx2070x->codec_drv = &soc_codec_dev_cx2070x;
	cx2070x->dai_drv = soc_codec_cx2070x_dai;
	cx2070x->num_dai = NUM_OF_DAI;
	cx2070x->regmap = regmap;
	mutex_init(&cx2070x->update_lock);
	
	// KJW
	/*
	cx2070x->reset_gpio = devm_gpiod_get_optional(dev, "reset", GPIOD_OUT_LOW);				
	if (cx2070x->reset_gpio) {
		mdelay(10);
		gpiod_set_value(cx2070x->reset_gpio, 1);
		mdelay(100);
	}
	*/

	dev_set_drvdata(dev, cx2070x);

	return cx2070x_register_codec_driver(cx2070x);
}
EXPORT_SYMBOL(cx2070x_probe);

EXPORT_SYMBOL_GPL(soc_codec_dev_cx2070x);
MODULE_DESCRIPTION("ASoC cx2070x Codec Driver");
MODULE_AUTHOR("Simon Ho <simon.ho@conexant.com>");
MODULE_LICENSE("GPL");
