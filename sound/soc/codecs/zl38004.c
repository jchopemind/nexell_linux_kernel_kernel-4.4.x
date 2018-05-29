/*
 * zl38004.c  --  ZL38004 Audio Codec driver
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
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

#include "zl38004.h"

#ifdef CONFIG_SND_SOC_ZL38004_SYSFS
extern int zl38004_sysfs_alloc(struct zl38004_priv *zl38004);
#endif

#define ZL38004_RATES \
	(SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_11025 | SNDRV_PCM_RATE_16000 | \
	SNDRV_PCM_RATE_22050 | SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_44100 | \
	SNDRV_PCM_RATE_48000)

#define ZL38004_FORMATS \
	( SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S8 | SNDRV_PCM_FMTBIT_U16_LE | SNDRV_PCM_FMTBIT_S16_LE )

#define get_zl38004_priv(_codec_) ((struct zl38004_priv *) \
			snd_soc_codec_get_drvdata(codec))

static int newc_ev(struct snd_soc_dapm_widget *w, struct snd_kcontrol *kcontrol,
		   int nevent)
{
	/* execute the DSP change */
	struct snd_soc_codec *codec = snd_soc_dapm_to_codec(w->dapm);
	return 0;
}

static int zl38004_hw_params(struct snd_pcm_substream *substream,
			     struct snd_pcm_hw_params *params,
			     struct snd_soc_dai *dai)
{
	//dev_info(dai->dev,"%s()",__func__);
	return 0;
}

static int zl38004_mute(struct snd_soc_dai *dai, int mute)
{
	//dev_info(dai->dev,"%s()",__func__);
	return 0;
}

static int zl38004_set_dai_sysclk(struct snd_soc_dai *dai, int clk_id,
				  unsigned int freq, int dir)
{
	//dev_info(dai->dev,"%s()",__func__);
	return 0;
}

static int zl38004_set_dai_fmt(struct snd_soc_dai *dai, unsigned int fmt)
{
	//dev_info(dai->dev,"%s()",__func__);
	return 0;
}

struct snd_soc_dai_ops zl38004_dai_ops;

struct snd_soc_dai_driver soc_codec_zl38004_dai[NUM_OF_DAI];

EXPORT_SYMBOL_GPL(soc_codec_zl38004_dai);

static int zl38004_set_bias_level(struct snd_soc_codec *codec,
				  enum snd_soc_bias_level level)
{
	return 0;
}

static int zl38004_codec_probe(struct snd_soc_codec *codec)
{
	struct zl38004_priv *zl38004 = get_zl38004_priv(codec);

	dev_err(codec->dev, "%s()",__func__);
	
	zl38004->codec = codec;
	codec->control_data = zl38004->regmap;

#ifdef CONFIG_SND_SOC_ZL38004_SYSFS
	zl38004_sysfs_alloc(zl38004);
#endif
	return 0;
}

static int zl38004_codec_remove(struct snd_soc_codec *codec)
{
	zl38004_set_bias_level(codec, SND_SOC_BIAS_OFF);
	return 0;
}

#ifdef CONFIG_PM
static int zl38004_suspend(struct snd_soc_codec *codec)
{
	zl38004_set_bias_level(codec, SND_SOC_BIAS_OFF);
	return 0;
}

static int zl38004_resume(struct snd_soc_codec *codec)
{
	zl38004_set_bias_level(codec, SND_SOC_BIAS_STANDBY);
	return 0;
}
#else
#define zl38004_suspend NULL
#define zl38004_resume NULL
#endif

static bool zl38004_volatile_register(struct device *dev, unsigned int reg)
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

struct snd_soc_codec_driver soc_codec_dev_zl38004;
const struct regmap_config zl38004_regmap_config = {
	.reg_bits = 16,
	.val_bits = 8,
	//.max_register = ZL38004_REG_MAX,
	//.reg_defaults = zl38004_reg_defaults,
	//.num_reg_defaults = ARRAY_SIZE(zl38004_reg_defaults),
	//.volatile_reg = zl38004_volatile_register,
	.cache_type = REGCACHE_RBTREE,
};
EXPORT_SYMBOL(zl38004_regmap_config);

