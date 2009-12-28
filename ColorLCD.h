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

#ifndef ColorLCD_h
#define ColorLCD_h

// Configure the port and pins here
// Pin X on PORTD = I/O pin number X on the Arduino board

// The port
#define PORT PORTD

// Pins
#define CS 2
#define CLK 3
#define SDA 4
#define RESET 5

// Fast digital I/O
// Arduino's digitalWrite is too slow 
#define cbi(reg, bit) (reg&=~(1<<bit))
#define sbi(reg, bit) (reg|= (1<<bit))

#include "WProgram.h"

class ColorLCD
{
  byte screenWidth;
  
  byte fontWidth;
  byte fontHeight;
  byte fontSpacing;
  
  uint16_t textLength;
  byte textBoxLeftMargin;
  byte textBoxTopMargin;
  byte textBoxWidth;
  
  byte foreground;
  byte background;

  public:
    ColorLCD();
    void LCDInit();

    void setBackground(byte color);
    void setForeground(byte color);
    
    void colorFill(byte x1, byte y1, byte x2, byte y2, byte color);
    void colorFill(byte x1, byte y1, byte x2, byte y2);

    void printChar(char c, byte x, byte y, byte width, byte height, byte color);
    void displayBitmap(byte *bitmap, byte x, byte y, byte width, byte height);

    void clear();
    void reset();

    void print(char c, byte color);
    void print(char c);
    void print(char *string, byte color);
    void print(char *string);
    void print(int i, byte color);
    void print(int i);
    void println();
    void println(char c, byte color);
    void println(char c);
    void println(char *string, byte color);
    void println(char *string);
    void println(int i, byte color);
    void println(int i);

    void moveCursor(byte x, byte y, byte width);
    void moveCursor(byte x, byte y);    

  private:
    void select();
    void unselect();
    
    void softwareSerialByteOut(byte b);
    void sendData(byte data);
    void sendCommand(byte command);
    
    void setBox(byte x1, byte y1, byte x2, byte y2);
    
    const static byte font[475];
};

#endif
