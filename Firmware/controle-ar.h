#include <IRremoteESP8266.h>
#include <MideaIR.h>

#define IR_EMITER 3 // pino RX do nodemcu

bool controleArLigado = 0;

// Objeto IRSend e objeto do controle remoto
IRsend irsend(IR_EMITER);
MideaIR remote_control(&irsend);

void controleSetup() {
  // Definindo pinos como output
  pinMode(IR_EMITER, OUTPUT);
}

void controleLigar() {
  Serial.println(F("Ligando refrigerador."));
  remote_control.turnON();
  controleArLigado = true;
  piscaled();
}

void controleDesligar() {
  Serial.println(F("Desligando refrigerador."));
  remote_control.turnOFF();
  controleArLigado = false;
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

bool arLigado() {
  return controleArLigado;
}

