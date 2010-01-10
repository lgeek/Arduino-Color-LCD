/*
  This file is part of Arduino-Color-LCD, an Arduino library for driving
  Nokia 132x132 color displays, including the "Knock-Off color LCD"
  from SparkFun.
  
  Version 0.1.1. Created by Cosmin Gorgovan <cosmin AT linux-geek.org>,
  January 10, 2010
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

ColorLCD lcd;

// The ADC returns 10 bit integers as results, with 0 being 0 V and 1023 being 5V
double divisor = 1023 / 5;
double voltage;

void setup()
{
  // Start the LCD
  lcd.LCDInit();
  
  // Print 6 rows of Voltage_X:____V that are later going to be updated with the values
  for (uint8_t i = 0; i < 6; i++)
  {
    lcd.print("Voltage ");
    lcd.print(i);
    lcd.println(":     V");
  }
}

void loop()
{
  // Move the cursor at 5 pixels right of the ':' on each row and a top margin of 5 pixels
  lcd.moveCursor(5*14, 5);
  
  // Read the ADC value, compute the voltage and print it
  /* Note that on Arduino, the double FP numbers have the same precission as a regular
     float, hence the result may be slightly off (e.g. 5.01 V instead of 5.00 V). */
  /* Floating point operations are costly because ATmega MCUs don't have
     instructions for them, so they have to be emulated in software */
  for (uint8_t i = 0; i < 6; i++)
  {
    voltage = analogRead(i) / divisor;
    printFPNumber(voltage);
    lcd.println();
  }
  
  // With no delay the screen isn't readble for values that aren't stable
  delay(300);
}

// Prints a FP number
void printFPNumber(double d)
{
  // Print the decimal part
  lcd.print((int) d);
  lcd.print('.');
  
  // Compute and print the fractional part
  uint8_t fractionalPart = (d - (int) d) * 100;
  if (fractionalPart < 10)
    lcd.print('0');
  lcd.print(fractionalPart);
}
