// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// LM84
// This code is designed to work with the LM84_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/products

#include <application.h>
#include <spark_wiring_i2c.h>

// LM84 I2C address is 0x18(24)
#define Addr 0x18

float cTemp = 0, fTemp = 0;
void setup()
{
    // Set variable
    Particle.variable("i2cdevice", "LM84");
    Particle.variable("cTemp", cTemp);
    
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
    // Start I2C Transmission
    Wire.beginTransmission(Addr);
    // Select data register
    Wire.write(0x00);
    // Stop I2C Transmission
    Wire.endTransmission();
    
    // Request 1 byte of data
    Wire.requestFrom(Addr, 1);
    
    // Read 1 byte of data
    if(Wire.available() == 1)
    {
        cTemp = Wire.read();
    }
    
    // Covert the data
    fTemp = cTemp * 1.8 + 32;
    
    // Output data to dashboard
    Particle.publish("Temperature in Celsius : ", String(cTemp));
    Particle.publish("Temperature in Fahrenheit : ", String(fTemp));
    delay(1000);
}

