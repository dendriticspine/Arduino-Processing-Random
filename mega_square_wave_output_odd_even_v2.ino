void setup() {
  DDRA = B11111111;    // set as output mega pins 22-29  
  DDRC = B11111111;    // set as output mega pins 30-37
}

//PORTA
//   29 28 27 26 25 24 23 22 
//B  1  1  1  1  1  1  1  1

//PORTC
//   30 31 32 33 34 35 36 37 
//B  1  1  1  1  1  1  1  1

// these are annoying because I had to compensate for wiring issues

void loop() {
  PORTA = B11111111; // pins 22-29 on
  PORTC = B11111111; // pins 30-37 on
  delay(100);
  PORTA = B11111110; // 22 off : 23-29 on
  delay(150);
  PORTA = B11111010; // 22, 24 off : 23, 25-29 on
  delay(200);
  PORTA = B11101010; // 22, 24, 26 off : 23, 25, 27-29 on
  delay(250);
  PORTA = B10101010; // 22, 24, 26, 28 off : 23, 25, 27, 29 on
  delay(300);
  PORTC = B01111111; // 30 off : 31-27 on
  delay(350);
  PORTC = B01011111; // 30, 32 off : 31, 33-37 on
  delay(400);
  PORTC = B01010111; // 30, 32, 34 off : 31, 33, 35-37 on
  delay(450); 
  PORTC = B01010101; // 30, 32, 34, 36 off : 31, 33, 35, 37 on
  delay(500);
  PORTA = B10101000; // 22, 23, 24, 26, 28 off : 25, 27, 29 on
  delay(550);
  PORTA = B10100000; // 22-26, 28 off : 27, 29 on
  delay(600);
  PORTA = B10000000; // 22-28 off ; 29 on
  delay(650);
  PORTA = B00000000; // 22-29 off
  delay(700);
  PORTC = B00010101; // 30-32, 34, 36 off : 33, 35, 37 on
  delay(750);
  PORTC = B00000101; // 30-33, 34, 36 off : 35, 37 on
  delay(800);
  PORTC = B00000001; // 30-36 off : 37 on
  delay(850);  
  PORTC = B00000000; // 30-37 off
  delay(900);
}

