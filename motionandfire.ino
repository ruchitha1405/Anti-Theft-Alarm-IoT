#include "DHT.h"

#define pirPin 19
#define motionLed 18
#define fireLed 21
#define DHTpin 23
#define buzzer 22

#define DHTtype DHT11
DHT dht(DHTpin, DHTtype);

String username = "Bhargavi";
String password = "1234";

bool isDetected;

void setup()
{
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  pinMode(motionLed, OUTPUT);
  pinMode(fireLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(motionLed, LOW);
  digitalWrite(fireLed, LOW);
  digitalWrite(buzzer, LOW);
  dht.begin();
  Serial.println("--------------- Welcome 🙂 -----------------");
}

void loop()
{
  int authentication = 0;
  Serial.println("--------------- Welcome 🙂 -----------------");
  Serial.println("Please enter the username");
  if(Serial.available() > 0)
  {
  username = Serial.read();
  Serial.println("Please enter the password");
  if(Serial.available() > 0){
  password = Serial.read();
  if(username.equals("User") && password.equals("1234"))
  {
    Serial.println("Hey there, Successful authentication 🙂 !!");
    authentication = 1;
  }
   else
  {
    Serial.println("Invalid authentication!! Try again 😦 !!");
  }
  }
  }
  
  digitalWrite(buzzer, LOW);
  digitalWrite(motionLed, LOW);
  digitalWrite(fireLed, LOW);
  isDetected = digitalRead(pirPin);

  if (isDetected && authentication == 0)
  {
    Serial.println("Motion detected");
    digitalWrite(motionLed, HIGH);
    digitalWrite(buzzer, HIGH);
    while(1)
    {
    Serial.println("Motion detected. If this is something you know please press y");
    if(Serial.available() > 0)
    {
      char yes;
      yes = Serial.read();
      if(yes == 'y')
      {
        continue;
      }
    }
    delay(1000);
  }
  }
  else
  {
    Serial.println("No motion detected");
  }

  float t = dht.readTemperature();
  Serial.print("Temperature: ");
  Serial.println(t);

  if (t > 50)
  {
    digitalWrite(fireLed, HIGH);
    digitalWrite(buzzer, HIGH);
  }

  while(authentication == 1)
  {
    isDetected = digitalRead(pirPin);
    if(isDetected)
    {
      Serial.println("Motion detected");
    }
    float t = dht.readTemperature();
    Serial.print("Temperature: ");
    Serial.println(t);

    if (t > 50)
    {
      digitalWrite(fireLed, HIGH);
      digitalWrite(buzzer, HIGH);
    }
    char exiting;
    if(Serial.available() > 0)
    {
      exiting = Serial.read();
      if(exiting == 'q')
      {
        authentication = 0;
      }
    }
    delay(1000);
    
  }
}
