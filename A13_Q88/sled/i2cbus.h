#ifndef _i2cbus_h_
#define _i2cbus_h_

int open_i2c_dev(char *filename);
int set_slave_addr(int file, int address);

#endif
