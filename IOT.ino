//Sujesh956@gmail.com
//Pass : sSujesh@2002

#include <Wire.h>

#define BLYNK_TEMPLATE_ID "TMPL3zH3TKJTy"
#define BLYNK_TEMPLATE_NAME "Smart Helmet"
#define BLYNK_AUTH_TOKEN "OkFwdn3J_n9lheEMlRv3vDVzKv4uf3LX"
/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "projectiot";
char pass[] = "123456789";

#define VPIN_1    V0  // Vibration
#define VPIN_2    V1  // Heart Rate
#define VPIN_3    V2  // SPO2
#define VPIN_4    V3  // Emergenecy




BLYNK_CONNECTED()
{ 

  Blynk.syncVirtual(V0);  // Vibration
  Blynk.syncVirtual(V1);  // Heart Rate
  Blynk.syncVirtual(V2);  // SPO2
  Blynk.syncVirtual(V3);  // Emergency
  
  
}




void setup()
{
  // Debug console
  Serial.begin(9600);
  delay(100);
 // sensors.begin();     
  pinMode(D5,OUTPUT); 


  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);
}

void loop()
{
  Blynk.run();
  if (Serial.available()>0) 
  {
  char a=Serial.read();
  Serial.print(a);


if(a=='V')
{  
    Blynk.virtualWrite(VPIN_1,HIGH); 
}



if(a=='v')
{  
    Blynk.virtualWrite(VPIN_1,LOW); 
}



if(a=='H')
{  
 int H=Serial.parseInt();   ///Heart Rate
    Blynk.virtualWrite(VPIN_2,H); 
}
  
 if(a=='S')
{  
 int S=Serial.parseInt(); 
    Blynk.virtualWrite(VPIN_3,S);//SPO2 
}
  
if(a=='E')//Emergency
    {  
      Blynk.virtualWrite(VPIN_4,HIGH); 
    }

if(a=='e')//Emergency
{  
  Blynk.virtualWrite(VPIN_4,LOW); 
}

}  
}
