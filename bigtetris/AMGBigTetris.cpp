#include "AMGBigTetris.h"
#include <Adafruit_NeoPixel.h>
#include "Arduino.h"

#define BOARDWIDTH 10
#define BOARDHEIGHT 20

#define PIN 3
#define UP 9
#define Left 10
#define Right 11
#define DOWN 12

Adafruit_NeoPixel strip;

void setupStrip() {
  strip = Adafruit_NeoPixel(200, PIN, NEO_GRB + NEO_KHZ800);
  strip.begin();
  strip.show();
}

void setupController() {
  pinMode(UP, INPUT);
  pinMode(DOWN, INPUT);
  pinMode(Left, INPUT);
  pinMode(Right, INPUT);
}

void setCartesianPixelColor(int x, int y, int r, int g, int b) {
  // The IF statement takes all even rows and reverses them. This accounts for all odd rows linking from left to right and all even rows connecting from right to left.
  if (y % 2 == 0) {
    strip.setPixelColor((y*BOARDWIDTH)+x, r, g, b);
  }
  else {
    strip.setPixelColor((y*BOARDWIDTH)+(BOARDWIDTH-x-1), r, g, b);
  }
}

void setLinearPixelColor(int i, int r, int g, int b) {
  strip.setPixelColor(i, r, g, b);
}

void updateDisplay() {
  strip.show();
}

int readRight() {
  return digitalRead(Right);
}

int readLeft() {
  return digitalRead(Left);
}

int readUp() {
  return digitalRead(UP);
}

int readDown() {
  return digitalRead(DOWN);
}

void clearBoard() {
  for(int i = 0; i < strip.numPixels(); i++){
    setLinearPixelColor(i, 0, 0, 0);
  }
}

