int torqueSensorPin = 1;     // analog input on this pin

void setup() {
  pinMode(torqueSensorPin, INPUT); 
  Serial.begin(115200);
}
 
void loop() {
   int torqueValue = analogRead(torqueSensorPin)/4;
   // send the value out the serial port:
   //Serial.print(torqueValue, BYTE);
   Serial.write(torqueValue);
   Serial.send_now();
   delay(2);
}
