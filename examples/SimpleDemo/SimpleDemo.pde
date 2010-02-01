/*
  This file is part of Arduino-Color-LCD, an Arduino library for driving
  Nokia 132x132 color displays, including the "Knock-Off color LCD"
  from SparkFun.
  
  Version 0.2.0. Created by Cosmin Gorgovan <cosmin AT linux-geek.org>,
  February 1, 2010
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

#include <ColorLCD.h>

// Define some color codes
#define WHITE 0xFF
#define BLACK 0x00
#define RED     0b11100000
#define GREEN   0b00011100
#define BLUE    0b00000011
#define YELLOW	0xFC
#define MAGENTA	0xE3
#define CYAN	0x1F
#define GRAY    0b01101110

// Create a instance of the MyLCD class
ColorLCD lcd;

void setup()
{
  // Init serial comunication and the LCD display
  Serial.begin(9600);
  Serial.println("Starting");
  lcd.LCDInit();
  Serial.println("Done setting up the LCD");
}

void loop()
{
  // Write the title with red color on top of a blue background
  Serial.println("Printing the title");
  lcd.setBackground(BLUE);
  lcd.colorFill(0, 0, 132, 26, BLUE);
  lcd.moveCursor(5, 10);
  lcd.print("Nokia 6100 LCD Demo", RED);
  
  // Print the rest of the text
  Serial.println("Printing the contents");
  lcd.setBackground(BLACK);
  lcd.moveCursor(5, 32, 132-10);
  lcd.println("Powered by Arduino");
  lcd.println("Awesome coding\nby Cosmin Gorgovan", BLUE);
  lcd.println("GPL library: \nwww2.cs.man.ac.uk/~gorgovc9/arduino.html", GRAY);
  lcd.moveCursor(5, 100);
  lcd.println("Yellow color test", YELLOW);
  lcd.println("Cyan color test", CYAN);
  lcd.println("Magenta color test", MAGENTA);
  
  // After printing, enter an endless loop
  Serial.println("Done, entering endless loop");
  while(1);
}
