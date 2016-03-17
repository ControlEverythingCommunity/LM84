# Distributed with a free-will license.
# Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
# LM84
# This code is designed to work with the LM84_I2CS I2C Mini Module available from ControlEverything.com.
# https://www.controleverything.com/products

import smbus
import time

# Get I2C bus
bus = smbus.SMBus(1)

# LM84 address, 0x18(24)
# Select configuration register, 0x09(09)
#		0x80(128)	Read Local temperature
bus.write_byte_data(0x18, 0x09, 0x80)

time.sleep(0.5)

# LM84 address, 0x18(24)
# Read data back from 0x00(00), 1 byte
data = bus.read_byte_data(0x18, 0x00)

# Convert the data
cTemp = data
fTemp = cTemp * 1.8 + 32

# Output data to screen
print "Temperature in Celsius : %.2f C" %cTemp
print "Temperature in Fahrenheit : %.2f F" %fTemp
