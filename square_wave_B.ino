void setup() {
  // set pins 1 (serial transmit) and 2..7 as output,
  // but leave pin 0 (serial receive) as input
  // (otherwise serial port will stop working!) ...
  DDRD = B11111110;  // digital pins 7,6,5,4,3,2,1,0
  // set pins 8..13 as output...
  DDRB = B00000011;  // digital pins -,-,13,12,11,10,9,8
  // Turn off digital output pins 2..7 ...
  //PORTD &= B00000011;   // turns off 2..7, but leaves pins 0 and 1 alone
  // Write simultaneously to pins 8..13...
  //PORTB = B00111000;   // turns on 13,12,11; turns off 10,9,8
}

void loop() {
  PORTD = B11111100; // turns pins 2-7 on
  PORTB = B00000011; // pins 8-9 on
  delay(70);
  PORTD = B11111000; // pin 2 off
  delay(75);
  PORTD = B11110000; // pin 3 off
  delay(80);
  PORTD = B11100000; // pin 4 off 
  delay(85);
  PORTD = B11000000; // pin 5 off
  delay(90);
  PORTD = B10000000; // pin 6 off
  delay(95);
  PORTD = B00000000; // pin 7 off
  delay(100);
  PORTB = B00000010; 
  delay(105);
  PORTB = B00000000;
  delay(115);
}

