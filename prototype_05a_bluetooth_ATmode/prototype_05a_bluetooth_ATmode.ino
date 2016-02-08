#include <SoftwareSerial.h>

SoftwareSerial BlueToothSerial(10, 11);

void setup()
{
  pinMode(9, OUTPUT);  
  digitalWrite(9, HIGH); // Key pin
  Serial.begin(9600);
  Serial.println("Enter AT commands:");
  BlueToothSerial.begin(38400);
}

void loop()
{
  // From BlueTooth Module to Arduino monitor
  if (BlueToothSerial.available())
    Serial.write(BlueToothSerial.read());

  // From Arduino monitor to BlueTooth Module
  if (Serial.available())
    BlueToothSerial.write(Serial.read());
} 
