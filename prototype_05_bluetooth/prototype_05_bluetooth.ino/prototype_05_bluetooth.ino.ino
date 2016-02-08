void setup() {
  Serial.begin(38400);
  pinMode(2, OUTPUT);
}

void loop() {
  if(Serial.available()) {
    while(Serial.available()) {
      char x = (char)Serial.read();
      Serial.println(x);
      Serial.flush();
      
      if(x == 'a') {
        digitalWrite(2, HIGH);
      }
      else if (x == 'b') {
        digitalWrite(2, LOW);
      }
    }
  }
}
