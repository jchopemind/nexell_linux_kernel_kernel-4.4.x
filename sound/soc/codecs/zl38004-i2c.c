/*
 * Zarlink ZL38004 audio codec i2c driver
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

#include <linux/i2c.h>
#include <linux/module.h>
#include <sound/soc.h>

#include "zl38004.h"

static int zl38004_i2c_probe(struct i2c_client *i2c,
			     const struct i2c_device_id *id)
{
	int ret = zl38004_probe(&i2c->dev,
			devm_regmap_init_i2c(i2c, &zl38004_regmap_config));
	if (ret)
		return ret;

	return 0;
}

static int zl38004_i2c_remove(struct i2c_client *i2c)
{
	snd_soc_unregister_codec(&i2c->dev);

	return 0;
}

static struct i2c_device_id zl38004_i2c_id[] = {
	{ "zl38004", 0, },
	{ }
};
MODULE_DEVICE_TABLE(i2c, zl38004_i2c_id);

static const struct of_device_id zl38004_of_match[] = {
	{ .compatible = "zarlink,zl38004", },
	{ }
};
MODULE_DEVICE_TABLE(of, zl38004_of_match);

static struct i2c_driver zl38004_i2c_driver = {
	.driver = {
		.name = "zl38004",
		.of_match_table = zl38004_of_match,
	},
	.probe = zl38004_i2c_probe,
	.remove = zl38004_i2c_remove,
	.id_table = zl38004_i2c_id,
};

module_i2c_driver(zl38004_i2c_driver);

MODULE_DESCRIPTION("Zarlink ZL38004 ALSA SoC Codec I2C Driver");
MODULE_AUTHOR("Chanho Park <chanho61.park@samsung.com>");
MODULE_LICENSE("GPL");
