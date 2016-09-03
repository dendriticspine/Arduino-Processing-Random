const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the onboard LED pin
const int ttlPin =  7;       // the number of the TTL out pin

int leverState = 0;         // variable for reading the pushbutton status
int delayCount = 0;

void setup() {
  pinMode(ledPin, OUTPUT);   // initialize the LED pin as an output  
  pinMode(ttlPin, OUTPUT);   // initialize the TTL pin as an output  
  pinMode(buttonPin, INPUT); // initialize the pushbutton pin as an input
}

void loop(){
  leverState = digitalRead(buttonPin);
  while(leverState == HIGH && delayCount < 11) { // if the lever is pressed and the delay count is less than 11 (100 milliseconds)
    delay(10);                    // delay for 10 ms
    delayCount = delayCount + 1;  // increase the count by 1
  } 
  if (leverState == HIGH && delayCount > 10) {          // check if lever has made contact
      digitalWrite(ledPin, HIGH);       
      digitalWrite(ttlPin, HIGH);   
      delay(50);                     // delay for 50 ms
    //delayCount = 0;                // return the delay count to 0
    //digitalWrite(ledPin, LOW);
    //digitalWrite(ttlPin, LOW);
   } else {
      digitalWrite(ledPin, LOW);        // turn LED off
      digitalWrite(ttlPin, LOW); 
      delayCount = 0;
   }
}
