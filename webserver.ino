#include <WiFi.h>
#include <WebServer.h>
#include <WiFiClient.h>
//#include <Wire.h>
//#include <Adafruit_Sensor.h>
//#include <Adafruit_BME280.h>

//#define SEALEVELPRESSURE_HPA (1013.25)

//Adafruit_BME280 bme;

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

int authentication = 0;
bool isDetected;
float t;
float humidity;
bool led_status;


String temperature, humidity, pressure, distance,motion,led_status,buzzer_status;

/*Put your SSID & Password*/
const char* ssid = "YourNetworkName";  // Enter SSID here
const char* password = "YourPassword";  //Enter Password here

// Email alerts through IFTTTS SERVER
const char *host = "maker.ifttt.com";
const char *privateKey = "*********";

WebServer server(80);             

void setup() {
  Serial.begin(115200);
  delay(100);

  //bme.begin(0x76);   

  Serial.println("Connecting to ");
  Serial.println(ssid);
  
  pinMode(pirPin, INPUT);
  pinMode(motionLed, OUTPUT);
  pinMode(fireLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(motionLed, LOW);
  digitalWrite(fireLed, LOW);
  digitalWrite(buzzer, LOW);
  dht.begin();
  Serial.println("--------------- Welcome -----------------");
  led_status = 0;

  //connect to your local wi-fi network
  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());

  server.on("/", handle_OnConnect);
  server.on("/login", handle_login);
  server.on("/monitor", handle_monitor);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");

}


void loop() {
  server.handleClient();
  Serial.println("Please enter the username");
  if(Serial.available() > 0)
  {
  username = Serial.read();
  Serial.println("Please enter the password");
  if(Serial.available() > 0){
  password = Serial.read();
  if(username.equals("User") && password.equals("1234"))
  {
    Serial.println("Hey there, Successful authentication !!");
    authentication = 1;
  }
   else
  {
    Serial.println("Invalid authentication!! Try again !!");
  }
  }
  }
  
  digitalWrite(buzzer, LOW);
  digitalWrite(motionLed, LOW);
  digitalWrite(fireLed, LOW);
  led_status = 0;
  isDetected = digitalRead(pirPin);
  humidity = dht.readHumidity();
  if (isDetected && authentication == 0)
  {
    Serial.println("Motion detected");
    digitalWrite(motionLed, HIGH);
    led_status = 1;
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
        digitalWrite(buzzer, LOW);
        digitalWrite(motionLed, LOW);
        led_status = 0;
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

  t = dht.readTemperature();
  Serial.print("Temperature: ");
  Serial.println(t);

  if (t > 50)
  {
    digitalWrite(fireLed, HIGH);
    led_status = 1;
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
      led_status = 1;
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

//**************SENSOR FUNCTIONS START*************************
//**************SENSOR FUNCTIONS END*************************
//**************HANDLE FUNCTIONS START*************************
void handle_OnConnect() {

  server.send(200, "text/html", SendHTML_home()); 
}
void handle_login(){
  server.send(200, "text/html", SendHTML_login()); }

void handle_monitor(){

  server.send(200, "text/html", SendHTML_monitor(temperature,humidity, pressure,led_status, buzzer_status, distance, motion));
  }

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}
//**************HANDLE FUNCTIONS END*************************
//**************SendHTML FUNCTIONS START*************************
String SendHTML_home(){}
String SendHTML_login(){} 
String SendHTML_monitor(String temperature,String humidity,String pressure,String led_status,String buzzer_status,String distance,String motion){}
//**************SendHTML FUNCTIONS END*************************

void send_event(const char *event)
{
  Serial.print("Connecting to ");
  Serial.println(host);
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) 
  {
  Serial.println("Connection failed");
  return;
  }
  String url = "/trigger/";
  url += event;
  url += "/with/key/";
  url += privateKey;
  Serial.print("Requesting URL: ");
  Serial.println(url);
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +"Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
  
  while(client.connected())
  {
    if(client.available())
    {
      // sends msg to server

      String line = client.readStringUntil('\r');
      Serial.print(line);
    } 
    else 
    {
      delay(50);
    }
  }
  Serial.println();
  Serial.println("Closing Connection");
  client.stop();
}
