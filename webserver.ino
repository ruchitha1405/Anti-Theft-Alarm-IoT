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
const char HOME_page[] PROGMEM = R"=====(

<!DOCTYPE html>
<html>

<head>
    <meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=no">
    <title>Home</title>
<style>
* {
   box-sizing: border-box;
}

body {
   margin: 0;
   font-family: Arial;
   font-size: 17px;
}

#myVideo {
   position: fixed;
   right: 0;
   bottom: 0;
   min-width: 100%;
   min-height: 100%;
}

.content {
   position: fixed;
   bottom: 0;
   background: rgba(0, 0, 0, 0.5);
   color: #f1f1f1;
   width: 100%;
   padding: 20px;
}

#myBtn {
   width: 200px;
   font-size: 18px;
   padding: 10px;
   border: none;
   background: #ddd;
   color: midnightblue;
   cursor: pointer;
}

#myBtn:hover {
   background: black;
   color: white;
}
</style>
    
<script >
    function pageRedirect() {
    
    setTimeout("window.location.href = '/login'", 0);
}

var video = document.getElementById("myVideo");
var btn = document.getElementById("myBtn");

function myFunction() {
    if (video.paused) {
        video.play();
        btn.innerHTML = "Pause";
    } else {
        video.pause();
        btn.innerHTML = "Play";
    }
}</script>
    
</head>

<body>

    <video autoplay muted loop id="myVideo">
        <source src="https://st4.depositphotos.com/11486624/24816/v/600/depositphotos_248163784-stock-video-iot-internet-things-devices-symbols.mp4" type="video/mp4">
        Your browser does not support HTML5 video.
    </video>

    <div class="content">
        <h1>BigFoot</h1>
        <h3>Anti Theft and Fire alarm</h3>
        <p>IoT project Monson 2021</p>
        <p>- Bhargavi</p>
        <p>- Ruchita</p>
        <p>- Nandini</p>
        <p>- Girija</p>
        <button id="myBtn" onclick="pageRedirect()">Sign in</button>
    </div>

</body>
</html>
)=====";

const char LOGIN_page[] PROGMEM = R"=====(

<!DOCTYPE html>
<html>

<head>
    <meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=no">
    <title>Login</title>
    <script >
    var UserName = "Bhargavi"
var PassWord = "1234"
var maxChances = 5
var cur_chance = 0

function authentication() {
    var cust_Name = document.getElementById("myID").value;
    var cust_Password = document.getElementById("myPassword").value;
    if(cust_Name == UserName)
    {
        if(cust_Password == PassWord)
        {
            
            setTimeout("window.location.replace('/monitor'), 0")
        }
    }
    else{
        cur_chance = cur_chance + 1
        alert("Invalid Authenticaton !! Please try again. ");
    }
    
}
</script>

<style>
body {
    background-color: skyblue;
}

.login {
    position: absolute;
    left: 100px;
    top: 40px;
    border-radius: 100%;
}


#myVideo {
    position: fixed;
    right: 0;
    bottom: 0;
    min-width: 100%;
    min-height: 100%;
 }
 

.container {
    border-radius: 20px;
    padding-top: 400px;
    padding-bottom: 20px;
    padding-left: 25px;
    padding-right: 25px;

    background-color: skyblue;
    opacity: 0.9;
}

form { 
    color: midnightblue;
    font-size: 25px;
    font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, Oxygen, Ubuntu, Cantarell, 'Open Sans', 'Helvetica Neue', sans-serif;
    position: absolute;
    left: 600px;
    top: 100px;
    width: 550px;
    height: 700px;
    border-radius: 30px;
} 
input[type=text], input[type=password] { 
    width: 100%; 
    margin: 8px 0;
    padding: 12px 20px; 
    display: inline-block; 
    border: 3px solid midnightblue; 
    box-sizing: border-box; 
    border-radius: 10px;
    outline: none;
}
button { 
    font-size: 20px;
    background-color: midnightblue; 
    width: 100%;
    color: white; 
    padding: 15px; 
    margin: 10px 0px; 
    border: none; 
    cursor: pointer; 
    border-radius: 10px;
} 
button:hover { 
    transform: scale(1.02);
    opacity: 0.7; 
} 

</style>
    
    <meta charset="utf-8">
</head>

