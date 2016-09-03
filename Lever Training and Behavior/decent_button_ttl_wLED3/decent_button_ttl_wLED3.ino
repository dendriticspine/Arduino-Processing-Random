int levPin = 8;
int tdtPin = 9;
int ledPin = 13;
int pelPin = 2;

int restrict = 0;

void setup()
{
  pinMode(levPin, INPUT);
  pinMode(tdtPin,OUTPUT);
  pinMode(ledPin,OUTPUT);
  pinMode(pelPin,OUTPUT);
}

void loop()
{

  if (digitalRead(levPin) == HIGH)
  {
    digitalWrite(tdtPin, LOW);
    digitalWrite(ledPin, LOW);
    restrict = 1;
  }

  else if (digitalRead(levPin) == LOW)
  {
    if (restrict == 1)
    {
      digitalWrite(tdtPin, HIGH);
      digitalWrite(ledPin, HIGH);
      delay(1);
      digitalWrite(tdtPin, LOW);
      
      delay(19);
      digitalWrite(ledPin, LOW);
      restrict = 0;
    }
    else
    {
      digitalWrite(tdtPin, LOW);
      digitalWrite(ledPin, LOW);
    }
    delay(2000-1-20);
  }
  else
  {
    digitalWrite(tdtPin, LOW);
    digitalWrite(ledPin, LOW);
  }
}






