#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "index_html.h"
#include "auth.h"
#include <Crypto.h>
#include <AES.h>
#include <string.h>
#include <Base64.h>
#include "Arduino.h"
#include "motor.h"

char password[16];
AES128 aes128;

// Wifi connection details
// TODO: Update to use separate .h file that's not in Version Control

ESP8266WebServer server(80);

typedef String (*handle_speed_t) (String arg0, String arg1);
typedef void (*setup_t)(void);
typedef struct motor_interface_t
{
    handle_speed_t handle_speed;
    setup_t setup;

}motor_interface_t;

motor_interface_t * motor;


void handleRoot() {
  // Null terminate index.html
  web_index_html[web_index_html_len] = '\0';
  String response((const char*)web_index_html);

  server.send(200, "text/html", response);
}

void handleNotFound(){
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void handleSpeed(){
  String response = "";

  if(server.args() > 1) {
    response = motor->handle_speed(server.arg(0),server.arg(1));
  }
  else {
    response = "Not enough arguments";
  }

  server.send(200, "text/plain", response.c_str());
}



void decryptWifiAuth(BlockCipher *cipher){
  Serial.println("decrypting");
  // length of array , minus the null byte
  int inputStringLength = sizeof(ciphertext) -1;

  int decodedLength = Base64.decodedLength(ciphertext, inputStringLength);

  char decodedString[decodedLength];
  Base64.decode(decodedString, ciphertext, inputStringLength);
  // symmetric decrpytion key matching the encrption key in the generate cipher
  // script
  cipher->setKey((uint8_t *)"turtlebot_3129_p", 16);
  byte buffer[16];
  uint8_t * ciphertextBytes;
  cipher->decryptBlock(buffer, (uint8_t *)decodedString);

  memcpy(password, buffer, 16);
  //need to strip spaces of the end of password
}

void setup(void){


  Serial.begin(115200);
  decryptWifiAuth(&aes128);
  //strip spaces
  motor->handle_speed = &handle_speed_implementation;
  motor->setup = &setup_implementation;
  motor->setup();
  int i = 15; //password array
  while (password[i--] == 0x20){
  }
  int password_length = i + 2; //plus 2 because post decrement....
  char password_trimmed[password_length + 1];
  memcpy(password_trimmed, password, password_length);
  password_trimmed[password_length] = '\0';
  WiFi.begin(ssid, password_trimmed);
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.on("/speed", handleSpeed);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
  delay(500);
}
