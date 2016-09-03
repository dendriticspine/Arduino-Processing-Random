// [Glove] MASTER (sending bluetooth) Script
// Read from sensor, modulate LEDs, send to bluetooth.

int touchSens1 = A0;		           // Read in for thumb sensor
//int touchSens2 = A1;		           // Read in for index finger sensor
//int touchSens3 = A2;		           // Read in for middle finger sensor
//int touchSens4 = A3;		           // Read in for ring? Pinky?

int lightPin1 = 9;                         // Output pin for light status 1
//int lightPin2 = 10;                      // Output pin for light status 2
//int lightPin3 = 11;                      // Output pin for light status 3
//int lightPin4 = 3;                       // Output pin for light status 4

int scaleInput1;                           // Scaled sensor1 value for PWM output
//int scaleInput2;                         // Scaled sensor2 value for PWM output
//int scaleInput3;                         // Scaled sensor3 value for PWM output
//int scaleInput4;                         // Scaled sensor4 value for PWM output

int scaleInputC1;

void setup() {
	pinMode(lightPin1, OUTPUT);        // Set the pins which control the motors to "OUTPUT" mode
	//pinMode(lightPin2, OUTPUT);
	//pinMode(lightPin3, OUTPUT);
	//pinMode(lightPin4, OUTPUT);
	
	Serial.begin(115200);              // Init serial connection (used w/bluetooth)
}

void loop() {
	scaleInput1 = ((analogRead(touchSens1) / 4));	// Scales 0-1024 of analogRead to PWM 0-255.
	//scaleInput2 = ((analogRead(touchSens2) / 4) - 1);	
	//scaleInput3 = ((analogRead(touchSens3) / 4) - 1);
	//scaleInput4 = ((analogRead(touchSens4) / 4) - 1);
	analogWrite(lightPin1, scaleInput1);                    // Reflect current pressures on LED status indicators
	//analogWrite(lightPin2, scaleInput2);
	//analogWrite(lightPin3, scaleInput3);
	//analogWrite(lightPin4, scaleInput4);
	scaleInputC1 = atoi(scaleInput1);
	Serial.println(scaleInput1);                              // Send the scaled input reading to the motor via bluetooth (serial)
	//Serial.println(scaleInputC1);
	delay(100);
}
