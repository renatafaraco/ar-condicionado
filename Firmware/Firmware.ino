#include "controle-ar.h"
#include "wifi.h"
#include "webserver.h"
#include "file.h"
#include "websocket.h"

void setup(){
  Serial.begin(9600);
  controleSetup();
  wifiSetup();
  serverSetup();
  fileSetup();
  scanFiles();
  websocketSetup();
  
}

void loop(){
  serverLoop();
  websocketLoop();
}
