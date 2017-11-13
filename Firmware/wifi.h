#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>

//Login e senha da rede wifi - alterar depois para pegar configuração
//de arquivo
const char* ssid = "FAVERI";
const char* password = "05061983";
const char* hostname1 = "REFRIGERADOR";

void wifiSetup() {
  
  WiFi.mode(WIFI_STA);
  if (WiFi.hostname(hostname1) == true) {
    Serial.println("Hostname succsess");
  }
  WiFi.begin(ssid, password);
  
  if(WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Falhou ao conectar! Reiniciando...");
    delay(1000);
    ESP.restart();
  }
  Serial.print("Hostname: ");
  Serial.println(WiFi.hostname().c_str());
}

