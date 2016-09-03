// slave device
int boardLight = 13;
int statusLight = 5;
int incomingByte = 0;
char bluetoothMsg[256];
char bluetoothCmd[256];

void bt_receive(void) {
	bool keepReading = true;
	int index = 0;
	bluetoothMsg[0] = '\0';
	while (keepReading) {
		keepReading = false;
		if (Serial.available() > 0) {
			incomingByte = Serial.read();		// read the incoming byte
			if (incomingByte != 13) {
				bluetoothMsg[index++] = incomingByte;
				keepReading = true;
			}
		}
	}
	bluetoothMsg[index] = '\0';
}

void bt_Send(char* i_bt_cmd, bool i_line = true) {
	if (i_line) {
		Serial.println(i_bt_cmd);
	} else {
		Serial.print(i_bt_cmd);
	}
	delay(100);
	bt_receive();
}

void bt_initialize(void) {
	bool bt_Connected = false;
	Serial.begin(115200); 

	bt_Send("$$$", false);
	bt_Send("SM,0");
	bt_Send("---"); 

	while (!bt_Connected) {
		delay(1000);
		bt_Send("$$$", false);
		bt_Send("GK");
		int numVal = 0;
		if (strlen(bluetoothMsg) > 0) {
			numVal= atoi(bluetoothMsg);
		}
		if (numVal == 1) {                  
			bt_Connected = true;
                        
		}
		bt_Send("---");              
	}

	digitalWrite(statusLight, HIGH);
	delay(200);
	digitalWrite(statusLight, LOW);
	delay(200);
	digitalWrite(statusLight, HIGH);
	delay(200);
	digitalWrite(statusLight, LOW);
	delay(200);

}

void setup() {
	pinMode(boardLight, OUTPUT);  
	pinMode(statusLight, OUTPUT);
	digitalWrite(statusLight, LOW);
	digitalWrite(boardLight, HIGH);
	delay(500);
	digitalWrite(boardLight, LOW);
	delay(500);
	digitalWrite(boardLight, HIGH);
	delay(500);
	digitalWrite(boardLight, LOW);
	delay(500);
	bt_initialize();
}

void receive_msg() {  
	for (int i = 0; i < 10; i++) {
		if (Serial.available() > 0) {
			incomingByte = Serial.read();      // read the incoming byte
			if (incomingByte == 'R') {
				digitalWrite(statusLight, LOW);
				delay(200);
				digitalWrite(statusLight, HIGH);
				delay(200);
				digitalWrite(statusLight, LOW);
			}
		}
		delay(100);
	}
}

void loop() {  
	receive_msg();
}
