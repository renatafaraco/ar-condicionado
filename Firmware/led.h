#define LED 0 // pino D3 do nodemcu
#define FIVE_SECONDS    5000

int ledControl = -1;
unsigned long tempo;


void ledSetup() {
  pinMode(LED, OUTPUT);
}

void piscaled() {
  ledControl = 2;
  tempo = millis();
}


void ledLoop() {
  if (ledControl != -1) {
    if (millis() - tempo > 500) {
      digitalWrite(LED,HIGH);
    }
    if (millis() - tempo > 1000) {
      digitalWrite(LED,LOW);
      tempo = millis();
      ledControl--;  
    }
  }
}

