#include "Adafruit_FONA.h"
#include <HardwareSerial.h>
HardwareSerial *fonaSerial = &Serial1;
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);

#define FONA_RST           13
 
#define FONA_RI_INTERRUPT  0

String teachmesomething;

Adafruit_FONA fona = Adafruit_FONA(FONA_RST);
 
void setup() {
    lcd.begin();
    lcd.setCursor(0,0);
    lcd.print("    Subscribe");
    lcd.setCursor(0,1);
    lcd.print("TeachMeSomething");
  Serial.begin(115200);
  Serial.println(F("FONA incoming call example"));
  Serial.println(F("Initializing....(May take 3 seconds)"));
  delay(3000);
   fonaSerial->begin(4800);
  if (! fona.begin(*fonaSerial)) {
    Serial.println(F("Couldn't find FONA"));
    while (1);
  }
  Serial.println(F("FONA is OK"));
 
  if(fona.callerIdNotification(true, FONA_RI_INTERRUPT)) {
    Serial.println(F("Caller id notification enabled."));
  }
  else {
    Serial.println(F("Caller id notification disabled"));
  }
  delay(1000);
}
 
void loop(){
    
    lcd.setCursor(0,0);
    lcd.print("  GSM SIM 800L ");
    lcd.setCursor(0,1);
    lcd.print("Caller ID Project"); 

  
  char phone[32] ={0};
   
  while(fona.available())
 { teachmesomething = fona.readString();
   if( teachmesomething.indexOf("CLIP") > -1)
    {Serial.println(F("RING!"));
   Serial.println(teachmesomething);
    lcd.clear();
    Serial.print("Call From: ");
    teachmesomething=teachmesomething.substring(20,30);
    Serial.println(teachmesomething);
    lcd.setCursor(0,0);
    lcd.print("Ringing !!!");
    lcd.setCursor(3,1);
    lcd.print(teachmesomething);
    delay(15000);
    Serial.print("Hangup");
    delay(1500);
    fona.println("ATH");
    lcd.clear();
    }
    }   
       
     
  }
