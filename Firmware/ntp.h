#include <NTPClient.h>
#include <WiFiUdp.h>

WiFiUDP ntpUDP;
int16_t utc = -3; //UTC -3:00 Brazil
NTPClient timeClient(ntpUDP, "a.st1.ntp.br", utc*3600, 60000);


void ntpSetup() {
  timeClient.begin();
  timeClient.update();
}

unsigned long checkNTP() {
  Serial.print("Formato gregoriano");
  Serial.println(timeClient.getFormattedTime());
  return timeClient.getEpochTime();
}

