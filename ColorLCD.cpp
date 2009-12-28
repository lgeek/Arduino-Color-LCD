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


// Constructor function
ColorLCD::ColorLCD()
{  
  // Screen width (used to compute text box size)
  screenWidth = 132;
  
  // The font dimensions
  fontWidth = 5;
  fontHeight = 8;
  fontSpacing = 1;
 
   // Text length in a box, gets reseted to 0 when moving the text pointer
  textLength = 0;
  // The margins of the text box
  textBoxLeftMargin = 5;
  textBoxTopMargin = 5;
  // The width of the text box in pixels
  textBoxWidth = screenWidth - 2 * textBoxLeftMargin;
  
  // Foreground and background color codes
  foreground = 0xFF;
  background = 0x00;
}

// Change the background color (used by text printing)
void ColorLCD::setBackground(byte color)
{
  background = color;
}

// Change the foreground color (default color when displaying stuff)
void ColorLCD::setForeground(byte color)
{
  foreground = color;
}

// Fill an area of the screen with the foreground color
void ColorLCD::colorFill(byte x1, byte y1, byte x2, byte y2)
{
  colorFill(x1, y1, x2, y2, foreground);
}

// Fills the whole screen with the background color
void ColorLCD::clear()
{
  colorFill(0, 0, 131, 131, background);
  textLength = 0;
  moveCursor(5, 5, 120);
}

// Fills the whole screen with black
void ColorLCD::reset()
{
  colorFill(0, 0, 131, 131, 0x00);
  textLength = 0;
  moveCursor(5, 5, 120);
}


