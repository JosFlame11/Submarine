#include <Arduino.h>

#include <HardwareSerial.h>

HardwareSerial RxSerial(1);
void setup() {

  Serial.begin(115200);
  RxSerial.begin(2400, SERIAL_8N1, 16, 17);
}

void loop() {
  // put your main code here, to run repeatedly:
  String received ="";

  while (RxSerial.available())
  {
    received = (char)RxSerial.read();
    Serial.println(received);
  }
  
}