static int zl38004_register_codec_driver(struct zl38004_priv *zl38004)
{
	int i;
	int ret;
	bool continue_probe = true;;

	dev_err(zl38004->dev, "%s() Start\n",__func__);
	/*this is nesscarry for non gcc compilier */
	memset(&zl38004_dai_ops, 0, sizeof(zl38004_dai_ops));
	zl38004_dai_ops.set_sysclk = zl38004_set_dai_sysclk;
	zl38004_dai_ops.set_fmt = zl38004_set_dai_fmt;
	zl38004_dai_ops.digital_mute = zl38004_mute;
	zl38004_dai_ops.hw_params = zl38004_hw_params;

	/*this is nesscarry for non gcc compilier */
	memset(soc_codec_zl38004_dai, 0, sizeof(soc_codec_zl38004_dai));
	for (i = 0; i < NUM_OF_DAI; i++) {
		soc_codec_zl38004_dai[i].name =
		    i == 0 ? DAI_DP1_NAME : DAI_DP2_NAME;
		soc_codec_zl38004_dai[i].ops = &zl38004_dai_ops;
		soc_codec_zl38004_dai[i].capture.stream_name =
		    i == 0 ? CAPTURE_STREAM_NAME_1 : CAPTURE_STREAM_NAME_2;
		soc_codec_zl38004_dai[i].capture.formats = ZL38004_FORMATS;
		soc_codec_zl38004_dai[i].capture.rates = ZL38004_RATES;
		soc_codec_zl38004_dai[i].capture.channels_min = 1;
		soc_codec_zl38004_dai[i].capture.channels_max = 2;
		soc_codec_zl38004_dai[i].playback.stream_name =
		    i == 0 ? PLAYBACK_STREAM_NAME_1 : PLAYBACK_STREAM_NAME_2;
		soc_codec_zl38004_dai[i].playback.formats = ZL38004_FORMATS;
		soc_codec_zl38004_dai[i].playback.rates = ZL38004_RATES;
		soc_codec_zl38004_dai[i].playback.channels_min = 1;
		soc_codec_zl38004_dai[i].playback.channels_max = 2;
		soc_codec_zl38004_dai[i].symmetric_rates = 1;
	}
	/*this is nesscarry for non gcc compilier */
	memset(&soc_codec_dev_zl38004, 0, sizeof(soc_codec_dev_zl38004));
	soc_codec_dev_zl38004.probe = zl38004_codec_probe;
	soc_codec_dev_zl38004.remove = zl38004_codec_remove;
	soc_codec_dev_zl38004.suspend = zl38004_suspend;
	soc_codec_dev_zl38004.resume = zl38004_resume;

	/*
	soc_codec_dev_zl38004.controls = zl38004_snd_controls;
	soc_codec_dev_zl38004.num_controls = ARRAY_SIZE(zl38004_snd_controls);
	soc_codec_dev_zl38004.dapm_widgets = zl38004_dapm_widgets;
	soc_codec_dev_zl38004.num_dapm_widgets =
	    ARRAY_SIZE(zl38004_dapm_widgets);
	soc_codec_dev_zl38004.dapm_routes = zl38004_routes;
	soc_codec_dev_zl38004.num_dapm_routes = ARRAY_SIZE(zl38004_routes);
	soc_codec_dev_zl38004.set_bias_level = zl38004_set_bias_level;
	*/

	if (continue_probe) {
		ret =
		    snd_soc_register_codec(zl38004->dev, &soc_codec_dev_zl38004,
					   soc_codec_zl38004_dai, NUM_OF_DAI);
		if (ret < 0)
			dev_err(zl38004->dev, "Failed to register codec: %d\n",
				ret);
		else
			dev_dbg(zl38004->dev, "%s: Register codec.\n",
				__func__);
	}
	dev_err(zl38004->dev, "%s() End\n",__func__);
	return ret;
}

int zl38004_probe(struct device *dev, struct regmap *regmap)
{
	struct zl38004_priv *zl38004;

	dev_err(dev, "%s()",__func__);
	
	zl38004 =
	    (struct zl38004_priv *)devm_kzalloc(dev,
						sizeof(struct zl38004_priv),
						GFP_KERNEL);
	if (zl38004 == NULL) {
		dev_err(dev, "Out of memory!\n");
		return -ENOMEM;
	}

	zl38004->dev = dev;
	zl38004->codec_drv = &soc_codec_dev_zl38004;
	zl38004->dai_drv = soc_codec_zl38004_dai;
	zl38004->num_dai = NUM_OF_DAI;
	zl38004->regmap = regmap;
	mutex_init(&zl38004->update_lock);
	
	// KJW
	/*
	zl38004->reset_gpio = devm_gpiod_get_optional(dev, "reset", GPIOD_OUT_LOW);				
	if (zl38004->reset_gpio) {
		mdelay(10);
		gpiod_set_value(zl38004->reset_gpio, 1);
		mdelay(100);
	}
	*/

	dev_set_drvdata(dev, zl38004);

	return zl38004_register_codec_driver(zl38004);
}
EXPORT_SYMBOL(zl38004_probe);

EXPORT_SYMBOL_GPL(soc_codec_dev_zl38004);

MODULE_DESCRIPTION("ASoC zl38004 driver");
MODULE_AUTHOR("Euijae Lee");
MODULE_LICENSE("GPL");
