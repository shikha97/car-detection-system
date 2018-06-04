#include <SoftwareSerial.h>
SoftwareSerial bt(11, 12);

int lm1 = 2;
int lm2 = 3;
int rm1 = 4;
int rm2 = 5;
int l1 = 12;
int l2 = 13;
int val;
const int pingPin = 7;

void setup()
{
  pinMode(l1, OUTPUT);
  pinMode(l2, OUTPUT);
  pinMode(lm1, OUTPUT);
  pinMode(lm2, OUTPUT);
  pinMode(rm1, OUTPUT);
  pinMode(rm2, OUTPUT);
  Serial.begin(9600);
  bt.begin(9600);
  Serial.print("Establishing BT" );
}

void loop()
{
  char x = '0';
  char t = '0';
  
  //delay(500);
  long duration, inches, cm;
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  //delay(100);
  if (bt.available())
  {
    x = bt.read();
    Serial.print("BT input:");
    Serial.println(x);
    delay(100);

    if (x == 'B' || t == 'y')
    {
      Serial.println("FORWARD");
      digitalWrite(lm1, HIGH);
      digitalWrite(rm1, HIGH);
      digitalWrite(lm2, LOW);
      digitalWrite(rm2, LOW);

    }
    else if (x == 'B' || t == 'n')
    {
      Serial.println("FORWARD, dont blast");
      digitalWrite(lm1, HIGH);
      digitalWrite(lm2, LOW);
      digitalWrite(rm1, HIGH);
      digitalWrite(rm2, LOW);

    }

    /*********For Backward Motion*********/
    else if (x == 'F' || t == 'y')
    {
      Serial.println("BACK");
      digitalWrite(lm2, HIGH);
      digitalWrite(rm2, HIGH);
      digitalWrite(lm1, LOW);
      digitalWrite(rm1, LOW);

    }

    else if (x == 'F' || t == 'n')
    {
      Serial.println("BACK, dont fire");
      digitalWrite(lm2, HIGH);
      digitalWrite(lm1, LOW);
      digitalWrite(rm2, HIGH);
      digitalWrite(rm1, LOW);
    }
    /*********Right*********/
    else if (x == 'R' || t == 'y')
    {
      Serial.println("RIGHT");
      digitalWrite(lm1, HIGH);
      digitalWrite(rm2, HIGH);
      digitalWrite(lm2, LOW);
      digitalWrite(rm1, LOW);
    }
    else if (x == 'R' || t == 'n')
    {
      Serial.println("RIGHT dont fire");
      digitalWrite(lm1, HIGH);
      digitalWrite(lm2, LOW);
      digitalWrite(rm1, LOW);
      digitalWrite(rm2, HIGH);
    }
    /*********Left*********/
    else if (x == 'L' || t == 'y')
    {
      Serial.println("LEFT");
      digitalWrite(lm2, HIGH);  digitalWrite(rm1, HIGH);
      digitalWrite(lm1, LOW);       digitalWrite(rm2, LOW);
    }
    else if (x == 'L' || t == 'n')
    {
      Serial.println("LEFT dont fire");
      digitalWrite(lm2, HIGH);
      digitalWrite(lm1, LOW);
      digitalWrite(rm2, LOW);
      digitalWrite(rm1, HIGH);
    }
    else if (x == 'S' || t == 'y')
    {
      Serial.println("STOP");
      digitalWrite(lm2, LOW);
      digitalWrite(rm1, LOW);
      digitalWrite(lm1, LOW);
      digitalWrite(rm2, LOW);
    }
    else if (x == 'S' || t == 'n')
    {
      Serial.println("STOP dont fire");
      digitalWrite(lm1, HIGH);
      digitalWrite(lm2, HIGH);
      digitalWrite(rm1, HIGH);
      digitalWrite(rm2, HIGH);
    }
  }
}
long microsecondsToInches(long microseconds)
{
  return microseconds / 74 / 2;
}
long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}
