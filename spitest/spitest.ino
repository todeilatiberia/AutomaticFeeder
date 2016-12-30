#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {  0x08, 0x21, 0xEF, 0x92, 0xB6, 0x4A };

void setup() {
  Serial.begin(9600);

  // disable SD SPI
  pinMode(4,OUTPUT);
  digitalWrite(4,HIGH);

  Serial.print(F("Starting ethernet..."));
  if(!Ethernet.begin(mac)) Serial.println(F("failed"));
  else {
      Serial.println(Ethernet.localIP());
      Serial.println(Ethernet.gatewayIP());
  }
}

void loop() {
}
