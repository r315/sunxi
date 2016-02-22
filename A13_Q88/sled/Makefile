# Copyright (C) 2012       Alejandro Mery <amery@geeks.cl>
# Copyright (C) 2012,2013  Henrik Nordstrom <henrik@henriknordstrom.net>
# Copyright (C) 2013       Patrick Wood <patrickhwood@gmail.com>
# Copyright (C) 2013       Pat Wood <Pat.Wood@efi.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

CC = gcc
CFLAGS = -g -O0 
#-Wall -Wextra
CFLAGS += -std=c99 -D_POSIX_C_SOURCE=200112L
CFLAGS += -I../i2c-tools/include/

TOOLS = sled

CROSS_COMPILE ?= arm-none-eabi-

.PHONY: all clean

all: sled


clean:
	@rm -vf $(TOOLS) $(MISC_TOOLS) *.o *.elf *.sunxi *.bin *.nm *.orig

sled: sled.c sled.h test.c
	$(CC) $(CFLAGS) -c -o sled.o sled.c
	$(CC) $(CFLAGS) -c -o i2cbus.o i2cbus.c
	$(CC) $(CFLAGS) -c -o test.o test.c
	$(CC) $(CFLAGS) -c -o smbus.o smbus.c
	$(CC) $(LDFLAGS) -o $@ test.o smbus.o i2cbus.o sled.o $(LIBS)

%: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(filter %.c,$^) $(LIBS)


