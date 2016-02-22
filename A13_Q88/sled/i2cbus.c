
#include <sys/ioctl.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <i2c/smbus.h>

#include "i2cbus.h"

int open_i2c_dev(char *filename){
int file = open(filename, O_RDWR);	
	if (file < 0) {
		fprintf(stderr, "Error: Could not open bus %s : %s\n",
				filename, strerror(errno));	
	}
	return file;
}

int set_slave_addr(int file, int address){	
	if ( ioctl(file, I2C_SLAVE, address) < 0) {
		fprintf(stderr,
			"Error: Could not set address to 0x%02x: %s\n",
			address, strerror(errno));
		return -errno;
	}
	return 0;
}
