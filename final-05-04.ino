#define BLYNK_PRINT Serial
#include <SPI.h>
#include <Ethernet.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>

char auth[] = "63f3be663e7b4c1a8583f6586808677a";
char ssid[] = "Moto M";
char pass[] = "harshit2509";

#define DHTPIN D2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
//int fan = D6;

int temp_soil_value = 0;
int pinValue1;
int pinValue2;
int pinValue3;
int pinValue4;
int soil, light;

BLYNK_WRITE(V2)
{
  pinValue1 = param.asInt();

}

BLYNK_WRITE(V3)
{
  pinValue2 = param.asInt();

}

BLYNK_WRITE(V19)
{
  pinValue3 = param.asInt();

}

BLYNK_WRITE(V20)
{
  pinValue4 = param.asInt();

}

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
}

void analogsensor()
{
  digitalWrite(D8, LOW);
  light = analogRead(A0);
  Serial.print("Light is:");
  Serial.println(light);
  light = map(light, 0, 1023, 0, 100);
  Blynk.virtualWrite(V12, light);// display light on the app

  delay(500);
  digitalWrite(D8, HIGH);
  soil = analogRead(A0);
  Serial.print("Moisture is:");
  Serial.println(soil);
  soil = map(soil, 0, 1023, 0, 100);
  Blynk.virtualWrite(V13, soil);
  delay(500);
  
  Serial.print("pinValue1 is");
  Serial.println(pinValue1);
  Serial.print("pinValue2 is");
  Serial.println(pinValue2);
  Serial.print("pinValue3 is");
  Serial.println(pinValue3);
  Serial.print("pinValue4 is");
  Serial.println(pinValue4);
}

void ext_switch_master()
{
  int x = digitalRead(D1);
  Serial.print("x:");
  Serial.println(x);

  if (x == LOW)// slave mode: AUTOMATIC
  { Blynk.virtualWrite(V25, 0);
    sendSensor();
    analogsensor();
    ctrl_pump();
    ctrl_light();
    
  }
  else
  { Blynk.virtualWrite(V25, 255);
    int a=digitalRead(D3);
    if(a==HIGH)
    {
      digitalWrite(D7,HIGH);
    }
    else
    {
      digitalWrite(D7,LOW);
      
    }
    int b=digitalRead(D0);
    
    if(b==HIGH)
    {
       digitalWrite(D6,HIGH);
    }
    else
    {
      digitalWrite(D6,LOW);
    }
    Blynk.virtualWrite(V25, 255);
  }
  //delay(500);
}
void ctrl_pump()
{
  if (digitalRead(D1) == LOW)
  {
    if (digitalRead(D3) == LOW)
    {
      if (pinValue1 == 1)
      {
        digitalWrite(D7, HIGH);
        Blynk.virtualWrite(V4, 255);
        Blynk.virtualWrite(V0, 255);
      }
      else if (pinValue2 == 1)
      {
        digitalWrite(D7, LOW);
        Blynk.virtualWrite(V4, 0);
        Blynk.virtualWrite(V0, 0);
      }
      else
      {
        if (soil <= 50) //any temp value of soil
        {
          digitalWrite(D7, HIGH);
          Blynk.virtualWrite(V4, 255);
          Blynk.virtualWrite(V0, 255);
        }
        else
        {
          digitalWrite(D7, LOW);
          Blynk.virtualWrite(V4, 0);
          Blynk.virtualWrite(V0, 0);
        }
      }
    }
  
  else
  {
    digitalWrite(D7, HIGH);
  }
}
}

void ctrl_light()
{
  if (digitalRead(D1) == LOW)
  {
    if (digitalRead(D0) == LOW)
    {
      if (pinValue3 == 1)
      {
        digitalWrite(D6, HIGH);
        Blynk.virtualWrite(V7, 255);
        Blynk.virtualWrite(V1, 255);
      }
      else if (pinValue4 == 1)
      {
        digitalWrite(D6, LOW);
        Blynk.virtualWrite(V7, 0);
        Blynk.virtualWrite(V1, 0);
      }
    
    else
    {
      if (light <= 50)
      {
        digitalWrite(D6, HIGH);
        Blynk.virtualWrite(V7, 255);
        Blynk.virtualWrite(V1, 255);
      }
      else
      {
        digitalWrite(D6, LOW);
        Blynk.virtualWrite(V7, 0);
        Blynk.virtualWrite(V1, 0);
      }
    }
  }
  else
  {
    digitalWrite(D6, HIGH);
  }
}
}
void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(D1, INPUT);//master switch
  pinMode(D2, INPUT);//dht
  pinMode(D0, INPUT);//light switch
  pinMode(D5, OUTPUT);//in4
  pinMode(D6, OUTPUT);//in3
  pinMode(D7, OUTPUT);//in2
  pinMode(D8, OUTPUT);//in1
  dht.begin();
  timer.setInterval(1000L, ext_switch_master);
  //timer.setInterval(500L, sendSensor);
  //timer.setInterval(500L, analogsensor);
  //timer.setInterval(500L, ctrl_pump);
  //timer.setInterval(500L, ctrl_light);
  
}

void loop()
{
  Blynk.run();
  timer.run();
}
