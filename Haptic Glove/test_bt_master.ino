// master device
int boardLight = 13;
int statusLight = 5;
int msgToken = 0;
int incomingByte = 0;
char bluetoothMsg[256];
char bluetoothCmd[256];

int bt_devices_count = 2;
char* known_bt_macs[2];									// this is set to hold only two MAC addresses

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
	known_bt_macs[0] = "0006664F9414";			// Green:  0006664F9414
	known_bt_macs[1] = "0006664F89B7";			// Blue:   0006664F89B7
	Serial.begin(115200); 

	bt_Send("$$$", false);
	bt_Send("SM,1");
	bt_Send("I,5");
	bt_Send("---"); 

	while (!bt_Connected) {
		delay(100);
		bt_receive();
		int msgLength = strlen(bluetoothMsg);
		if (msgLength > 0) {
			if (msgLength >= 12) {
				char* doneMsg = &bluetoothMsg[msgLength - 12];
				bluetoothMsg[12] = '\0';
				bool found_known_MAC = false;
				for (int i = 0; i < bt_devices_count && !found_known_MAC; i++) {
					if(!strcmp(bluetoothMsg, known_bt_macs[i])) {
						found_known_MAC = true;
					}
				}
				if (!strcmp(doneMsg, "Inquiry Done")) {
					digitalWrite(statusLight, HIGH);
					if (found_known_MAC) {              
						bluetoothCmd[0] = 'C';
						bluetoothCmd[1] = ',';
						for (int i = 0; i < 12; i++) {
							bluetoothCmd[i + 2] = bluetoothMsg[i];
						}
						bluetoothCmd[15] = '\0';
						bt_Send("$$$", false);
						bt_Send(bluetoothCmd);
						bt_Send("---");      
						delay(2000);
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
					}
				}
			}
		}
	}
	digitalWrite(boardLight, LOW);
	msgToken = 1;
}

void setup() {
	pinMode(boardLight, OUTPUT);
	pinMode(statusLight, OUTPUT);
	digitalWrite(statusLight, LOW);
	delay(1000);
	digitalWrite(statusLight, HIGH);
	delay(1000);
	digitalWrite(statusLight, LOW);
	delay(1000);
	digitalWrite(statusLight, HIGH);
	delay(1000);
	digitalWrite(statusLight, LOW);
	delay(1000);
	bt_initialize();
}

void send_msg() {
	delay(50);  
	Serial.print("R");
	delay(50); 
	Serial.print("R");
	delay(50);
	Serial.print("R");
	delay(50);
}

void loop() {  
	if (msgToken == 1) {
		digitalWrite(statusLight, HIGH);
		send_msg();
		delay(1200);
	} else {
		digitalWrite(statusLight, LOW);
	}
}
