#include <WiFi.h>
#include <WebServer.h>

// Board pins

#define pirPin 4

int pirState = LOW;
int val = 0;
bool trig = false;
String data = "";
String page = "";

// SSID & Password
const char* ssid = "";  
const char* password = "";  

WebServer server(80);  // Object of WebServer(HTTP port, 80 is default)

void setup() {

  pinMode(BuzzPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(pirPin, INPUT);
  
  Serial.begin(9600);

  delay(1000);
  
  Serial.print("Try Connecting to ");
  Serial.println(ssid);
  
  delay(500);
  
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected successfully");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());  
  
  server.on("/data.txt", [](){
     if(trig){
       data = "Person Detected!";
     }else{
       data = "No motion detected";
     }
     server.send(200, "text/html", data);
   });
   server.on("/", [](){
     page = "<h1>PIR Sensor to NodeMCU</h1><h1>Data:</h1> <h1 id=\"data\">""</h1>\r\n";
     page += "<script>\r\n";
     page += "var x = setInterval(function() {loadData(\"data.txt\",updateData)}, 1000);\r\n";
     page += "function loadData(url, callback){\r\n";
     page += "var xhttp = new XMLHttpRequest();\r\n";
     page += "xhttp.onreadystatechange = function(){\r\n";
     page += " if(this.readyState == 4 && this.status == 200){\r\n";
     page += " callback.apply(xhttp);\r\n";
     page += " }\r\n";
     page += "};\r\n";
     page += "xhttp.open(\"GET\", url, true);\r\n";
     page += "xhttp.send();\r\n";
     page += "}\r\n";
     page += "function updateData(){\r\n";
     page += " document.getElementById(\"data\").innerHTML = this.responseText;\r\n";
     page += "}\r\n";
     page += "</script>\r\n";
     server.send(200, "text/html", page);
  });


  server.begin();
}

void loop() {
  server.handleClient();
  
  val = digitalRead(pirPin);
  if(val == 0)
  {
    trig = false;
  }
  else
  {
    trig = true;
  }
  
}
