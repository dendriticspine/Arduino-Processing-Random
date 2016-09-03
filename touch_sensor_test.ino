//int sensor_1 = A0;
//int led = 9;
int motor = 11;
//float touchVolt;
//int ledOut;
//int motorOut;

void setup() {
  TCCR2B = TCCR2B & 0b11111000 | 0x06;
  Serial.begin(115200);
  pinMode(11, OUTPUT);
  //digitalWrite(sensor_1, HIGH); // enable pull-ups
}  

void loop() {
  //touchVolt = analogRead(sensor_1);
  //ledOut = touchVolt / 4;
  //motorOut = touchVolt / 8;
  //analogWrite(led, ledOut);
  analogWrite(motor, 250);
}

