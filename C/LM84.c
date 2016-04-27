// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// LM84
// This code is designed to work with the LM84_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/products

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

void main() 
{
	// Create I2C bus
	int file;
	char *bus = "/dev/i2c-1";
	if((file = open(bus, O_RDWR)) < 0) 
	{
		printf("Failed to open the bus. \n");
		exit(1);
	}
	// Get I2C device, LM84 I2C address is 0x18(24)
	ioctl(file, I2C_SLAVE, 0x18);

	// Select Configuration register(0x09)
	// Read Local temperature(0x80)
	char config[2] = {0};
	config[0] = 0x09;
	config[1] = 0x80;
	write(file, config, 2);
	sleep(1);

	// Read 1 byte of data from register(0x00)
	char reg[1] = {0x00};
	write(file, reg, 1);
	char data[1] = {0};
	if(read(file, data, 1) != 1)
	{
		printf("Error : Input/output Error \n");
	}
	else
	{
		// Convert the data
		float cTemp = data[0];
		float fTemp = cTemp * 1.8 + 32;

		// Output data to screen
		printf("Temperature in Celsius : %.2f C \n", cTemp);
		printf("Temperature in Fahrenheit : %.2f F \n", fTemp);
	}
}
