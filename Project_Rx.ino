/// need to Connect 11th Pin to RF Rx
#include <RH_ASK.h>
#include <SPI.h>
RH_ASK driver;
#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, A0, 10, 9, 8); // RS,E,D4,D5,D6,D7

int H,T,S,j;
char command;
String a;
String final_lat_long;

long duration;
int d;

void onBeatDetected()
{
    //Serial.println("Beat!");
}
#include <LiquidCrystal.h>

#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
//////////////////////////////////
///////////////////////////
#define REPORTING_PERIOD_MS     1000
int count=0;
int value;
PulseOximeter pox;
uint32_t tsLastReport = 0;



void setup()
{
  if (!driver.init())
  Serial.println("init failed");
  lcd.begin(16, 2); // LCD 16X2
  lcd.setCursor(0, 0);
  lcd.print("  Mine Safety   ");
  lcd.setCursor(0, 2);
  lcd.print(" Helmat System  ");

  delay(2000);
  lcd.clear();
  
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
  Serial.begin(9600); // Starts the serial communication
  if (!pox.begin()) {
    //Serial.println("FAILED");
    for(;;);
    } 
    else 
    {
        //Serial.println("SUCCESS");
    }
    pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
    pox.setOnBeatDetectedCallback(onBeatDetected);


  
}

void loop()
{

    pox.update();
  if (millis() - tsLastReport > REPORTING_PERIOD_MS)
  {   
        S=(pox.getSpO2());
        H=(pox.getHeartRate());
        tsLastReport = millis();
  }

digitalWrite(4,LOW);
  lcd.setCursor(0, 0);
  lcd.print("HR:");
  lcd.setCursor(3, 0);
    lcd.setCursor(4, 0);
  lcd.print(H); 
    
  lcd.setCursor(7, 0);
  lcd.print("BO:");
  lcd.setCursor(10, 0);
  lcd.print(S);   
  if ((S>95))//(H>70)&&
  {
  lcd.setCursor(0, 1);
  lcd.print("NR");
  }
 
  else if ((H==0)&&(S==0))
  {
    lcd.setCursor(0, 1);
    lcd.print("NF");
    }
  else if (S==0)
  {
    lcd.setCursor(0, 1);
    lcd.print("NF");
    }    
  
  else
  {
    lcd.setCursor(0, 1);
    lcd.print("AN");
   digitalWrite(4,HIGH);
    }

      Serial.print('S');
    Serial.print(S); 
    delay(5);
    
   Serial.print('H');
   Serial.print(H); 
   delay(5);


  uint8_t buf[12];
  uint8_t buflen = sizeof(buf);

  // Check if RF is connected and a message is received
  if (driver.recv(buf, &buflen)) // Non-blocking
  {

    
    int i;
    // Message with a good checksum received, dump it.
    Serial.print("Message: ");
    Serial.println((char *)buf);

    if ((buf[i] == '2'))
    {
      lcd.setCursor(14, 0);
      lcd.print("VD");

      digitalWrite(3,HIGH);     
      Serial.print('V');
      delay(10);

      
            
    }
    else if ((buf[i] == '1'))
    {
      lcd.setCursor(14, 0);
      lcd.print("VN");
      Serial.print('v');
      digitalWrite(3,LOW);
      delay(10);    
    }   
  }

  j=digitalRead(2);
  if(j==HIGH)
  {
    lcd.setCursor(3,1);
    lcd.print(" Emergency!");
    Serial.print('E');
    
    }
    else
    {
          lcd.setCursor(3,1);
    lcd.print(" Normal!      ");
      Serial.print('e');
      }

}
