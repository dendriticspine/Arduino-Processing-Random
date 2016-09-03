// slave
int statLED = 5;
int incomingByte = 0;

void setup() {
	pinMode(statLED, OUTPUT);
	Serial.begin(115200);
	delay(400);
	Serial.print("$$$");
	delay(100);
	Serial.println("SM,0");
	delay(100);
	Serial.println("---");
}

void receive_msg() {  
	for (int i = 0; i < 10; i++) {
		if (Serial.available() > 0) {
			incomingByte = Serial.read();      // read the incoming byte
			if (incomingByte == 'R') {
				digitalWrite(statLED, HIGH);
				delay(100);
				digitalWrite(statLED, LOW);
				delay(100);
				digitalWrite(statLED, HIGH);
				delay(100);
				digitalWrite(statLED, LOW);
			}
		}
		delay(100);
	}
}

void loop() {
	receive_msg();
}
