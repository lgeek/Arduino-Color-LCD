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
#include "ColorLCD.h"

// LCD commands
#define DISON   0xAF    // Display on
#define DISOFF  0xAE    // Display off
#define DISNOR  0xA6    // Normal display
#define DISINV  0xA7    // Inverse display
#define COMSCN  0xBB    // Common scan direction
#define DISCTL  0xCA    // Display control
#define SLPIN   0x95    // Sleep in
#define SLPOUT  0x94    // Sleep out
#define PASET   0x75    // Page address set
#define CASET   0x15    // Column address set
#define DATCTL  0xBC    // Data scan direction, etc.
#define RGBSET8 0xCE    // 256-color position set
#define RAMWR   0x5C    // Writing to memory
#define RAMRD   0x5D    // Reading from memory
#define PTLIN   0xA8    // Partial display in
#define PTLOUT  0xA9    // Partial display out
#define RMWIN   0xE0    // Read and modify write
#define RMWOUT  0xEE    // End
#define ASCSET  0xAA    // Area scroll set
#define SCSTART 0xAB    // Scroll start set
#define OSCON   0xD1    // Internal oscillation on
#define OSCOFF  0xD2    // Internal oscillation off
#define PWRCTR  0x20    // Power control
#define VOLCTR  0x81    // Electronic volume control
#define VOLUP   0xD6    // Increment electronic control by 1
#define VOLDOWN 0xD7    // Decrement electronic control by 1
#define TMPGRD  0x82    // Temperature gradient set
#define EPCTIN  0xCD    // Control EEPROM
#define EPCOUT  0xCC    // Cancel EEPROM control
#define EPMWR   0xFC    // Write into EEPROM
#define EPMRD   0xFD    // Read from EEPROM
#define EPSRRD1 0x7C    // Read register 1
#define EPSRRD2 0x7D    // Read register 2
#define NOP     0x25    // NOP instruction

// Initiates the LCD
void ColorLCD::LCDInit()
{
  // Configure the pins as output
  pinMode(CS, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(SDA, OUTPUT);
  pinMode(RESET, OUTPUT);
  
  // The datasheet says it should be low, it works with high for me
  sbi(PORTD, RESET);
  
  // Select the LCD
  select();
  
  // Setup display timing
  sendCommand(DISCTL);
  sendData(0b00011); 		// 2 divisions, Field swithcing period (no idea)
  sendData(32);   		// 132 lines to be display
  sendData(12);   		// Inversely hightlighted lines - 1 (no idea)
  sendData(1);                  // Dispersion (again, no idea what's that)
  
  // Set common output scan direction
  sendCommand(COMSCN);
  sendData(0b00000001);
  
  // Turn on the oscillation circuit
  sendCommand(OSCON);
  
  // Wake up from sleep (?)
  sendCommand(SLPOUT);
  
  // Power all the circuits
  sendCommand(PWRCTR);
  sendData(0b00001111);
  delay(100);
  
  // This sets the RAM color order to RGB
  sendCommand(DISINV);
  
  // Setup how the data stored in RAM is displayed
  sendCommand(DATCTL);
  sendData(0b00000011); // scanning directions (address, column, page)
  sendData(0b00000000); // RGB mode for the LCD panel
  sendData(0b00000001); // Grayscale mode

  // Set color lookup table for 256 grayscale mode
  sendCommand(RGBSET8); 
  // Red
  sendData(0); // 000
  sendData(2); // 001
  sendData(4); // 010
  sendData(6); // 011
  sendData(8); // 100
  sendData(10); // 101
  sendData(12); // 110
  sendData(15); // 111
  // Green
  sendData(0); // 000
  sendData(2); // 001
  sendData(4); // 010
  sendData(6); // 011
  sendData(8); // 100
  sendData(10); // 101
  sendData(12); // 110
  sendData(15); // 111
  // Blue
  sendData(0); // 00
  sendData(5); // 01
  sendData(10); // 10
  sendData(15); // 11
  
  // Clear the memory
  reset();
  
  delay(100);
  
  // Turn on the display
  sendCommand(DISON);
}

// Selects an area of the screen
void ColorLCD::setBox(byte x1, byte y1, byte x2, byte y2)
{  
  // Select the columns
  sendCommand(CASET);
  sendData(x1);
  sendData(x2);
  
  // Select the rows
  sendCommand(PASET);
  sendData(y1);
  sendData(y2);
}

// Fill an area of the screen with color
void ColorLCD::colorFill(byte x1, byte y1, byte x2, byte y2, byte color)
{
  // Compute the dimensions
  byte width = x2 - x1 + 1;
  byte height = y2 - y1 + 1;
  uint16_t area = width * height;
  
  // Select a screen area
  setBox(x1, y1, x2, y2);
  
  // Fill it with color
  sendCommand(RAMWR);
  for (uint16_t i = 0; i < area; i++)
    sendData(color);
}

// Prints a char at position (x, y) with dimensions width and height and color code color
void ColorLCD::printChar(char c, byte x, byte y, byte width, byte height, byte color)
{
  uint16_t start = (c - 32) * width;
  
  for (int column = 0; column < width; column++)
  {
    setBox(x + column, y, x + column, y + height);
    sendCommand(RAMWR);
    
    for (int row = 0; row < height; row++)
    {
      if ((1<<row) & pgm_read_byte_near(font + start + column))
        sendData(color);
      else
        sendData(background);
    }
  }
}

// Displays a byte array with dimensions width and height at position (x, y)
void ColorLCD::displayBitmap(byte *bitmap, byte x, byte y, byte width, byte height) {
  setBox(x, y, x + width - 1, y + height - 1);
  sendCommand(RAMWR);
  for (uint16_t i = 0; i < height * width; i++)
  {
    sendData(*bitmap);
    bitmap++;
  }
}
