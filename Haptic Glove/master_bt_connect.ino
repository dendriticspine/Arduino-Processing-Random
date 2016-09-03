// master
int statLED = 5;

void setup() {
	pinMode(statLED, OUTPUT);
	Serial.begin(115200);
	delay(400);
	Serial.print("$$$");
	delay(100);
	Serial.println("SM,1");  
	delay(100);
	Serial.println("C,0006664F89B7");
	delay(100);
	Serial.println("---");
}

void send_msg() {
	Serial.print("R");
	delay(1000); 
	Serial.print("R");
	delay(1000);
	Serial.print("R");
	delay(1000);
}

void loop() {
	send_msg();
}
