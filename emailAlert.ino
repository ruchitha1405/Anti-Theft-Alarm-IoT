#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

const char* ssid = "Galaxy M511CCF";
const char* password = "*******";

// Email alerts through IFTTTS SERVER
const char *host = "maker.ifttt.com";
const char *privateKey = "*********";

// Email alerts
WebServer server(80);
void send_event(const char *event);
int led_pin = 14;
int sensor_pin = 13;

String Message;

const char MAIN_page[] PROGMEM = R"=====(

<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<style>
// code for css
</style>
</head>
<body>
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
<script>
// some code for xhttp stuff
</script>
</html>
)=====";

void Root() {
  String s = MAIN_page;server.send(200, "text/html", s);
}

void read() 
{
  if(digitalRead(sensor_pin) == HIGH)
  {
    digitalWrite (led_pin, HIGH);
    delay(1000);
    digitalWrite (led_pin, LOW);
    Message = "Motion Detected";
    String data = "{String(Message)}";
    server.send(200, "text/plane", data);
    send_event("Motion_Detection");
    Serial.println("Motion detected!");
  }
}
void setup() 
{
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
  delay(500);
  Serial.println("Connecting!");
  }
  Serial.println("");
  Serial.println("Successfully connected to WiFi.");
  Serial.println("IP address is : ");
  Serial.println(WiFi.localIP());
  server.on("/", Root);
  server.on("/read", read);
  server.begin();
  pinMode(sensor_pin, INPUT);
  pinMode(led_pin, OUTPUT);
  digitalWrite (led_pin, LOW);
}

void loop()
{
  server.handleClient();
}
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

