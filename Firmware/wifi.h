#include <ESP8266WiFi.h>

//Login e senha da rede wifi - alterar depois para pegar configuração
//de arquivo
const char* ssid = "FAVERI";
const char* password = "05061983";

void wifiSetup() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if(WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Falhou ao conectar! Reiniciando...");
    delay(1000);
    ESP.restart();
  }
  WiFi.hostname(F("refrigerador"));
}

