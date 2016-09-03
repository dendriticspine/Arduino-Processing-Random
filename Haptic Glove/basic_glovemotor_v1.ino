// Basic Glove/Motor Script (No Bluetooth)
// Read from sensor, modulate motors.

int touchSense1 = A0;		// Thumb sensor
//int touchSense2 = A1;		// Index finger sensor
//int touchSense3 = A2;		// Middle finger sensor
//int touchSense4 = A3;		// Ring? Pinky?

int motorOut1 = 9;
int startMotor1 = 12;
//int motorOut2 = 10;
//int motorOut3 = 11;
//int motorOut4 = 3;

int runMotor1;

void setup() {
	TCCR1B = TCCR1B & 0b11111000 | 0x01;		// Sets Timer 1 (pwm pins 9,10) Frequency to 31250
//	TCCR2B = TCCR2B & 0b11111000 | 0x01;		// Sets Timer 2 (pwm pins 3, 11) Frequency to 31250
	pinMode(motorOut1, OUTPUT);
        pinMode(startMotor1, OUTPUT);
//	pinMode(motorOut2, OUTPUT);
//	pinMode(motorOut3, OUTPUT);
//	pinMode(motorOut4, OUTPUT);
}

// the drv2603 requires >50% duty cycle for vibration
// so anything above analogWrite(128) should in theory produce vibration
// with test circuit 140 (2.75V) is about where the motor starts spinning.
// making the tactile range from 140-255

void loop() {
        digitalWrite(startMotor1, HIGH);
        runMotor1 = ((analogRead(touchSense1) / 8) + 128);	// Scales the 0-1024 of analogRead
//	runMotor2 = ((analogRead(touchSense2) / 8) + 128);	// into PWM values of 128-255.
//	runMotor3 = ((analogRead(touchSense3) / 8) + 128);
//	runMotor4 = ((analogRead(touchSense4) / 8) + 128);
	analogWrite(motorOut1, runMotor1);
//	analogWrite(motorOut2, runMotor2);
//	analogWrite(motorOut3, runMotor3);
//	analogWrite(motorOut4, runMotor4);
}
