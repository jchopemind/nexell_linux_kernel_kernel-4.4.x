#ifndef __CM130PC20_H__
#define __CM130PC20_H__

#define CM130PC20_SENSOR_I2C_ADDR       	0x40
#define CM130PC20_REG_TERM 			        0x00	        /* terminating list entry for reg */
#define CM130PC20_VAL_TERM 			        0x00	        /* terminating list entry for val */
#define CM130PC20_FRAMERATE					15

struct sensor_reg {
	unsigned short reg;
	unsigned char val;
};

struct capture_size {
	unsigned long width;
	unsigned long height;
};

extern struct capture_size sensor_sizes[];

#endif