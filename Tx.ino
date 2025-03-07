const int vibrationPin = A5;  // Analog pin for the vibration sensor
const int thresholdValue = 100;  // Adjust this threshold value according to your needs
int currentValue = 0;
char SendIOT;

#include <RH_ASK.h>
#include <SPI.h>
RH_ASK driver;
int m,n,o;
char command;

void setup() {
   if (!driver.init())
  Serial.println("init failed");

  Serial.begin(9600);  // Initialize serial communication for debugging
  pinMode(7,OUTPUT);
}

void loop() {

  int vibrationValue = analogRead(vibrationPin);
  //Serial.print('a');
  //Serial.println(vibrationValue);
  // Check if the vibration value is above the threshold
  if (vibrationValue >= thresholdValue) {
    // If above threshold, hold the value
    currentValue = vibrationValue;
    
    
  }
  if (currentValue<100)
  {
    SendIOT ='a';
  digitalWrite(7,HIGH);
    digitalWrite(7,HIGH);
  const char *msg = "1";
  driver.send((uint8_t *)msg, strlen(msg));
  driver.waitPacketSent();
     delay(1000);



  
    }
    else
    {
      SendIOT ='A';
    digitalWrite(7,LOW);
  digitalWrite(7,HIGH);
  const char *msg = "2";
  driver.send((uint8_t *)msg, strlen(msg));
  driver.waitPacketSent();
     delay(1000);

    
      }

  // Use currentValue for further processing or send it to other modules
  //Serial.print("CurrentValue:");
  Serial.println(currentValue);  // Print the value for debugging purposes
  Serial.print(SendIOT);
  // Add a delay to control the rate of reading the sensor
  delay(100);  // Adjust the delay based on your application's needs
}
