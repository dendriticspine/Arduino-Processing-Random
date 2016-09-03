int switchPin = 8;
int digPin = 9;
int ledPin = 13;
int pelPin = 2;

int flashcount = 0; 
int x = 0;


void setup()
{
  pinMode(switchPin, INPUT);
  pinMode(digPin,OUTPUT);
  pinMode(ledPin,OUTPUT);
  pinMode(pelPin,OUTPUT);
  Serial.begin(9600); 
}


void loop()
{

  if (digitalRead(switchPin) == HIGH)
  {
    digitalWrite(digPin, LOW);
    digitalWrite(ledPin, LOW);
    flashcount = 0;
  }

  else if (digitalRead(switchPin) == LOW)
  {

    if (flashcount <= 0)
    {
      flashcount = flashcount + 1;
      digitalWrite(digPin, HIGH);
      digitalWrite(ledPin, HIGH);
      delay(1);
      digitalWrite(digPin, LOW);
      digitalWrite(ledPin, LOW);
      delay(3);
    }
    else if (flashcount = 3)
    {
      delay(1000);
      digitalWrite(pelPin, HIGH);
      delay(1);
      digitalWrite(pelPin, LOW);
      delay(3);
      digitalWrite(pelPin, HIGH);
      delay(1);
      digitalWrite(pelPin, LOW);
      delay(3);
      digitalWrite(pelPin, HIGH);
      delay(1);
      digitalWrite(pelPin, LOW);
      x = x+1;
      Serial.print("\n"); 
      Serial.print(x);
    }

    else
    {
      digitalWrite(digPin, LOW);
      digitalWrite(ledPin, LOW);
      delay(1000);
    }
  }
}







