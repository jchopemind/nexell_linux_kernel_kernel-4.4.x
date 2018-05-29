/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see < http://www.gnu.org/licenses/ >.
 */
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <sound/pcm.h>
#include <sound/pcm_params.h>
#include <sound/soc.h>
#include <sound/soc-dai.h>
#include <sound/jack.h>
#include "nexell-i2s.h"

#define I2S_BASEADDR 0xC0055000
#define I2S_CH_OFFSET 0x1000

#define DEBUG

//static char str_dai_name[16] = "c0055000.i2s";
static char str_dai_name[16] = "c0056000.i2s";
static struct snd_soc_codec *cx2070x;

static int cx2070x_hw_params(struct snd_pcm_substream *substream,
			struct snd_pcm_hw_params *params)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_dai *codec_dai = rtd->codec_dai;
	/* 48K * 256 = 12.288 Mhz */
	unsigned int freq = params_rate(params) * 256;
	unsigned int fmt = SND_SOC_DAIFMT_I2S |
			SND_SOC_DAIFMT_NB_NF | SND_SOC_DAIFMT_CBS_CFS;
	int ret = 0;

	ret = snd_soc_dai_set_sysclk(codec_dai, 0, freq,
					SND_SOC_CLOCK_IN);
	if (0 > ret)
		return ret;

	ret = snd_soc_dai_set_fmt(codec_dai, fmt);

	if (0 > ret)
		return ret;
	return ret;
}

static int cx2070x_suspend_pre(struct snd_soc_card *card)
{
	return 0;
}

static int cx2070x_resume_pre(struct snd_soc_card *card)
{
	return 0;
}

static int cx2070x_resume_post(struct snd_soc_card *card)
{
	return 0;
}

static struct snd_soc_ops cx2070x_ops = {
	.hw_params = cx2070x_hw_params,
};

static const struct snd_soc_dapm_widget cx2070x_dapm_widgets[] = {
	/* TODO: change initial path */
	SND_SOC_DAPM_HP("Headphone Jack", NULL),
	/* TODO: change initial path */
	SND_SOC_DAPM_MIC("Main Mic", NULL),
};

/* Corgi machine audio map (connections to the codec pins) */
static const struct snd_soc_dapm_route cx2070x_audio_map[] = {
	/* headphone connected to HPOL, HPOR */ /* TODO: change initial path */
	{"Headphone Jack", NULL, "HPOL"},
	{"Headphone Jack", NULL, "HPOR"},
	/* speaker connected to HPOL, HPOR */ /* TODO: change initial path */
	{"Ext Spk", NULL, "HPOL"},
	{"Ext Spk", NULL, "HPOR"},
	/* Main Mic Connected to IN2P */
	{"IN2P", NULL, "MICBIAS1"},
	{"IN2P", NULL, "Main Mic"},
};

static int cx2070x_dai_init(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_soc_codec *codec = rtd->codec;
	struct snd_soc_dapm_context *dapm = snd_soc_codec_get_dapm(codec);

	cx2070x = codec;
	/* set endpoints to not connected */
	snd_soc_dapm_nc_pin(dapm, "DMIC");/* TODO: change initial path */
	snd_soc_dapm_nc_pin(dapm, "MIC2");/* TODO: change initial path */

	/* to power up alc5658 (HP Depop: hp_event) */
	snd_soc_dapm_enable_pin(dapm, "Headphone Jack");
	/* TODO: change initial path */
	snd_soc_dapm_sync(dapm);

	return 0;
}

static struct snd_soc_dai_link cx2070x_dai_link = {
	.name = "ASOC-CX2070X",
	.stream_name = "CX2070X_DP1",
	.cpu_dai_name = str_dai_name,
	.codec_dai_name = "cx2070x-dp1",
	.ops = &cx2070x_ops,
	.symmetric_rates = 1,
	.init = cx2070x_dai_init,
};

static struct snd_soc_card cx2070x_card = {
	.name = "I2S-CX2070X", /* proc/asound/cards */
	.owner = THIS_MODULE,
	.dai_link = &cx2070x_dai_link,
	.num_links = 1,
	.suspend_pre = &cx2070x_suspend_pre,
	.resume_pre = &cx2070x_resume_pre,
	.resume_post = &cx2070x_resume_post,
	.dapm_widgets = cx2070x_dapm_widgets,
	.num_dapm_widgets = ARRAY_SIZE(cx2070x_dapm_widgets),
	.dapm_routes = cx2070x_audio_map,
	.num_dapm_routes = ARRAY_SIZE(cx2070x_audio_map),
};

/*
 * codec driver
 */
static int cx2070x_probe(struct platform_device *pdev)
{
	struct snd_soc_card *card = &cx2070x_card;
	struct snd_soc_dai_driver *i2s_dai = NULL;
	int ret;

	dev_err(&pdev->dev, "%s()",__func__);
	card->dev = &pdev->dev;
	if (!cx2070x_dai_link.codec_name) {
		cx2070x_dai_link.codec_name = NULL;
		cx2070x_dai_link.codec_of_node = of_parse_phandle(
		pdev->dev.of_node, "audio-codec", 0);
		if (!cx2070x_dai_link.codec_of_node) {
			dev_err(&pdev->dev,
			    "Property 'audio-codec' missing or invalid\n");
		}
	}

	ret = snd_soc_register_card(card);
	if (ret) {
		dev_err(&pdev->dev,
			"snd_soc_register_card() failed: %d\n", ret);
		return ret;
	}

	if (card->rtd) {
		struct snd_soc_dai *cpu_dai = card->rtd->cpu_dai;

		if (cpu_dai)
			i2s_dai = cpu_dai->driver;
	}
	dev_dbg(&pdev->dev, "cx2070x-dai: register card %s -> %s\n",
			card->dai_link->codec_dai_name,
			card->dai_link->cpu_dai_name);
	if (NULL == i2s_dai)
		return 0;
	return ret;
}

static int cx2070x_remove(struct platform_device *pdev)
{
	struct snd_soc_card *card = platform_get_drvdata(pdev);

	snd_soc_unregister_card(card);
	return 0;
}
#ifdef CONFIG_OF
static const struct of_device_id nx_cx2070x_match[] = {
	{ .compatible = "nexell,nexell-cx2070x" },
	{},
};
MODULE_DEVICE_TABLE(of, nx_cx2070x_match);
#else
#define nx_alc5658_match NULL
#endif

static struct platform_driver cx2070x_driver = {
	.driver = {
		.name = "cx2070x-audio",
		.owner = THIS_MODULE,
		.pm = &snd_soc_pm_ops, /* for suspend */
		.of_match_table = of_match_ptr(nx_cx2070x_match),
	},
	.probe = cx2070x_probe,
	.remove = cx2070x_remove,
};
module_platform_driver(cx2070x_driver);

MODULE_AUTHOR("Geonho Kim < gh007.kim@samsung.com >");
MODULE_DESCRIPTION("Sound codec-cx2070x driver for Nexell sound");
MODULE_LICENSE("GPL");
