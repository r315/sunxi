
#include <sys/ioctl.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <i2c/smbus.h>

#include "i2cbus.h"
#include "sled.h"



#define MISSING_FUNC_FMT	"Error: Adapter does not have %s capability\n"

char checkIo(int file, int size){
unsigned long funcs;

	/* check adapter functionality */
	if (ioctl(file, I2C_FUNCS, &funcs) < 0) {
		fprintf(stderr, "Error: Could not get the adapter "
			"functionality matrix: %s\n", strerror(errno));
		return -1;
	}

	switch (size) {
	case I2C_SMBUS_BYTE:
		if (!(funcs & I2C_FUNC_SMBUS_WRITE_BYTE)) {
			fprintf(stderr, MISSING_FUNC_FMT, "SMBus send byte");
			return -1;
		}
		break;

	case I2C_SMBUS_BYTE_DATA:
		if (!(funcs & I2C_FUNC_SMBUS_WRITE_BYTE_DATA)) {
			fprintf(stderr, MISSING_FUNC_FMT, "SMBus write byte");
			return -1;
		}
		break;
	default:
		fprintf(stderr,"Size not supported\n",size);
			return -1;
	}

	return 0;

}


char setColor(char color){
int file;

	file = open_i2c_dev(I2C_BUS);	
	if (file < 0  || checkIo(file, I2C_SMBUS_BYTE_DATA)  || 
			set_slave_addr(file,  I2CIOEXPANDER))
		return -1;


	 if( i2c_smbus_write_byte(file, ~color) < 0){
		fprintf(stderr, "Error: Write failed\n");
		close(file);
		return -1;
	}

	close(file);
return color;
}
