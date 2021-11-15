#include "DHT.h"

#define pirPin 19
#define motionLed 18
#define fireLed 21
#define DHTpin 23
#define buzzer 22
#define DHTpin 4

#define DHTtype DHT11
DHT dht(DHTpin, DHTtype);

String username = "Bhargavi";
String password = "1234";

String given_username = "";
String given_password = "";

bool isDetected;
int limit = 5;

int wrong_access = 0;

void setup()
{
  pinMode(pirPin, INPUT);
  pinMode(motionLed, OUTPUT);
  pinMode(fireLed, OUTPUT);
  pinMode(buzzer, OUTPUT);

  digitalWrite(motionLed, LOW);
  digitalWrite(fireLed, LOW);
  digitalWrite(buzzer, LOW);

  Serial.begin(9600);
  dht.begin();

  Serial.println("--------------- Welcome :) -----------------");
  Serial.println("Please enter the valid credentials");
  while(limit != 0)
  {
    /*Serial.print("Username: ");
    if (Serial.available())
    {
      given_username = Serial.readString();
    }
    Serial.print("Password: ");
    if (Serial.available())
    {
      given_password = Serial.readString();
    }*/
    if(username.equals("Bhargavi") && password.equals("1234"))
    {
      Serial.println("Hey there, Successful authentication :) !!");
      return;
    }
    else
    {
      Serial.println("Invalid authentication!! Try again :( !!");
    }

    limit = limit - 1;
  }
  wrong_access = 1;
  
  digitalWrite(buzzer, HIGH);
  digitalWrite(motionLed, HIGH);
  digitalWrite(fireLed, HIGH);
}
void loop()
{
  if(wrong_access == 1)
  {
    return;
  }
  isDetected = digitalRead(pirPin);

  if (isDetected)
  {
    Serial.println("Motion detected");
    digitalWrite(motionLed, HIGH);
    digitalWrite(buzzer, HIGH);

    delay(3000);
  }
  else
  {
    Serial.println("No motion detected");
  }

  digitalWrite(buzzer, LOW);
  digitalWrite(motionLed, LOW);

  delay(2000);

  float t = dht.readTemperature();
  Serial.print("Temperature: ");
  Serial.println(t);

  if (t > 20.0)
  {
    digitalWrite(fireLed, HIGH);
    digitalWrite(buzzer, HIGH);

    delay(3000);
  }

  digitalWrite(buzzer, LOW);
  digitalWrite(motionLed, LOW);
  digitalWrite(fireLed, LOW);

  delay(1000);
}
