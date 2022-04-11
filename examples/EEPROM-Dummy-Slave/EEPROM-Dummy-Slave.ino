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
    EEPROM (DUMMY) (Slave)
    Valid address range: 0-9
    Device (Slave, this device) ID: 10

    Connect with standard i2c pins. In this example we will use standard wire library.
    
    I2C PINS (slave):
    =====================
    SDA = Analog 4 (A4)
    SCL = Analog 5 (A5)

    Make sure the ground connection is common between two boards.

*/

#include <Wire.h>

byte address;
byte data[10]={255,255,255,255,255,255,255,255,255,255}; //Storage area
bool ready;

void setup()
{
  pinMode(13,OUTPUT);
  Wire.begin(10);               //Slave address: 10
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  //Serial.begin(115200);
}

void receiveEvent(int howMany) 
{
  byte rx = Wire.available();
   if(rx==1)
   {         
            address = Wire.read(); 
            if(address<10)
            {
              ready=1;
            }
            else
            {
              //Serial.println("Invalid address1.");
            }
   }

   else if(rx==2)
   {
            byte a = Wire.read(); 
            byte d = Wire.read(); 
            if(a<10)
            {
              digitalWrite(13,0);
              save(&a, &d);
            }
            else
            {
              //Serial.println("Invalid address2.");
            }
  }
}

void requestEvent() 
{ 
 if(ready)
 {
  digitalWrite(13,1);
  Get();
  ready=0;
 }
 else
 {
  //Serial.println("Invalid Request");
 }
}

void save(byte *a, byte *d)
{
  data[*a] = *d;
}

void Get()
{
  Wire.write(data[address]);
}

void loop() 
{
  //Nothing here.
}
