#include <Wire.h>  //INCLUSÃO DE BIBLIOTECA
#include <LiquidCrystal_I2C.h> //INCLUSÃO DE BIBLIOTECA
 
LiquidCrystal_I2C lcd(0x3F, 16, 2);//FUNÇÃO DO TIPO "LiquidCrystal_I2C"


void lcdSetup() {
  lcd.init();   
  lcd.backlight();
  lcd.setCursor(0, 0); 
  lcd.print("Iniciando..."); 
  Serial.println("Iniciando LCD");
  lcd.setCursor(0, 1);    
  lcd.print("Opa laloe!"); 
}

void lcdLoop() {
  
}

