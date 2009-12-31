/*
  This file is part of Arduino-Color-LCD, an Arduino library for driving
  Nokia 132x132 color displays, including the "Knock-Off color LCD"
  from SparkFun.
  
  Version 0.1.1. Created by Cosmin Gorgovan <cosmin AT linux-geek.org>,
  December 31, 2009
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
#include <avr/pgmspace.h>

#include "ColorLCD.h"

// Font bitmaps
// Created by Thomas Jespersen, July 2009
prog_uchar ColorLCD::font[] PROGMEM = {
0x00 , 0x00 , 0x00 , 0x00 , 0x00 ,
0x00 , 0x06 , 0x5F , 0x06 , 0x00 ,                      // !
0x07 , 0x03 , 0x00 , 0x07 , 0x03 ,                      // ,
0x24 , 0x7E , 0x24 , 0x7E , 0x24 ,                      // #
0x24 , 0x2B , 0x6A , 0x12 , 0x00 ,                      // $
0x63 , 0x13 , 0x08 , 0x64 , 0x63 ,                      // %
0x36 , 0x49 , 0x56 , 0x20 , 0x50 ,                      // &
0x00 , 0x07 , 0x03 , 0x00 , 0x00 ,                      // //
0x00 , 0x3E , 0x41 , 0x00 , 0x00 ,                      // (
0x00 , 0x41 , 0x3E , 0x00 , 0x00 ,                      // )
0x08 , 0x3E , 0x1C , 0x3E , 0x08 ,                      // *
0x08 , 0x08 , 0x3E , 0x08 , 0x08 ,                      // +
0x00 , 0xE0 , 0x60 , 0x00 , 0x00 ,                      // ,
0x08 , 0x08 , 0x08 , 0x08 , 0x08 ,                      // -
0x00 , 0x60 , 0x60 , 0x00 , 0x00 ,                      // .
0x20 , 0x10 , 0x08 , 0x04 , 0x02 ,                      // /
0x3E , 0x51 , 0x49 , 0x45 , 0x3E ,                      // 0
0x00 , 0x42 , 0x7F , 0x40 , 0x00 ,                      // 1
0x62 , 0x51 , 0x49 , 0x49 , 0x46 ,                      // 2
0x22 , 0x49 , 0x49 , 0x49 , 0x36 ,                      // 3
0x18 , 0x14 , 0x12 , 0x7F , 0x10 ,                      // 4
0x2F , 0x49 , 0x49 , 0x49 , 0x31 ,                      // 5
0x3C , 0x4A , 0x49 , 0x49 , 0x30 ,                      // 6
0x01 , 0x71 , 0x09 , 0x05 , 0x03 ,                      // 7
0x36 , 0x49 , 0x49 , 0x49 , 0x36 ,                      // 8
0x06 , 0x49 , 0x49 , 0x29 , 0x1E ,                      // 9
0x00 , 0x6C , 0x6C , 0x00 , 0x00 ,                      // :
0x00 , 0xEC , 0x6C , 0x00 , 0x00 ,                      // ;
0x08 , 0x14 , 0x22 , 0x41 , 0x00 ,                      // <
0x24 , 0x24 , 0x24 , 0x24 , 0x24 ,                      // =
0x00 , 0x41 , 0x22 , 0x14 , 0x08 ,                      // >
0x02 , 0x01 , 0x59 , 0x09 , 0x06 ,                      // ?
0x3E , 0x41 , 0x5D , 0x55 , 0x1E ,                      // @
0x7E , 0x09 , 0x09 , 0x09 , 0x7E ,                      // A
0x7F , 0x49 , 0x49 , 0x49 , 0x36 ,                      // B
0x3E , 0x41 , 0x41 , 0x41 , 0x22 ,                      // C
0x7F , 0x41 , 0x41 , 0x41 , 0x3E ,                      // D
0x7F , 0x49 , 0x49 , 0x49 , 0x41 ,                      // E
0x7F , 0x09 , 0x09 , 0x09 , 0x01 ,                      // F
0x3E , 0x41 , 0x49 , 0x49 , 0x7A ,                      // G
0x7F , 0x08 , 0x08 , 0x08 , 0x7F ,                      // H
0x00 , 0x41 , 0x7F , 0x41 , 0x00 ,                      // I
0x30 , 0x40 , 0x40 , 0x40 , 0x3F ,                      // J
0x7F , 0x08 , 0x14 , 0x22 , 0x41 ,                      // K
0x7F , 0x40 , 0x40 , 0x40 , 0x40 ,                      // L
0x7F , 0x02 , 0x04 , 0x02 , 0x7F ,                      // M
0x7F , 0x02 , 0x04 , 0x08 , 0x7F ,                      // N
0x3E , 0x41 , 0x41 , 0x41 , 0x3E ,                      // O
0x7F , 0x09 , 0x09 , 0x09 , 0x06 ,                      // P
0x3E , 0x41 , 0x51 , 0x21 , 0x5E ,                      // Q
0x7F , 0x09 , 0x09 , 0x19 , 0x66 ,                      // R
0x26 , 0x49 , 0x49 , 0x49 , 0x32 ,                      // S
0x01 , 0x01 , 0x7F , 0x01 , 0x01 ,                      // T
0x3F , 0x40 , 0x40 , 0x40 , 0x3F ,                      // U
0x1F , 0x20 , 0x40 , 0x20 , 0x1F ,                      // V
0x3F , 0x40 , 0x3C , 0x40 , 0x3F ,                      // W
0x63 , 0x14 , 0x08 , 0x14 , 0x63 ,                      // X
0x07 , 0x08 , 0x70 , 0x08 , 0x07 ,                      // Y
0x71 , 0x49 , 0x45 , 0x43 , 0x00 ,                      // Z
0x00 , 0x7F , 0x41 , 0x41 , 0x00 ,                      // [
0x02 , 0x04 , 0x08 , 0x10 , 0x20 ,                      // Back slash
0x00 , 0x41 , 0x41 , 0x7F , 0x00 ,                      // ]
0x04 , 0x02 , 0x01 , 0x02 , 0x04 ,                      // ^
0x80 , 0x80 , 0x80 , 0x80 , 0x80 ,                      // _
0x00 , 0x03 , 0x07 , 0x00 , 0x00 ,                      // `
0x20 , 0x54 , 0x54 , 0x54 , 0x78 ,                      // a
0x7F , 0x44 , 0x44 , 0x44 , 0x38 ,                      // b
0x38 , 0x44 , 0x44 , 0x44 , 0x28 ,                      // c
0x38 , 0x44 , 0x44 , 0x44 , 0x7F ,                      // d
0x38 , 0x54 , 0x54 , 0x54 , 0x18 ,                      // e
0x08 , 0x7E , 0x09 , 0x09 , 0x00 ,                      // f
0x18 , 0xA4 , 0xA4 , 0xA4 , 0x7C ,                      // g
0x7F , 0x04 , 0x04 , 0x78 , 0x00 ,                      // h
0x00 , 0x00 , 0x7D , 0x00 , 0x00 ,                      // i
0x40 , 0x80 , 0x84 , 0x7D , 0x00 ,                      // j
0x7F , 0x10 , 0x28 , 0x44 , 0x00 ,                      // k
0x00 , 0x00 , 0x7F , 0x40 , 0x00 ,                      // l
0x7C , 0x04 , 0x18 , 0x04 , 0x78 ,                      // m
0x7C , 0x04 , 0x04 , 0x78 , 0x00 ,                      // n
0x38 , 0x44 , 0x44 , 0x44 , 0x38 ,                      // o
0xFC , 0x44 , 0x44 , 0x44 , 0x38 ,                      // p
0x38 , 0x44 , 0x44 , 0x44 , 0xFC ,                      // q
0x44 , 0x78 , 0x44 , 0x04 , 0x08 ,                      // r
0x08 , 0x54 , 0x54 , 0x54 , 0x20 ,                      // s
0x04 , 0x3E , 0x44 , 0x24 , 0x00 ,                      // t
0x3C , 0x40 , 0x20 , 0x7C , 0x00 ,                      // u
0x1C , 0x20 , 0x40 , 0x20 , 0x1C ,                      // v
0x3C , 0x60 , 0x30 , 0x60 , 0x3C ,                      // w
0x6C , 0x10 , 0x10 , 0x6C , 0x00 ,                      // x
0x9C , 0xA0 , 0x60 , 0x3C , 0x00 ,                      // y
0x64 , 0x54 , 0x54 , 0x4C , 0x00 ,                      // z
0x08 , 0x3E , 0x41 , 0x41 , 0x00 ,                      // {
0x00 , 0x00 , 0x7F , 0x00 , 0x00 ,                      // |
0x00 , 0x41 , 0x41 , 0x3E , 0x08 ,                      // }
0x02 , 0x01 , 0x02 , 0x01 , 0x00                        // ~
};

// Function used to print a char with a different color from the foreground color
void ColorLCD::print(char c, byte color)
{
  switch (c)
  {
    // Newline
    // It marks the current line as filled, without actually displaying something
    case '\n':
      textLength += textBoxWidth - (textLength % textBoxWidth);
      break;
    // Carriage return
    // Moves the text pointer at the beggining of the line
    // Note: it doesn't work as backspace, it doesn't delete text
    case '\r':
      textLength -= textLength % textBoxWidth;
      break;
    // Regular char
    default:
      byte x = (textLength % textBoxWidth) + textBoxLeftMargin;
      byte y = (textLength / textBoxWidth) * (fontHeight + 1) + textBoxTopMargin;
    
      printChar(c, x, y, fontWidth, fontHeight, color);
      textLength += fontWidth + fontSpacing;
  }
}

// Function used to print a char with the foreground color
void ColorLCD::print(char c)
{
  print(c, foreground);
}

// Function used to print a string with a different color from the foreground color
void ColorLCD::print(char *string, byte color)
{
  while (*string)
  {
    print(*string, color);
    string++;
  }
}

// Function used to print a string with the foreground color
void ColorLCD::print(char *string)
{
  print(string, foreground);
}

// Function used to print an integer with a different color from the foreground color
void ColorLCD::print(int i, byte color)
{
  char buffer[33];
  print(itoa(i, buffer, 10));
}

// Function used to print an integer with the foreground color
void ColorLCD::print(int i)
{
  print(i, foreground);
}

// Function used to print a newline
void ColorLCD::println()
{
  print('\n');
}

// Function used to print a char with a different color from the foreground color
// Followed by a newline
void ColorLCD::println(char c, byte color)
{
  print(c, color);
  print('\n');
}

// Followed by a newline
void ColorLCD::println(char c)
{
  println(c, foreground);
}

// Followed by a newline
void ColorLCD::println(char *string, byte color)
{
  print(string, color);
  print('\n');
}

// Followed by a newline
void ColorLCD::println(char *string)
{
  println(string, foreground);
}

// Followed by a newline
void ColorLCD::println(int i, byte color)
{
  print(i, color);
  print('\n');
}

// Followed by a newline
void ColorLCD::println(int i)
{
  println(i, foreground);
}

// Function used to move the text pointer to a new position
// Text box width (in pixels) parameter
// It resets the text length to 0
void ColorLCD::moveCursor(byte x, byte y, byte width)
{
  textBoxLeftMargin = x;
  textBoxTopMargin = y;
  textLength = 0;
  textBoxWidth = width;
}

// Function used to move the text pointer to a new position
// without specifing the width, which will be computed
// so that the right margin of the text box is a the right margin of the screen
void ColorLCD::moveCursor(byte x, byte y)
{
  byte width = (screenWidth - x);
  moveCursor(x, y, width);
}
