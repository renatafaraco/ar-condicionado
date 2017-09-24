#include <IRremoteESP8266.h>
#include <MideaIR.h>

#define IR_EMITER 3
#define LED 4
#define FIVE_SECONDS    5000


// Objeto IRSend e objeto do controle remoto
IRsend irsend(IR_EMITER);
MideaIR remote_control(&irsend);


void piscaled() {
  for(int i = 0; i < 5; i++) {
    digitalWrite(LED,HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    delay(500);
  }
}

void controleSetup() {
  // Definindo pinos como output
  pinMode(IR_EMITER, OUTPUT);
  pinMode(LED, OUTPUT);
}

void controleLigar() {
  Serial.println(F("Ligando refrigerador."));
  remote_control.turnON();
  piscaled();
}

void controleDesligar() {
  Serial.println(F("Desligando refrigerador."));
  remote_control.turnOFF();
  piscaled();
}

void controleMudarTemp(int temp) {
  Serial.print(F("Temperatura configurada para "));
  Serial.print(temp);
  Serial.println(F("°C."));
  remote_control.setTemperature(temp);
  remote_control.emit();
  piscaled();
}

