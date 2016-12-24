#include <Time.h> 
#include <Wire.h> 
#include <DS1307RTC.h> 

void setup()  {
  Serial.begin(9600);
  setSyncProvider(RTC.get);   // the function to get the time from the RTC
 }

void loop()
{
   hourDisplay(); 
   delay(1000);
}

void hourDisplay(){
  Serial.println(hour());
}


