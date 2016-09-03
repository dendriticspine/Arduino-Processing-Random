void setup() {
DDRA = B11111111;    // set as output mega pins 22-29  
DDRC = B11111111;    // set as output mega pins 30-37
}

void loop() {
PORTA = B11111111; // pins 22-29 on
PORTC = B11111111; // pins 30-37 on
delay(100);
PORTA = B11111110; // pin 22 off
delay(150);
PORTA = B11111100; // pin 23 off
delay(200);
PORTA = B11111000; // pin 24 off
delay(250);
PORTA = B11110000; // pin 25 off
delay(300);
PORTA = B11100000; // pin 26 off
delay(350);
PORTA = B11000000; // pin 27 off
delay(400);
PORTA = B10000000; // pin 28 off
delay(450); 
PORTA = B00000000; // pin 29 off
delay(500);
PORTC = B01111111; // pin 30 off
delay(550);
PORTC = B00111111; // pin 31 off
delay(600);
PORTC = B00011111; // pin 32 off
delay(650);
PORTC = B00001111; // pin 33 off
delay(700);
PORTC = B00000111; // pin 34 off
delay(750);
PORTC = B00000011; // pin 35 off
delay(800);
PORTC = B00000001; // pin 36 off
delay(850);
PORTC = B00000000; // pin 37 off
delay(900);
}

