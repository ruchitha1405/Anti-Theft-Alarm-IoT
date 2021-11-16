#include <WiFi.h>
#include <WebServer.h>
#include <WiFiClient.h>
//#include <Wire.h>
//#include <Adafruit_Sensor.h>
//#include <Adafruit_BME280.h>

//#define SEALEVELPRESSURE_HPA (1013.25)

//Adafruit_BME280 bme;

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
 temperature=GetTemperature();
  humidity=GetHumidity();
  pressure=GetPressure();
  led_status=GetLed_status();
  buzzer_status=GetBuzzer_status();
  distance=GetDistance();
  motion=GetMotion();
}

//**************SENSOR FUNCTIONS START*************************
GetTemperature(){}
GetHumidity(){}
GetPressure(){}
GetLed_status(){}
GetBuzzer_status(){}
GetDistance(){}
GetMotion(){}
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
