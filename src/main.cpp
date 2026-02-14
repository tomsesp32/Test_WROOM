#include <Arduino.h>

#ifndef LED_BUILTIN
constexpr uint8_t LED_PIN = 13;
#else
constexpr uint8_t LED_PIN = LED_BUILTIN;
#endif

constexpr uint16_t UNIT_MS = 200;

void signalOnForUnits(uint8_t units) {
  digitalWrite(LED_PIN, HIGH);
  delay(UNIT_MS * units);
  digitalWrite(LED_PIN, LOW);
  delay(UNIT_MS);
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
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.begin(115200);
  delay(500);
  Serial.println();
  Serial.println("Starting SOS Morse blink");
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
