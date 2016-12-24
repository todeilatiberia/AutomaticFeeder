#include <Time.h> 
#include <Wire.h> 
#include <DS1307RTC.h> 

int lightSensor = 0;
int distanceSensor=1;


void setup() {
  Serial.begin(9600);
  setSyncProvider(RTC.get);
}



void loop() {
  int valueFromLightSensor = analogRead(lightSensor);
  Serial.print("Light Value= ");
  Serial.print(valueFromLightSensor);
  Serial.println("");
  Serial.print("Distance Value= ");
  int valueFromDistanceSensor = analogRead(distanceSensor);
  int distance= 4800/(valueFromDistanceSensor - 20);
  Serial.println(distance);
  
  delay(1000);
  
  Serial.print("Hour= ");
  Serial.println(hour());
  
}
