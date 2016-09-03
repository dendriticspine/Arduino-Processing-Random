int levPin = 8;
int tdtCh1Pin = 9;
int tdtCh2Pin = 10;
int ledPin = 13;


int restrict = 0;

void setup()
{
  pinMode(levPin, INPUT);
  pinMode(tdtCh1Pin,OUTPUT);
  pinMode(tdtCh2Pin,OUTPUT);
  pinMode(ledPin,OUTPUT);

}

void loop()
{

  if (digitalRead(levPin) == HIGH)
  {
    digitalWrite(tdtCh1Pin, LOW);
    digitalWrite(tdtCh2Pin, LOW);
    digitalWrite(ledPin, LOW);
    restrict = 1;
  }

  else if (digitalRead(levPin) == LOW)
  {
    if (restrict == 1)
    {
      digitalWrite(tdtCh1Pin, HIGH);
      digitalWrite(ledPin, HIGH);
      restrict = 0;
      delay(1);
      digitalWrite(tdtCh1Pin, LOW);

      delay(19);
      digitalWrite(ledPin, LOW);


      delay(200);
      digitalWrite(tdtCh2Pin, HIGH);
      delay(1);
      digitalWrite(tdtCh2Pin, LOW);

    }
    else
    {
      digitalWrite(tdtCh1Pin, LOW);
      digitalWrite(tdtCh2Pin, LOW);
      digitalWrite(ledPin, LOW);

    }
    delay(2000-1-20-1000);
  }
  else
  {
    digitalWrite(tdtCh1Pin, LOW);
    digitalWrite(tdtCh2Pin, LOW);
    digitalWrite(ledPin, LOW);

  }
}









