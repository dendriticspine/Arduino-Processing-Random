int lightB = 7;
int lightG = 6;
int lightR = 5;
int masterPin = 4;
int isMaster = 0;
int msgToken = 0;

int incomingByte = 0;
char gBtMsg[256];
char gBTAdr[13];
char gBtCmd[256];

int gBtKnownMACTotal = 2;
char* gBtKnownMAC[2];								// this is set to hold only two MAC addresses

void BtReceive(void) {
	bool keepReading = true;
	int index = 0;
	gBtMsg[0] = '\0';
  
	while (keepReading){
		keepReading = false;
		if (Serial.available() > 0) {
			incomingByte = Serial.read();        	// read the incoming byte
			if (incomingByte != 13) {
				gBtMsg[index++] = incomingByte;
				keepReading = true;
			}
		}
	}
	gBtMsg[index] = '\0';
}

void BtSend(char* i_pBtCmd, bool i_ln = true) {
	if (i_ln) {
		Serial.println(i_pBtCmd);
	} else {
		Serial.print(i_pBtCmd);
	}
	delay(100);
	BtReceive();
}

void BtInit(void) {
	isMaster = digitalRead(masterPin); 
	bool btConnect = false;
	digitalWrite(lightR,HIGH);
	gBtKnownMAC[0] = "0006664F9414";		// Green:  0006664F9414
	gBtKnownMAC[1] = "0006664F89B7";		// Blue:   0006664F89B7
	Serial.begin(115200); 
	BtSend("$$$", false);
  
	if (isMaster == LOW) {
		BtSend("SM,1");
		BtSend("I,5");
		BtSend("---"); 
   
		while (!btConnect) {
			delay(100);
			BtReceive();
			int msgLen = strlen(gBtMsg);
			
			if (msgLen > 0) {
				if (msgLen >= 12) {
					char* doneMsg = &gBtMsg[msgLen - 12];
					gBtMsg[12] = '\0';
					bool foundKnownMAC = false;
				  
					for (int i = 0; i < gBtKnownMACTotal && !foundKnownMAC; i++) {
						if(!strcmp(gBtMsg, gBtKnownMAC[i])) {
							foundKnownMAC = true;
						}
					}
				  
					if (!strcmp(doneMsg, "Inquiry Done")) {
						digitalWrite(lightB,HIGH);
						if (foundKnownMAC) {              
							gBtCmd[0] = 'C';
							gBtCmd[1] = ',';
					  
							for(int i = 0; i < 12; i++) {
								gBtCmd[i + 2] = gBtMsg[i];
							}
						  
							gBtCmd[15] = '\0';
							BtSend("$$$", false);
							BtSend(gBtCmd);
							BtSend("---");      
							delay(2000);
							digitalWrite(lightG,HIGH);
						  
							while (!btConnect) {
								delay(1000);
								BtSend("$$$", false);
								BtSend("GK");
							
								int numVal = 0;
				  
								if (strlen(gBtMsg) > 0) {
									numVal= atoi(gBtMsg);
								}
							
								if (numVal == 1) {
									btConnect = true;
								}
								BtSend("---");
							}
						}
					}
				}
			}
		}
		digitalWrite(lightG,LOW);
		digitalWrite(lightB,LOW);
		msgToken = 1;
	} else {
		BtSend("SM,0");
		BtSend("---"); 
		while (!btConnect) {
			delay(1000);
			BtSend("$$$", false);
			BtSend("GK");
			int numVal = 0;
			if (strlen(gBtMsg) > 0) {
				numVal= atoi(gBtMsg);
			}
			if (numVal == 1) {                  
				btConnect = true;
			}
			BtSend("---");              
		}
	}
	digitalWrite(lightR,LOW);
}

void setup() {
	pinMode(lightR, OUTPUT);
	pinMode(lightG, OUTPUT);
	pinMode(lightB, OUTPUT);
	pinMode(isMaster, INPUT);
  
	digitalWrite(lightR,LOW);
	digitalWrite(lightG,LOW);
	digitalWrite(lightB,HIGH);
	delay(500);
	digitalWrite(lightB,LOW);
	digitalWrite(lightR,HIGH);
	delay(500);
	digitalWrite(lightR,LOW);
	digitalWrite(lightG,HIGH);
	delay(500);
	digitalWrite(lightG,LOW);  

	BtInit();
}

void receiveMsg(){  
	for (int i = 0; i < 10; i++) {
		if (Serial.available() > 0) {
			incomingByte = Serial.read();      // read the incoming byte
			if (incomingByte == 'R') {
				digitalWrite(lightB, LOW);
				delay(50);
				digitalWrite(lightB,HIGH);
			}
		}
		delay(100);
	}
}

void sendMsg() {
	digitalWrite(lightG,LOW);  
	delay(50);  
	Serial.print("R");
	digitalWrite(lightG,HIGH);
	delay(50);  
	Serial.print("R");
	digitalWrite(lightG,LOW);  
	delay(50);  
	digitalWrite(lightG,HIGH);
	Serial.print("R");
}

void loop() {  
	if (msgToken == 1) {
		digitalWrite(lightG,HIGH);
		sendMsg();
		delay(1000);
	} else {
		digitalWrite(lightB,HIGH);
		receiveMsg();
	}
}

