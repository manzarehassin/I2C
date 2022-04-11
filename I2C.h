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


#ifndef I2C_h
#define I2C_h

#if (ARDUINO >=100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif


class I2C
{
  public:

  //constructor
    I2C(byte SDA_, byte SCL_);

  //Methods
    void begin(void);
    void endTransmission(void);
    bool beginTransmission(byte addr);
    void requestFrom(byte addr,  size_t len);
    byte read(void);
    bool write(byte *data, size_t len);
    bool write(byte data);
    byte available(void);
    void flush(void);


  private:
  
  //Private Methods
      void allocateMemory(size_t buffer_size, bool *status);
      void byteWrite(byte data, bool *stat);
      void sda(bool x);
      void scl(bool x);
      void starting(void);
      void bitSend(bool b);
      void bitReceive(bool *b);
      void ACK(bool *ack, bool mode, bool fin);
      void byteRx(byte *buff);


  //Global Variables
    byte   *rxbuf;
    struct FLAG
    {
      byte scl    :4;
      byte sda    :4;
      byte av     :6;
      byte index  :6;
    }f;

    #define ACK_R 0
    #define ACK_W 1
};
#endif
