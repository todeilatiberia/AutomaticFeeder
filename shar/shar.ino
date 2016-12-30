void setup() {
  Serial.begin(9600); 
}

void loop() {
  int valoareSenzor = readDistanceMediata(10, 0);
  Serial.print("Valoare senzor:");
  Serial.println(valoareSenzor);
  delay(100);
}

int readDistanceMediata(int count, int pin) {
  int sum = 0;
  for (int i = 0; i<count; i++) {
    float volts = analogRead(pin) * ((float) 5 / 1024);
    float distance = 65 * pow(volts, -1.10); 
    sum = sum + distance;
    delay(500);
  } 
  return (int) (sum/count);
}
