#include <Wire.h>
#include <Time.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#include <Servo.h>
#include <EEPROM.h>     
#include <SPI.h>        
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
 
Servo myservo;

boolean match = false;        
boolean programMode = false;  
boolean replaceMaster = false;

int lightSensor = 0;
int distanceSensor=1;
int pos = 0; 
int successRead; 

byte storedCard[4];  
byte readCard[4];   
byte masterCard[4];

MFRC522 mfrc522(SS_PIN, RST_PIN); 

void setup() {
  Serial.begin(9600);
  setSyncProvider(RTC.get); 
  
  myservo.attach(9);
  
  Serial.begin(9600);  // Initialize serial communications with PC
 
}



void loop() {
  
  int valueFromLightSensor = analogRead(lightSensor);
  //Serial.print("Light Value= ");
  //Serial.println(valueFromLightSensor);
  //Serial.println("");
  //Serial.print("Distance Value= ");
  int valueFromDistanceSensor = analogRead(distanceSensor);
  int distance= 4800/(valueFromDistanceSensor - 20);
  Serial.println(distance);
  //Serial.print("Hour= ");
 // Serial.println(hour());
 delay(100);
}
