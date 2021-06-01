/* RestClient simple GET request
 *
 * by Fabiano França (fabianofranca)
 */

#include "RestClient.h"

RestClient client = RestClient("arduino-http-lib-test.herokuapp.com");

//Setup
void setup() {
  Serial.begin(9600);
  Serial.println("connect to WiFi network");
  client.begin("ssid", "password");
  Serial.println("Setup!");
}

String response;
void loop(){
  response = "";
  int statusCode = client.get("/get", &response);
  Serial.print("Status code from server: ");
  Serial.println(statusCode);
  Serial.print("Response body from server: ");
  Serial.println(response);
  delay(1000);
}
