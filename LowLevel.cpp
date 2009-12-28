/*
  This file is part of Arduino-Color-LCD, an Arduino library for driving
  Nokia 132x132 color displays, including the "Knock-Off color LCD"
  from SparkFun.
  
  Version 0.1. Created by Cosmin Gorgovan <cosmin AT linux-geek.org>,
  December 28, 2009
  Home page: http://www2.cs.man.ac.uk/~gorgovc9/arduino.html

  Arduino-Color-LCD is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Arduino-Color-LCD is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Arduino-Color-LCD.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "WProgram.h"
#include "ColorLCD.h"


// Outputs a bit with the logical value of (byte & mask)
#define bitout(byte, mask) \
  cbi(PORT, CLK); \
  if (mask & b)\
    sbi(PORT, SDA);\
  else\
    cbi(PORT, SDA);\
  sbi(PORT, CLK);\


// Software serial output (MSB first)
void ColorLCD::softwareSerialByteOut(byte b)
{
  // All this could be done in a for loop
  // But this way, it is about 40 % faster
  
  bitout(b, 128);
  bitout(b, 64);
  bitout(b, 32);
  bitout(b, 16);
  bitout(b, 8);
  bitout(b, 4);
  bitout(b, 2);
  bitout(b, 1);
}

// Select the LCD (CS line low)
void ColorLCD::select()
{
  cbi(PORT, CS);
}

// Unselect the LCD (CS line high)
void ColorLCD::unselect()
{
  sbi(PORT, CS);
}

// Sends a 1 bit followed by the 8 bits of data (data byte)
void ColorLCD::sendData(byte data)
{
  cbi(PORT, CLK);
  sbi(PORT, SDA);
  sbi(PORT, CLK);
  
  softwareSerialByteOut(data);
}

// Sends a 0 bit followed by the 8 bits of data (command byte)
void ColorLCD::sendCommand(byte command)
{
  cbi(PORT, CLK);
  cbi(PORT, SDA);
  sbi(PORT, CLK);

  softwareSerialByteOut(command);
}

