
#include <EEPROM.h>


void setup() {
  for (int i = 0; i < 5; i++) {
    EEPROM.write(i, 0);
  }
  Serial.begin(9600);  
  for (int i = 0; i < 5; i++) {
    Serial.print("Registro[");
    Serial.print(i);
    Serial.print("]: ");
    Serial.println(EEPROM.read(i));
  }
}

void loop() {
  
  
}
