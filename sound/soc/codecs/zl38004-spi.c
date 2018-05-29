/*
 * Zarlink ZL38004 audio codec spi driver
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/regmap.h>
#include <linux/spi/spi.h>
#include <sound/soc.h>

#include "zl38004.h"

static int zl38004_spi_probe(struct spi_device *spi)
{
	int ret;
	struct regmap *regmap;

	dev_dbg(&spi->dev, "probing zl38004 spi device\n");

	spi->mode = SPI_MODE_0;
	ret = spi_setup(spi);
	if (ret < 0)
		return ret;

	regmap = devm_regmap_init_spi(spi, &zl38004_regmap_config);

	return zl38004_probe(&spi->dev, regmap);
}

static int zl38004_spi_remove(struct spi_device *spi)
{
	snd_soc_unregister_codec(&spi->dev);
	return 0;
}

static struct spi_driver zl38004_spi = {
	.driver = {
		.name = "zl38004",
	},
	.probe = zl38004_spi_probe,
	.remove = zl38004_spi_remove,
};

module_spi_driver(zl38004_spi);

MODULE_DESCRIPTION("Zarlink ZL38004 ALSA SoC Codec SPI Driver");
MODULE_AUTHOR("Chanho Park <chanho61.park@samsung.com>");
MODULE_LICENSE("GPL");
