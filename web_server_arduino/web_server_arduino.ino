#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include <DallasTemperature.h>
#include <OneWire.h>

// Create sensor object, connected to pin 2
#define PinDatos 2 
OneWire oneWireObjeto(PinDatos);
DallasTemperature sensorDS18B20(&oneWireObjeto);

// Router information
const char* ssid = "TP-LINK_B228EE";  
const char* password = "123456789"; 

// Static IP information
IPAddress staticIP(192, 168, 1, 111); //Static IP address
IPAddress gateway(192, 168, 1, 1); //Router's IP address
IPAddress subnet(255, 255, 255, 0);
IPAddress dns(8, 8, 8, 8);
const char* deviceName = "pava";

// Create server
ESP8266WebServer server(80);

// Define functions
String SendHTML(float TemperatureWeb);
void handle_OnConnect();
void handle_NotFound();
void turnOn();
void turnOff();
void tempData();
void statusData();

// Define global variables
int RELAY=12;
float Temperature;

void setup() {
  Serial.begin(115200);

  // Connect to WiFi network
  WiFi.hostname(deviceName);
  WiFi.config(staticIP, gateway, subnet, dns);
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
  // API
  server.on("/on", turnOn);
  server.on("/off", turnOff);
  server.on("/actualTemp", tempData);
  server.on("/actualStatus", statusData);
  server.begin();

  sensorDS18B20.begin();

// Start relay
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, LOW);
}

void loop() {
  server.handleClient();
}

void handle_OnConnect() {
  sensorDS18B20.requestTemperatures();
  Temperature = sensorDS18B20.getTempCByIndex(0);
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/html", SendHTML(Temperature));
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(float Temperature){
  String ptr = "";
  ptr += (int)Temperature;
  ptr += '/';
  ptr += digitalRead(RELAY);

  return ptr;
}

void turnOn() {
  int tempValue = server.arg(0).toInt();
  sensorDS18B20.requestTemperatures();
  Temperature = sensorDS18B20.getTempCByIndex(0);
  if (tempValue <= Temperature) {
    return;
  }

  if (tempValue == 0) {
    tempValue = 100;
  }

  digitalWrite(RELAY, HIGH);
  String placeholder_text = "Heating up water, please hold\n";
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", placeholder_text);

  while (tempValue >= Temperature) {
    // Handle other requests while heating up
    server.handleClient();
    // Update Temperature value to make necessary checks
    sensorDS18B20.requestTemperatures();
    Temperature = sensorDS18B20.getTempCByIndex(0);
  }

  digitalWrite(RELAY, LOW);
}

void turnOff() {
  digitalWrite(RELAY, LOW);
  String status_text = "";
  status_text += digitalRead(RELAY);
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", status_text);
}

void tempData() {
  sensorDS18B20.requestTemperatures();
  Temperature = sensorDS18B20.getTempCByIndex(0);
  String temp = "";
  temp += (int)Temperature;
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", temp);
}

void statusData() {
  String status_text = "";
  int stat = digitalRead(RELAY);
  status_text += stat;
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", status_text);
}
