#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DallasTemperature.h>
#include <OneWire.h>
#include <string>

// Create sensor object, connected to pin 2
#define PinDatos 2 
OneWire oneWireObjeto(PinDatos);
DallasTemperature sensorDS18B20(&oneWireObjeto);

// WiFi information
const char* ssid = "TP-LINK_B228EE";  
const char* password = "123456789"; 

// Create server
ESP8266WebServer server(80);
WiFiServer otherServer(80);

// Define functions
String SendHTML(float TemperatureWeb);
void handle_OnConnect();
void handle_NotFound();
void handle_usps(WiFiClient client);
void handle_heat(int stat, int temp);

// Define global variables
int RELAY=12;
float Temperature;

void setup() {
  Serial.begin(115200);

  // Connect to WiFi network
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected to WiFi");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  // Connect server to root
  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);
  server.begin();

  sensorDS18B20.begin();

// Start relay
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, HIGH);
}

void loop() {
  server.handleClient();
  WiFiClient client = otherServer.available();
  if (client.connected()) {
    handle_usps(client);
  }
  client.flush();
}

void handle_OnConnect() {
  sensorDS18B20.requestTemperatures();
  Temperature = sensorDS18B20.getTempCByIndex(0); 
  server.send(200, "text/html", SendHTML(Temperature)); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(float TemperatureWeb){
  String ptr = "";
  ptr += (int)TemperatureWeb;
  ptr += '/';
  ptr += digitalRead(RELAY);

  return ptr;
}

void handle_usps(WiFiClient client){
  String req = client.readStringUntil('\n');
  int temp = req.substring(0, (req.length() - 2)).toInt();
  int stat;
  if ((req[req.length()]) == "1") {
    handle_heat(1, temp);
  }
  else {
    digitalWrite(RELAY, LOW);
  }
  //handle_heat(stat, temp);
}

void handle_heat(int stat, int temp){
  if (stat == 1) {
      sensorDS18B20.requestTemperatures();
      Temperature = sensorDS18B20.getTempCByIndex(0);
      while (Temperature != temp) {
        digitalWrite(RELAY, HIGH);
        delay(60000);
      }
  }
  // Turn off relay if temp is achieved or stat is 0
  digitalWrite(RELAY, LOW);
}
