#define PIN_CS  5
#define PIN_DC  4
#define PIN_RST 16

#include <Arduino.h>
#include "SSD1327.h"

unsigned long framecount = 0;

char timeText[] = {'1', '2', ':', '3', '5'};

SSD1327 disp(PIN_CS, PIN_DC, PIN_RST);

void setup() {
  disp.init();
}

void loop() {
  framecount++;

  disp.clearBuffer();
  
  for (int x = 0; x < 128; x++) {
    for (int y = (sin(((float)x+framecount)/16)*32)+64; y < 128; y++) {
       disp.drawPixel(x, y, 3, false);
     }
  }

  disp.drawCharArray(24, 0, timeText, 0xF, 32);
  disp.drawString(0, 112, "-12.5C", 0xF, 16);
  disp.drawString(84, 112, "52.1%", 0xF, 16);
  disp.writeFullBuffer();
  delay(8);
}
