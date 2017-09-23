#include <IRremoteESP8266.h>
#include <MideaIR.h>

#define IR_EMITER 3
#define LED 4
#define FIVE_SECONDS    5000

// IRsend Object and Remote Control object
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

void setup(){
  Serial.begin(9600);
  
  // Define IR PIN as Output
  pinMode(IR_EMITER, OUTPUT);
  pinMode(LED, OUTPUT);
  
  // Try to turn ON the Air Conditioner
  Serial.println(F("Trying to Turn ON the Air Conditioner..."));
  remote_control.turnON();
  piscaled();

  // Change temperature to 22
  Serial.println(F("Set temperature to 22"));
  remote_control.setTemperature(22);
  remote_control.emit();
  piscaled();

  // Change mode
  Serial.println(F("Set mode to auto"));
  remote_control.setMode(mode_auto);
  remote_control.emit();
  piscaled();
  
  // Change speed fan
  Serial.println(F("Set fan speed to 1"));
  remote_control.setSpeedFan(fan_speed_1);
  remote_control.emit();
  piscaled();

  // Try to turn OFF
  Serial.println(F("Trying to Turn OFF the Air Conditioner..."));
  remote_control.turnOFF();
  piscaled();
  

  
}

void loop(){}
