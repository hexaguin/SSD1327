# Low Level SSD1327 Library

Allows for drawing pixels and text to the Waveshare SSD1327 128x128 OLED module and similar displays using a full framebuffer. It was developed using the official datasheet, so *in theory*, any SSD1327 128x128 module should work with this library. Note that using a complete framebuffer uses a lot of memory (8 KiB for the buffer alone), and as such, this library is unusable on AVR-based boards like the Uno and Mega. Recommended platforms include ARM-based boards (e.g. Arduino Due) and the ESP family (ESP8266 and ESP32 boards such as NodeMCU).

8x8 font based on [dhepper's font8x8](https://github.com/dhepper/font8x8). All other font sizes are Ubuntu Mono.

## Example Code

```cpp
#define PIN_CS  5
#define PIN_DC  4
#define PIN_RST 16

#include "SSD1327.h"

SSD1327 disp(PIN_CS, PIN_DC, PIN_RST);

void setup() {
  disp.init();
}

void loop() {
  disp.clearBuffer();
  disp.drawString(16, 16, "Hello", 0xF, 32);
	disp.drawString(16, 48, "World!", 0xF, 32);
  disp.writeFullBuffer();
  delay(100);
}
```

## Methods
| Method | Description | Example |
|--------|-------------|---------|
| `SSD1327(int cs, int dc, int rst)` | Creates a new SSD1327 object on the provided CS, DC, and RST pins. | `SSD1327 myDisplay(5, 4, 16)` |
| `void init()` | Initializes the display. Call this once in your `setup()`. | `myDisplay.init()` |
| `void clearBuffer()` | Resets the entire framebuffer to black (0). | `myDisplay.clearBuffer()` |
| `void writeFullBuffer()` | Outputs the entire framebuffer to the display. Best used when most of the screen has changed since last frame, or for initializing the screen (e.g. blacking it out). | `myDisplay.writeFullBuffer()` |
| `void writeUpdates()` | Writes all pixels that have changed since last write to the display. Optimal for animations that do not affect the entire screen at once. | `myDisplay.writeUpdates()` |
| `void drawPixel(uint8_t x, uint8_t y, uint8_t color, bool display)` | Draws a pixel at `x` and `y`, with greyscale shade `color` (0-15). If `display` is true, the pixel is immediately output to the display. Otherwise, only the internal framebuffer is affected. | `myDisplay.drawPixel(32, 12, 0xF, false)` |
| `void drawLine(int x1, int y1, int x2, int y2, uint8_t color, bool display = false)` | Draws a line from `x1`,`y1` to `x2`,`y2` of shade `color`. If `display` is `true`, the line will be immediately drawn to the display. | `myDisplay.drawLine(12, 12, 42, 15, 0xF, false)` |
| `void drawCharArray(uint8_t x, uint8_t y, char text[], uint8_t color, int size=8)` | Draws an array of chars sequentially, of shade `color` and font size `size`, with the upper left corner at `x`,`y`. Valid font sizes are 8 (8x8), 16 (8x16), and 32 (16x32). Note that this library does NOT support text wrapping, you will need to implement this yourself if you have unpredictable string lengths. | `myDisplay.drawCharArray(24, 16, {'H','e','l','l','o'}, 0xF, 32)` |
| `void drawString(uint8_t x, uint8_t y, String textString, uint8_t color, int size=8)` | Wrapper for drawCharArray which accepts Arduino `String` objects. | `myDisplay.drawString(24, 16, "Hi!", 0xF, 32)` |
| `void fillStripes(uint8_t offset)` | Fills the framebuffer with vertical gradient stripes, offset horizontally by `offset`. I don't know why I left this in, it's just a silly test function. | `myDisplay.fillStripes(0)` |
| `void setContrast(uint8_t contrast)` | Sets the display contrast to a value from 0-255. Higher values result in higher contrast. | `myDisplay.setContrast(255)` |
| `void setupScrolling(uint8_t startRow, uint8_t endRow, uint8_t startCol, uint8_t endCol, uint8_t scrollSpeed, bool right)` | Prepares the display for scrolling within a given rectangular area. Speed is a macro fitting the format of `SSD1327_SCROLL_X`, where X is a speed in frames per pixel from the following list: 2, 3, 4, 5, 6, 32, 64, 256. | `disp.setupScrolling(0, 127, 0, 127, SSD1327_SCROLL_2, true);`
