#include <EEPROM.h>    
#include <SPI.h>        
#include <MFRC522.h>	

		
boolean match = false;          
boolean programMode = false;	


int isOurPet;		

byte storedCard[4];		
byte readCard[4];		
byte masterCard[4];		

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);	



void setup() {
  Serial.begin(9600);	 
  SPI.begin();          
  mfrc522.PCD_Init();   
  if (EEPROM.read(1) != 143) {
    
    do {
      isOurPet = findOurPet();            
     
    }
    while (!isOurPet);                 
    for ( int j = 0; j < 4; j++ ) {        
      EEPROM.write( 2 + j, readCard[j] );  
    }
    EEPROM.write(1, 143);                  
   
  }

  for ( int i = 0; i < 4; i++ ) {          
    masterCard[i] = EEPROM.read(2 + i);   
    
  }
}


void loop () {
  do {
    isOurPet = findOurPet(); 	
 }
  while (!isOurPet); 	
  if ( master(readCard)) {  	
      programMode = true;
      Serial.println(F("Our Pet - Red Tag"));
      int count = EEPROM.read(0); 	
     
    }
    else {			
        Serial.println(F("Not our pet - Blue Tag"));
        
      }
    }

int findOurPet() {

  if ( ! mfrc522.PICC_IsNewCardPresent()) { 
    return 0;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {  
    return 0;
  }
  for (int i = 0; i < 4; i++) {  
    readCard[i] = mfrc522.uid.uidByte[i];
 }
 
  mfrc522.PICC_HaltA(); // Stop reading
  return 1;
}

void readCollar( int number ) {
  int start = (number * 4 ) + 2; 		
  for ( int i = 0; i < 4; i++ ) { 		
    storedCard[i] = EEPROM.read(start + i); 	
  }
}

boolean EEpromCheck ( byte a[], byte b[] ) {
  if ( a[0] != NULL ) 			
    match = true; 			
  for ( int k = 0; k < 4; k++ ) { 	
    if ( a[k] != b[k] ) 		
      match = false;
  }
  if ( match ) { 			
    return true; 			
  }
  else  {
    return false; 			
  }
}

boolean master( byte test[] ) {
  if ( EEpromCheck( test, masterCard ) )
    return true;
  else
    return false;
}
