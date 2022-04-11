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



#include "I2C.h"

I2C::I2C(byte SDA_, byte SCL_)
{
  f.scl = SCL_;
  f.sda = SDA_;
}

void I2C::allocateMemory(size_t buffer_size, bool *status)
{
    rxbuf = malloc(buffer_size); //Allocation
    if(rxbuf == NULL)
    {
      free(rxbuf);
      *status =0;
    }
    else
    {
      *status =1;
    }
}

void I2C::begin(void)
{
  pinMode(f.scl,OUTPUT);
  pinMode(f.sda,OUTPUT);
  digitalWrite(f.sda,1);
  digitalWrite(f.scl,1);
}

void I2C::sda(bool x)
{
  digitalWrite(f.sda,x);
}

void I2C::scl(bool x)
{
  digitalWrite(f.scl,x);
}

void I2C::starting(void)
{
  sda(0);
  scl(0);
}

void I2C::endTransmission(void)
{
  scl(1);
  sda(1);
}

void I2C::bitSend(bool b)
{
  sda(b);
  scl(1);
  scl(0);
}

void I2C::bitReceive(bool *b)
{
  *b = digitalRead(f.sda);
  scl(1);
  scl(0);
}

void I2C::ACK(bool *ack, bool mode, bool fin) 
{
  switch(mode)
  {
    case ACK_R: pinMode(f.sda,INPUT_PULLUP);
                *ack=digitalRead(f.sda);
                if(*ack==0) { *ack=1; }
                else { *ack=0; }
                scl(1); scl(0);
                pinMode(f.sda,OUTPUT);
                break;

    case ACK_W: bitSend(fin); *ack=1; break;
  } 
}

void I2C::byteRx(byte *buff)
{
  pinMode(f.sda,INPUT_PULLUP);
  for(byte i=0; i<8;i++)
  {
    bool x;
    bitReceive(&x);
    *buff |= x << (7-i);
  }
  pinMode(f.sda,OUTPUT);
}

void I2C::requestFrom(byte addr,  size_t len)
{
  bool x;
  starting();
  for(byte i=0; i<7;i++)
  {
    x=bitRead(addr,6-i);
    bitSend(x);
  }
  bitSend(1); //rw, read
  ACK(&x,ACK_R,0); //Reading ACK
  
  f.av=f.index=0;
  allocateMemory(len, &x); //allocating buffer.
  
  if(len==1)
  {
    byteRx(&rxbuf[0]);
    ACK(&x, ACK_W, 1); //Writing ACK, LAST BYTE
    endTransmission();
    f.av=1;
  }
  else if(len > 1)
  {
    byte k;
    for(k=0; k < (len-1); k++)
    {
      byteRx(&rxbuf[k]);
      ACK(&x, ACK_W, 0); //Writing ACK, Not LAST BYTE
      f.av++;
    }
    byteRx(&rxbuf[k]);
    ACK(&x, ACK_W, 1); //Writing ACK, The LAST BYTE
    endTransmission();
    f.av++;
  }
}

byte I2C::read(void)
{
  byte x;
  if(f.av > 0)
  {
    x= rxbuf[f.index];
    f.av--;
    f.index++;
  }
  if(f.av==0)
  {
    free(rxbuf);
    f.index=0;
  }
  return x;
}

bool I2C::beginTransmission(byte addr) //ok
{
  bool x;
  starting();
  for(byte i=0; i<7;i++)
  {
    x=bitRead(addr,6-i);
    bitSend(x);
  }
  bitSend(0); //rw, write
  ACK(&x,ACK_R,0); //Reading ACK
  return x;
}

void I2C::byteWrite(byte data, bool *stat)
{
  for(byte i=0; i<8;i++)
  {
    *stat = bitRead(data,7-i);
    bitSend(*stat);
  }
  ACK(stat,ACK_R,0); //Reading ACK
}

bool I2C::write(byte *data, size_t len) //ok
{
  byte count=0;
  bool x;
  for(byte i=0; i<len;i++)
  {
    byteWrite(data[i], &x);
    if(x)
    {
      count++;
    }
  }
  
  if(count==len)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

bool I2C::write(byte data)
{
  bool s;
  byteWrite(data, &s);
  return s;
}

byte I2C::available(void)
{
  return f.av;
}

void I2C::flush(void)
{
  free(rxbuf);
  f.av=0;
  f.index=0;
}
