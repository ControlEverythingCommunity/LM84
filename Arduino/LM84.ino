// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// LM84
// This code is designed to work with the LM84_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/products

#include<Wire.h>

// LM84 I2C address is 0x18(24)
#define Addr 0x18

void setup()
{
  // Initialise I2C communication
  Wire.begin();
  // Initialise Serial Communication
  Serial.begin(9600);

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select Configuration register
  Wire.write(0x09);
  // Read local temperature
  Wire.write(0x80);
  // Stop I2C Transmission
  Wire.endTransmission();
  delay(300);
}

void loop() 
{
  int cTemp = 0, fTemp = 0;
  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select data register
  Wire.write(0x00);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Request 1 byte of data
  Wire.requestFrom(Addr, 1);

  // Read the byte
  if(Wire.available() == 1)
  {
    cTemp = Wire.read();
  }
  
  // Covert the data
  fTemp = cTemp * 1.8 + 32;
  
  // Output data to serial monitor
  Serial.print("Temperature in celsius : ");
  Serial.println(cTemp);
  Serial.print("Temperature in Fahrenheit : ");
  Serial.println(fTemp);
  delay(1000);
}

