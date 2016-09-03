// Rat Mind Flex v3
// Firing Rate = 0-X
// TDT output = 0-4 V, TDT scaling factor = 4V / X
// Arduino analog in = 0-1023

#include <Servo.h>            // Use Servo library, included with IDE
Servo myServo;                // Create Servo object to control the servo 

int servoControlOut = 9;      // Digital pin connected to servo
int analogRateIn = 2;         // Analog pin connected to TDT
int currentRate = 0;          // Initialize variable for mapped firing rate
int thresholdRate = 500;      // Initialize variable for FR threshold

void setup() { 
  myServo.attach(servoControlOut);    // Initialize servo motor
  Serial.begin(9600);                 // For debugging FR -> Analog Out -> Arduino
} 

void loop() { 
  currentRate = analogRead(analogRateIn);    // Get current rate
  Serial.println(currentRate);               // Print to console for debugging
  if (currentRate > thresholdRate) {                   // 
    myServo.writeMicroseconds(1400);  // Clockwise
    delay(500);
  } else {
    myServo.writeMicroseconds(1500);  // Stop
    delay(100); 
  }
}
