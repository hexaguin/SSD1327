#ifndef SSD1327_H
#define SSD1327_H

#include <Arduino.h>
#include "stdint.h"
#include "SPI.h"

// Scroll rate constants. See datasheet page 40.
#define SSD1327_SCROLL_2   0b111
#define SSD1327_SCROLL_3   0b100
#define SSD1327_SCROLL_4   0b101
#define SSD1327_SCROLL_5   0b110
#define SSD1327_SCROLL_6   0b000
#define SSD1327_SCROLL_32  0b001
#define SSD1327_SCROLL_64  0b010
#define SSD1327_SCROLL_256 0b011

class SSD1327 {
	public:
		SSD1327(int cs, int dc, int rst);
		void writeCmd(uint8_t reg);
		void writeData(uint8_t data);
		void setWriteZone(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
		uint16_t coordsToAddress(uint8_t x, uint8_t y);
		void setPixelChanged(uint8_t x, uint8_t y, bool changed);
		void drawPixel(uint8_t x, uint8_t y, uint8_t color, bool display);
		void drawRect(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t color, bool display = false);
		void drawHLine(int x, int y, int length, uint8_t color, bool display = false);
		void drawVLine(int x, int y, int length, uint8_t color, bool display = false);
		void drawLine(int x1, int y1, int x2, int y2, uint8_t color, bool display = false);
		void drawByteAsRow(uint8_t x, uint8_t y, uint8_t byte, uint8_t color);
		void drawChar(uint8_t x, uint8_t y, char thisChar, uint8_t color);
		void drawChar16(uint8_t x, uint8_t y, char thisChar, uint8_t color);
		void drawChar32(uint8_t x, uint8_t y, char thisChar, uint8_t color);
		void drawCharArray(uint8_t x, uint8_t y, char text[], uint8_t color, int size=8);
		void drawString(uint8_t x, uint8_t y, String textString, uint8_t color, int size=8);
		void setupScrolling(uint8_t startRow, uint8_t endRow, uint8_t startCol, uint8_t endCol, uint8_t scrollSpeed, bool right);
		void startScrolling();
		void stopScrolling();
		void scrollStep(uint8_t startRow, uint8_t endRow, uint8_t startCol, uint8_t endCol, bool right);
		void fillStripes(uint8_t offset);
		void clearBuffer();
		void writeFullBuffer();
		void writeUpdates();
		void setContrast(uint8_t contrast);
		void initRegs();
		void init();
	private:
		uint8_t frameBuffer[8192];   // Should mirror the display's own frameBuffer.
		uint8_t changedPixels[1024]; // Each bit of this array represets whether a given byte of frameBuffer (e.g. a pair of pixels) is not up to date.
		int _cs;
		int _dc;
		int _rst;
};

#endif
