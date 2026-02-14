#include <Arduino.h>
extern "C" void neopixelWrite(uint8_t pin, uint8_t red_val, uint8_t green_val,
                              uint8_t blue_val);

constexpr uint8_t WS2812_PIN = 2;

constexpr uint16_t UNIT_MS = 200;
uint8_t colorIndex = 0;

void setColorByIndex(uint8_t index) {
  switch (index % 3) {
    case 0:
      neopixelWrite(WS2812_PIN, 255, 0, 0);  // Red
      break;
    case 1:
      neopixelWrite(WS2812_PIN, 0, 255, 0);  // Green
      break;
    default:
      neopixelWrite(WS2812_PIN, 0, 0, 255);  // Blue
      break;
  }
}

void ledOff() {
  neopixelWrite(WS2812_PIN, 0, 0, 0);
}

void signalOnForUnits(uint8_t units) {
  setColorByIndex(colorIndex);
  delay(UNIT_MS * units);
  ledOff();
  delay(UNIT_MS);
  colorIndex = (colorIndex + 1) % 3;
}

void dot() { signalOnForUnits(1); }
void dash() { signalOnForUnits(3); }

void letterGap() {
  delay(UNIT_MS * 2);
}

void wordGap() {
  delay(UNIT_MS * 4);
}

void blinkS() {
  dot();
  dot();
  dot();
}

void blinkO() {
  dash();
  dash();
  dash();
}

void setup() {
  ledOff();

  Serial.begin(115200);
  delay(500);
  Serial.println();
  Serial.println("Starting SOS Morse blink (WS2812 on GPIO 2)");
}

void loop() {
  Serial.println("... + S");
  blinkS();
  letterGap();

  Serial.println("--- + O");
  blinkO();
  letterGap();

  Serial.println("... + S");
  blinkS();
  wordGap();
}
