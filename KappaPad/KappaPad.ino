

#include <CapacitiveSensor.h>
#include <Keyboard.h>

#include "CapacitiveKey.h"

//#define SERIAL_OUTPUT
#define DISABLE_PIN 15

void setup() {
  #ifdef SERIAL_OUTPUT
  Serial.begin(115200);
  #endif
  Keyboard.begin();
  pinMode(DISABLE_PIN, INPUT_PULLUP);
}

CapacitiveKey key0 = CapacitiveKey(
  2,    //Capacitive Send Pin
  7,    //Capacitive Sense Pin
  6,    //LED Pin
  6,    //Capacitive Threshold
  'z',  //Keyboard Key
  255   //LED Brightness (0-255)
);
CapacitiveKey key1 = CapacitiveKey(
  4,    //Capacitive Send Pin
  8,    //Capacitive Sense Pin
  10,   //LED Pin
  5,    //Capacitive Threshold
  'x',  //Keyboard Key
  255   //LED Brightness (0-255)
);

void loop() {
  bool keyboardActive = digitalRead(DISABLE_PIN);
  key0.keyUpdate(keyboardActive);
  key1.keyUpdate(keyboardActive);

  #ifdef SERIAL_OUTPUT
  Serial.print(key0.sample);
  Serial.print(",");
  Serial.println(key1.sample);
  #endif
}


