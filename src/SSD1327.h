#ifndef SSD1327_H
#define SSD1327_H
#include "Arduino.h"
#include "stdint.h"
#include "SPI.h"
//#include "font8x8_basic.h"

class SSD1327 {
  public:
    SSD1327(int cs, int dc, int rst);
    void writeCmd(uint8_t reg);
    void writeData(uint8_t data);
    void setWriteZone(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
    int coordsToAddress(uint8_t x, uint8_t y);
    void drawPixel(uint8_t x, uint8_t y, uint8_t color, bool display);
    void drawByteAsRow(uint8_t x, uint8_t y, uint8_t byte, uint8_t color);
    void drawChar(uint8_t x, uint8_t y, char thisChar, uint8_t color);
    void drawChar16(uint8_t x, uint8_t y, char thisChar, uint8_t color);
    void drawChar32(uint8_t x, uint8_t y, char thisChar, uint8_t color);
    void drawCharArray(uint8_t x, uint8_t y, char text[], uint8_t color, int size=8);
    void drawString(uint8_t x, uint8_t y, String textString, uint8_t color, int size=8);
    void fillStripes(uint8_t offset);
    void clearBuffer();
    void writeFullBuffer();
    void initRegs();
    void init();
  private:
    uint8_t frameBuffer[8192]; //Should mirror the display's own frameBuffer.
    int _cs;
    int _dc;
    int _rst;
};

#endif