<body>
    <video autoplay muted loop id="myVideo">
        <source src="https://st4.depositphotos.com/11486624/24816/v/600/depositphotos_248163784-stock-video-iot-internet-things-devices-symbols.mp4" type="video/mp4">
        Your browser does not support HTML5 video.
    </video>

    <form>
        <div class="container">
            <div class="login">
                <img src="https://static.vecteezy.com/system/resources/previews/002/640/730/original/default-avatar-placeholder-profile-icon-male-vector.jpg" style="width: 360px; height:360px; border-radius: 100%; object-fit: cover; ">
            </div>
            <form>
                <label>Username : </label>
                <input type="text" id="myID" placeholder="Enter Username" name="username" required>
                <label>Password : </label>
                <input type="password" id="myPassword" placeholder="Enter Password" name="password" required>
                <button type="submit" onclick="authentication()">Login</button>
        </div>
    </form>
</body>


</html>

)=====";



String SendHTML_home(){
  String s = HOME_page;
  return s;
}
String SendHTML_login(){
   String s = LOGIN_page;
  return s;
} 
String SendHTML_monitor(String temperature,String humidity,String pressure,String led_status,String buzzer_status,String distance,String motion){

String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta charset=\"utf-8\">\n";
  ptr +="<title>Monitor</title>\n";
  
  ptr +="<style>body {background-image: url('https://clockwise.software/img/blog/best-iot-startups-to-follow/header-background.jpg');background-repeat: no-repeat;background-attachment: fixed;background-size: cover;}\n";
  ptr +=".container {margin: 150px 250px 80px 250px;display: flex;justify-content: space-between;}\n";
  ptr +=".safety_status {margin-left: 10px;margin-top: 10px;}\n";
  ptr +=".box {display: flex;}\n";
  ptr +=".hide {position: relative;z-index: 2;background-color: white;color: #444;margin-top: 40px;margin-left: -30px;padding: 30px;padding-bottom: 18px;padding-left: 55px;border-top-right-radius: 50px;border-bottom-right-radius: 50px;height: 50px;border: none;text-align: center;outline: none;font-size: 30px;font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, Oxygen, Ubuntu, Cantarell, 'Open Sans', 'Helvetica Neue', sans-serif;}\n";
  ptr +=".slidebtn {z-index: 3;border: none;outline: none;background: none;cursor: pointer;transition: 0.5s;}\n";
  ptr +=".slidebtn:hover{transform: scale(1.3);}\n";
  ptr +=".control-btns-panel {display: flex;justify-content: center;}\n";
  ptr +=".control-btn {margin: 30px;outline: none;border: none;padding: 30px;text-align: center;vertical-align: middle;height: 70px;font-size: 30px;font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, Oxygen, Ubuntu, Cantarell, 'Open Sans', 'Helvetica Neue', sans-serif;background-color: lightgreen;border-radius: 10px;cursor: pointer;transition: 0.3s;}\n";
  ptr +=".control-btn:hover {background-color: lightseagreen;color: white;transform: scale(1.1);}\n";
  ptr +="</style>\n";
  
  ptr +="<script>\n";
ptr +="setInterval(loadDoc,1000);\n";
ptr +="function loadDoc() {\n";
ptr +="var xhttp = new XMLHttpRequest();\n";
ptr +="xhttp.onreadystatechange = function() {\n";
ptr +="if (this.readyState == 4 && this.status == 200) {\n";
ptr +="document.body.innerHTML =this.responseText}\n";
ptr +="};\n";
ptr +="xhttp.open(\"GET\", \"/monitor\", true);\n";
ptr +="xhttp.send();\n";
ptr +="}\n";
ptr +="</script>\n";
  
  ptr +="</head>\n";
  
  ptr +="<body>\n";
  ptr +="<div class=\"container\">\n";
  ptr +="<div class=\"safety_status\">\n";
  ptr +="<div class=\"box\">\n";
  ptr +="<button class=\"slidebtn\"><img src=\"https://image.shutterstock.com/image-vector/led-light-bulb-icon-on-260nw-709931749.jpg\" style=\"width: 150px; height:150px; border-radius: 100%; object-fit: cover;\"></button>\n";
  ptr +="<div class=\"hide\">\n";
  ptr +=led_status;
  ptr += "</div>\n";
  ptr += "</div>\n";
  ptr += "<br>\n";
  ptr += "<br>\n";
  ptr +="<div class=\"box\">\n";
  ptr +="<button class=\"slidebtn\"><img src=\"https://st.depositphotos.com/1310390/4858/v/950/depositphotos_48584945-stock-illustration-temperature-icon-with-a-thermometer.jpg\" style=\"width: 150px; height:150px; border-radius: 100%; object-fit: cover;\"></button>\n";
  ptr +="<div class=\"hide\">\n";
  ptr += temperature;
  ptr += "</div>\n";
  ptr += "</div>\n";
  ptr += "<br>\n";
  ptr += "<br>\n";
  ptr += "<div class=\"box\">\n";
  ptr += "<button class=\"slidebtn\"><img src=\"https://media.istockphoto.com/vectors/motion-sensor-icon-in-comic-style-sensor-waves-with-man-vector-vector-id1093505818\" style=\"width: 150px; height:150px; border-radius: 100%; object-fit: cover;\"></button>\n";
  ptr += "<div class=\"hide\">\n";
  ptr += motion;
  ptr += "</div>\n";
  ptr += "</div>\n";
  ptr += "</div>\n";

  ptr += "<div class=\"safety_status\">\n";
  ptr += "<div class=\"box\">\n";
  ptr += "<button class=\"slidebtn\"><img src=\"https://media.istockphoto.com/vectors/emergency-siren-icon-in-flat-style-police-alarm-vector-illustration-vector-id1144204158?k=20&m=1144204158&s=170667a&w=0&h=vWFXabMbVd42h0XOVN9OCnFotB41Ul4thJNVos_BuWg=\" style=\"width: 150px; height:150px; border-radius: 100%; object-fit: cover;\"></button>\n";
  ptr += "<div class=\"hide\">\n";
  ptr += buzzer_status;
  ptr += "</div>\n";
  ptr += "</div>\n";
  ptr += "<br>\n";
  ptr += "<br>\n";
  ptr += "<div class=\"box\">\n";
  ptr += "<button class=\"slidebtn\"><img src=\"https://previews.123rf.com/images/sanek13744/sanek137441908/sanek13744190800082/128009902-humidity-icon-in-comic-style-climate-vector-cartoon-illustration-on-white-isolated-background-temper.jpg\" style=\"width: 150px; height:150px; border-radius: 100%; object-fit: cover;\"></button>\n";
  ptr += "<div class=\"hide\">\n";
  ptr += humidity;
  ptr += "</div>\n";
  ptr += "</div>\n";
  ptr += "<br>\n";
  ptr += "<br>\n";
  ptr += "<div class=\"box\">\n";
  ptr += "<button class=\"slidebtn\"><img src=\"https://previews.123rf.com/images/sanek13744/sanek137441907/sanek13744190700721/127709069-distance-pin-icon-in-comic-style-gps-navigation-vector-cartoon-illustration-on-white-isolated-backgr.jpg\" style=\"width: 150px; height:150px; border-radius: 100%; object-fit: cover;\"></button>\n";
  ptr += "<div class=\"hide\">\n";
  ptr += distance;
  ptr += "</div>\n";
  ptr += "</div>\n";
  ptr += "</div>\n";
  ptr += "</div>\n";

  ptr += "<div class=\"control-btns-panel\">\n";
  

  
   /*if(led1stat)
  {ptr +="<p>LED1 Status: ON</p><a class=\"button button-off\" href=\"/led1off\">OFF</a>\n";}
  else
  {ptr +="<p>LED1 Status: OFF</p><a class=\"button button-on\" href=\"/led1on\">ON</a>\n";}

  if(led2stat)
  {ptr +="<p>LED2 Status: ON</p><a class=\"button button-off\" href=\"/led2off\">OFF</a>\n";}
  else
  {ptr +="<p>LED2 Status: OFF</p><a class=\"button button-on\" href=\"/led2on\">ON</a>\n";}
*/
  ptr += "<button class=\"control-btn\">LED</button>\n";
  ptr += "<button class=\"control-btn\">Buzzer</button>\n";
  ptr += "</div>\n";
  
  
  ptr +="</body>\n";
  
  ptr +="</html>\n";
  return ptr;
}
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
