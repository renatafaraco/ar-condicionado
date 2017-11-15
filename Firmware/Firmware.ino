#include "sensor_temperatura.h"
#include "led.h"
#include "controle-ar.h"
#include "wifi.h"
#include "ntp.h"
#include "webserver.h"
#include "file.h"
#include "agenda.h"
#include "websocket.h"


void setup(){
  Serial.begin(9600);
  agendaSetup();
  ledSetup();
  controleSetup();
  wifiSetup();
  serverSetup();
  fileSetup();
  scanFiles();
  websocketSetup();
  sensorSetup();
  
}

void loop(){
  serverLoop();
  websocketLoop();
  ledLoop();
  agendaLoop();
}
