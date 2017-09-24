#include <ESP8266WebServer.h>

const char* www_username = "admin";
const char* www_password = "admin";

ESP8266WebServer server(80);
void handlerIndex();
void sendFile(String path);

void serverSetup() {
  server.on("/", handlerIndex);
  server.begin();

  Serial.print("Server em http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void handlerIndex() {
    if(!server.authenticate(www_username, www_password))
      return server.requestAuthentication();
    sendFile("/index.html");
}

void serverLoop() {
  server.handleClient();
}

