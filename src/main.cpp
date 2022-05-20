#include <Arduino.h>

#define blinkTime 3

const int enterGreenLED = 26; //setting output signal to Green LED for entry at pin 26
const int leaveRedLED = 33; //setting output signal to Green LED for entry at pin 33
const int entrySensor = 27; //setting input signal from entry PIR Motion Sensor at pin 27
const int ledPin = 25; //setting input signal from entry PIR Motion Sensorat pin 25



void setup() {
  // setup pin 5 as a digital output pin
  pinMode (ledPin, OUTPUT);
}
void loop() {
  digitalWrite (ledPin, HIGH);	// turn on the LED
  delay(500);	// wait for half a second or 500 milliseconds
  digitalWrite (ledPin, LOW);	// turn off the LED
  delay(500);	// wait for half a second or 500 milliseconds
}
