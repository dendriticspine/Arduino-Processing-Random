// [Motor] SLAVE (receiving bluetooth) Script
// Receive from bluetooth, modulate motors.

int motorOut1 = 9;		// Motor 1 pin (haptic for thumb sensor)
int motorOut2 = 10;		// Motor 2 pin (haptic for index sensor)
int motorOut3 = 11;		// Motor 3 pin (haptic for middle sensor)
int motorOut4 = 3;		// Motor 4 pin (haptic for ring? pinky? palm?)

int incomingHaptic[5];		// Todo: allow for incoming data from 4 sensors vs 1
int startMotor = 12;		// Sets the EN pin on DRVs to high
int i = 0;

void setup() {
  TCCR1B = TCCR1B & 0b11111000 | 0x01;	// Sets Timer 1 (pwm pins 9,10) Frequency to 31250
  TCCR2B = TCCR2B & 0b11111000 | 0x01;	// Sets Timer 2 (pwm pins 3, 11) Frequency to 31250
  pinMode(motorOut1, OUTPUT);		// Set the pins which control the motors to "OUTPUT" mode
  pinMode(motorOut2, OUTPUT);
  pinMode(motorOut3, OUTPUT);
  pinMode(motorOut4, OUTPUT);
  pinMode(startMotor, OUTPUT);

  Serial.begin(115200);			// Init serial connection (used w/bluetooth)
  delay(400);				// Short delay to allow system negotiation time
  Serial.print("$$$");			// Enter bluetooth command mode
  delay(100);
  Serial.println("SM,0");			// Slave mode (SM,0); other bt devices can discover and connect; 
  delay(100);			        //       outbound connections can also be made.
  Serial.println("---");			// Exit bluetooth command mode

  digitalWrite(startMotor, HIGH);	// Enable motors (set EN pin on DRVs to high)
}

// the drv2603 requires >50% duty cycle for vibration
// so anything above analogWrite(128) should in theory produce vibration
// with test circuit 140 (2.75V) is about where the motor starts spinning.
// making the tactile range from 140-255

void loop() {
  //motorLev1 = motorLev1/2 + 128;		// Scale from 0-255 to 128-255 for motor output (>50% duty cycle)
  analogWrite(motorOut1, incomingHaptic[0]);	// Run der motor
  analogWrite(motorOut2, incomingHaptic[1]);
  analogWrite(motorOut3, incomingHaptic[2]);
  analogWrite(motorOut4, incomingHaptic[3]);
  delay(50);
}

void serialEvent() {
  while (Serial.available()) {
    incomingHaptic[i] = Serial.read();
    if (incomingHaptic[i] == 77) {
      i=0;
    } 
    else {
      i++;
    }
  }
  i=0;
}


