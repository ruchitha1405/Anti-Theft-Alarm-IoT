#include <WiFi.h>
#include <WebServer.h>
//#include <Wire.h>
//#include <Adafruit_Sensor.h>
//#include <Adafruit_BME280.h>

//#define SEALEVELPRESSURE_HPA (1013.25)

//Adafruit_BME280 bme;

String temperature, humidity, pressure, distance,motion,led_status,buzzer_status;

/*Put your SSID & Password*/
const char* ssid = "YourNetworkName";  // Enter SSID here
const char* password = "YourPassword";  //Enter Password here

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
