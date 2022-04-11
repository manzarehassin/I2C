/*

MIT License

Copyright (c) 2022 Manzar-E-Hassin

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

/*
    EEPROM (DUMMY) Driver (Master)
    Valid address range: 0-9
    Target Slave ID: 10

    Use any two digital pins as I2C clock (SCL), data (SDA) line. 
    In this example, we will use following pins...

    SDA = Digital 6
    SCL = Digital 5

    Make sure the ground connection between two boards (master-slave) is common.

    User can use another additional secondary i2c bus in any avr based microcontrollers.

*/

#include <I2C.h>

I2C w(6,5);  //SDA, SCL

void setup() 
{
  Serial.begin(115200);
  w.begin();
}

void loop()
{
  Task();
  delay(1000);
}

//DEMO FUNCTIONS ===============================

void ReadMem(byte addr) //For Reading data
{
  w.beginTransmission(10);
  w.write(addr);
  w.endTransmission();
  
  w.requestFrom(10,1);
  byte x= w.read();
  
  Serial.print(F("Read: \t"));
  Serial.println(x);
}

void WriteMem(byte addr, byte val) //For Writing data
{
  w.beginTransmission(10);
  w.write(addr);
  w.write(val);
  w.endTransmission();
  
  Serial.print(F("Write: \t"));
  Serial.println(val);
}

void Task()
{
  static byte count;
  WriteMem(2, count); // Writing data to address 2
  ReadMem(2);         // Reading data from address 2
  Serial.println(F("-------------------------"));
  count++;
}
