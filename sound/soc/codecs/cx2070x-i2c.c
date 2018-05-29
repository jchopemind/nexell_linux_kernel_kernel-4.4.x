/*
 * Conexant CX2070X audio codec i2c driver
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

#include <linux/i2c.h>
#include <linux/module.h>
#include <sound/soc.h>

#include "cx2070x.h"

static int cx2070x_i2c_probe(struct i2c_client *i2c,
			     const struct i2c_device_id *id)
{
	int ret = cx2070x_probe(&i2c->dev,
			devm_regmap_init_i2c(i2c, &cx2070x_regmap_config));
	if (ret)
		return ret;

	return 0;
}

static int cx2070x_i2c_remove(struct i2c_client *i2c)
{
	snd_soc_unregister_codec(&i2c->dev);

	return 0;
}

static struct i2c_device_id cx2070x_i2c_id[] = {
	{ "cx2070x", 0, },
	{ }
};
MODULE_DEVICE_TABLE(i2c, cx2070x_i2c_id);

static const struct of_device_id cx2070x_of_match[] = {
	{ .compatible = "conexant,cx2070x", },
	{ }
};
MODULE_DEVICE_TABLE(of, cx2070x_of_match);

static struct i2c_driver cx2070x_i2c_driver = {
	.driver = {
		.name = "cx2070x",
		.of_match_table = cx2070x_of_match,
	},
	.probe = cx2070x_i2c_probe,
	.remove = cx2070x_i2c_remove,
	.id_table = cx2070x_i2c_id,
};

module_i2c_driver(cx2070x_i2c_driver);

MODULE_DESCRIPTION("Conexant CX2070X ALSA SoC Codec I2C Driver");
MODULE_AUTHOR("Chanho Park <chanho61.park@samsung.com>");
MODULE_LICENSE("GPL");
