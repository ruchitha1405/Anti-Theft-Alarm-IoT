#include "DHT.h"
#define DHTTYPE DHT11
#define dht_dpin 5
#define trig 14
#define echo 27
#define pin 12
bool motiondetected;
float temp1;
float temp2;
DHT dht(dht_dpin, DHTTYPE);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(pin, INPUT);
}

void loop() {
  temp1 = dht.readTemperature();
  digitalWrite(trig, LOW);
  delay(2);
  digitalWrite(trig, HIGH);
  delay(10);
  digitalWrite(trig, LOW);
  //Serial.print("Distance: ");
  int a = pulseIn(echo, HIGH)*0.034/2;
  delay(1000);
  digitalWrite(trig, LOW);
  delay(2);
  digitalWrite(trig, HIGH);
  delay(10);
  digitalWrite(trig, LOW);
  int b = pulseIn(echo, HIGH)*0.034/2;
  digitalWrite(trig, LOW);
  motiondetected = digitalRead(pin);
  Serial.println(motiondetected);
  if(a - b > 2 || motiondetected == TRUE)
  {
    Serial.println("ALERT");
  }
  temp2 = dht.readTemperature();
  if(temp2 - temp1 > 1.5)
  {
    Serial.println("Fire alert");
  }

}
