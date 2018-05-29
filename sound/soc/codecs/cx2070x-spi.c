/*
 * Conexant CX2070X audio codec spi driver
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/regmap.h>
#include <linux/spi/spi.h>
#include <sound/soc.h>

#include "cx2070x.h"

static int cx2070x_spi_probe(struct spi_device *spi)
{
	int ret;
	struct regmap *regmap;

	dev_dbg(&spi->dev, "probing cx2070x spi device\n");

	spi->mode = SPI_MODE_0;
	ret = spi_setup(spi);
	if (ret < 0)
		return ret;

	regmap = devm_regmap_init_spi(spi, &cx2070x_regmap_config);

	return cx2070x_probe(&spi->dev, regmap);
}

static int cx2070x_spi_remove(struct spi_device *spi)
{
	snd_soc_unregister_codec(&spi->dev);
	return 0;
}

static struct spi_driver cx2070x_spi = {
	.driver = {
		.name = "cx2070x",
	},
	.probe = cx2070x_spi_probe,
	.remove = cx2070x_spi_remove,
};

module_spi_driver(cx2070x_spi);

MODULE_DESCRIPTION("Conexant CX2070X ALSA SoC Codec SPI Driver");
MODULE_AUTHOR("Chanho Park <chanho61.park@samsung.com>");
MODULE_LICENSE("GPL");
