// [Glove] MASTER (sending bluetooth) Script
// Read from sensor, modulate LEDs, send to bluetooth.

int touchSens1 = A0;		// input for thumb sensor
int touchSens2 = A1;		// input for index finger sensor
int touchSens3 = A2;		// input for middle finger sensor
int touchSens4 = A3;		// input for ring? Pinky?

int lightPin1 = 9;		// output for light status 1
int lightPin2 = 10;		// output for light status 2
int lightPin3 = 11;		// output for light status 3
int lightPin4 = 3;		// output for light status 4

int scaledInput[5];		// scaled sensor values for PWM output

void setup() {
  pinMode(lightPin1, OUTPUT);	// Set the LED pins to "OUTPUT" mode
  pinMode(lightPin2, OUTPUT);
  pinMode(lightPin3, OUTPUT);
  pinMode(lightPin4, OUTPUT);

  Serial.begin(115200);			// Init serial connection (used w/bluetooth)
  delay(400);				// Short delay to allow system negotiation time
  Serial.print("$$$");			// Enter bluetooth command mode
  delay(100);
  Serial.println("SM,1");		// Master mode (SM,1); useful when device wants to initiate connections
  delay(100);				//        but not receive them. Device will NOT be discoverable or connectable.
  Serial.println("C,0006664F89B7");	// C,<address>; connect to the address specified in hex format
  delay(100);
  Serial.println("---");		// Exit bluetooth command mode
}

void loop() {
  scaledInput[0] = ((analogRead(touchSens1) / 8));	// Scales 0-1024 of analogRead to PWM 0-255.
  scaledInput[1] = ((analogRead(touchSens2) / 8));	
  scaledInput[2] = ((analogRead(touchSens3) / 8));
  scaledInput[3] = ((analogRead(touchSens4) / 8));
  analogWrite(lightPin1, scaledInput[0]);		// Reflect current pressures on LED status indicators
  analogWrite(lightPin2, scaledInput[1]);
  analogWrite(lightPin3, scaledInput[2]);
  analogWrite(lightPin4, scaledInput[3]);
  scaledInput[4] = 77;
  Serial.write((uint8_t *)scaledInput, (size_t)5);
  delay(40);
}


