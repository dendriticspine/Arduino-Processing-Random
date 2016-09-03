int analogPin = 0;

void setup() {
  // initialize the serial communication:
  Serial.begin(57600);
}

void loop() {
  // send the value of analog input 0:
  Serial.println(analogRead(analogPin));
  // wait a bit for the analog-to-digital converter 
  // to stabilize after the last reading:
  delay(2);
}
