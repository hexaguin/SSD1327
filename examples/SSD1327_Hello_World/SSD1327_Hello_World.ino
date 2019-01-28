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
