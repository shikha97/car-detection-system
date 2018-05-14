
#define BLYNK_PRINT Serial

int pingpin=D1;
int pingpin1=D2;
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "63f3be663e7b4c1a8583f6586808677a";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Moto M";
char pass[] = "harshit2509";

void UL1()
{
  long cm=0,duration=0;
  //Distance measurment starts from here
  pinMode(pingpin,OUTPUT);
  digitalWrite(pingpin,LOW);
  delayMicroseconds(5);
  digitalWrite(pingpin,HIGH);
  delayMicroseconds(10); // This is the minimun required time for distance measurment 
  digitalWrite(pingpin,LOW);
  //Reading from sensor
  pinMode(pingpin,INPUT);
  duration = pulseIn(pingpin,HIGH);
  cm = microSeconds_to_cm(duration);
  //serial printing starts from here
  Serial.print("\n The Distance is:");
  Serial.print(cm);
  if(cm<350)
  {
   Blynk.virtualWrite(V0,HIGH); 
  }
  else
    Blynk.virtualWrite(V0,LOW);
  delay(1000);
}

void UL2()
{
  long cm=0,duration=0;
  //Distance measurment starts from here
  pinMode(pingpin1,OUTPUT);
  digitalWrite(pingpin1,LOW);
  delayMicroseconds(5);
  digitalWrite(pingpin1,HIGH);
  delayMicroseconds(10); // This is the minimun required time for distance measurment 
  digitalWrite(pingpin1,LOW);
  //Reading from sensor
  pinMode(pingpin1,INPUT);
  duration = pulseIn(pingpin1,HIGH);
  cm = microSeconds_to_cm(duration);
  //serial printing starts from here
  Serial.print("\n The Distance is:");
  Serial.print(cm);
  if(cm<12)
  {
   Blynk.virtualWrite(V1,HIGH); 
  }
  else
    Blynk.virtualWrite(V1,LOW);
  delay(1000);
}

long microSeconds_to_cm(long microseconds)
{
    return microseconds/2/29;
}


void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  

}

void loop()
{
  Blynk.run();
  UL1();
  UL2();
}
