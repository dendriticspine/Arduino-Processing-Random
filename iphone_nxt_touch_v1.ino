void setup() {                
  Serial.begin(9600);    // Start the serial port
  pinMode(3, OUTPUT);    // Trigger the Lego Motor in place of Lever A
  pinMode(5, OUTPUT);    // Trigger the Lego Motor in place of Lever B
}

void loop() {
  if (Serial.available()) {       // If there's anything on the serial port,
    byte cmd = Serial.read();     // read a single byte from it.

    if (cmd == '1') {            // If the command is the character '1',
      digitalWrite(3, HIGH);     // Trigger Lego Lever A
      delay(500);
      digitalWrite(3, LOW);
      Serial.write(cmd);
    } 
    if (cmd == '2') {  // If the command is the character '0',
      digitalWrite(5, HIGH);    // Trigger Lego Lever B
      delay(500);
      digitalWrite(5, LOW);
      Serial.write(cmd);
    }
  }
}

