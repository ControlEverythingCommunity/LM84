# Distributed with a free-will license.
# Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
# LM84
# This code is designed to work with the LM84_I2CS I2C Mini Module available from ControlEverything.com.
# https://www.controleverything.com/products

from OmegaExpansion import onionI2C
import time

# Get I2C bus
i2c = onionI2C.OnionI2C()

# LM84 address, 0x18(24)
# Select configuration register, 0x09(09)
#		0x80(128)	Read Local temperature
i2c.writeByte(0x18, 0x09, 0x80)

time.sleep(0.5)

# LM84 address, 0x18(24)
# Read data back from 0x00(00), 1 byte
data = i2c.readBytes(0x18, 0x00, 1)

# Convert the data
cTemp = data[0]
fTemp = cTemp * 1.8 + 32

# Output data to screen
print "Temperature in Celsius : %.2f C" %cTemp
print "Temperature in Fahrenheit : %.2f F" %fTemp
