// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// LM84
// This code is designed to work with the LM84_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/products

import com.pi4j.io.i2c.I2CBus;
import com.pi4j.io.i2c.I2CDevice;
import com.pi4j.io.i2c.I2CFactory;
import java.io.IOException;

public class LM84
{
	public static void main(String args[]) throws Exception
	{
		// Create I2CBus
		I2CBus bus = I2CFactory.getInstance(I2CBus.BUS_1);
		// Get I2C device, LM84 I2C address is 0x18(24)
		I2CDevice device = bus.getDevice(0x18);

		// Select Configuration register
		// Read Local temperature
		device.write(0x09,(byte)0x80);

		// Read 1 byte of data from address 0x00(00)
		byte[] data = new byte[1];
		device.read(0x00, data, 0, 1);

		// Convert data
		double cTemp = data[0];
		double fTemp = cTemp * 1.8 + 32;

		// Output data to screen
		System.out.printf("Temperature in Celsius : %.2f C %n", cTemp);
		System.out.printf("Temperature in Fahrenheit : %.2f F %n", fTemp);
	}
}
