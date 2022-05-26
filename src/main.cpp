#include <Arduino.h>

#define blinkTime 2

const int enterGreenLED = 12 //setting output signal to Green LED for entry at pin 12
const int leaveWhiteLED = 33; //setting output signal to White LED for leave at pin 27
const int entrySensor = 27; //setting input signal from entry PIR Motion Sensor at pin 27
const int leaveSensor = 25; //setting input signal from leave PIR Motion Sensorat pin 25

//auxiliary variables for timer to be used for interrupt handling
unsigned long currentTime = millis(); // millis() returns the number of milliseconds that have passed since the program upload to ESP-32 was completed
unsigned long lastEnterTriggerTime = 0; //to record the time at which the last Entry PIR Motion sensor trigger occurred
unsigned long lastLeaveTriggerTime = 0; //to record the time at which the last Leave PIR Motion sensor trigger occurred
boolean startTimer = false;

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
