#include <Arduino.h>

#define blinkTime 2

const int enterGreenLED = 12 //setting output signal to Green LED for entry at pin 12
const int leaveWhiteLED = 33; //setting output signal to White LED for leave at pin 27
const int entrySensor = 27; //setting input signal from entry PIR Motion Sensor at pin 27
const int leaveSensor = 25; //setting input signal from leave PIR Motion Sensorat pin 25

int enterStatus = 0; //initializing status for entry
int leaveStatus = 0; //initializing status for departure
int count = 0; //initializing status for population of people

//auxiliary variables for timer to be used for interrupt handling
unsigned long currentTime = millis(); // millis() returns the number of milliseconds that have passed since the program upload to ESP-32 was completed
unsigned long lastEnterTriggerTime = 0; //to record the time at which the last Entry PIR Motion sensor trigger occurred
unsigned long lastLeaveTriggerTime = 0; //to record the time at which the last Leave PIR Motion sensor trigger occurred
boolean startentryTimer = false; //initializing startentryTimer as false in start
boolean startleaveTimer = false; //initializing startleaveTimer as false in start

// Checks if motion was detected by leave motion sensor, sets green LED HIGH and starts a timer
void IRAM_ATTR detectsentry() {
  digitalWrite(enterGreenLED, HIGH); //write high signal to enterGreenLED pin
  startentryTimer = true; //start the entry timer
  lastEnterTriggerTime = millis(); //set lastEnterTriggerTime as current time
  enterStatus = 1; //an entry has occurred
  count = count+1; //increment count
}

// Checks if motion was detected by enter motion sensor, sets green LED HIGH and starts a timer
void IRAM_ATTR detectsleave() {
  digitalWrite(leaveWhiteLED, HIGH); //write high signal to enterGreenLED pin
  startleaveTimer = true; //start the leave timer
  lastLeaveTriggerTime = millis(); //set lastLeaveTriggerTime as current time
  leaveStatus = 1; //a departure has occurred
  count = count-1; //decrement count
}


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
