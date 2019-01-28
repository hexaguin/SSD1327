# Low Level SSD1327 Library

Allows for drawing pixels and text to the Waveshare SSD1327 OLED module and similar displays using a full framebuffer. Note that using a complete framebuffer uses a lot of memory (8 KiB for the buffer alone), and as such, this library is unusable on AVR-based boards like the Uno and Mega. Recommended platforms include ARM-based boards (e.g. Arduino Due) and the ESP family (ESP8266 and ESP32 boards such as NodeMCU).

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
