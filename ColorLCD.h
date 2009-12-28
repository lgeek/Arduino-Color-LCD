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
