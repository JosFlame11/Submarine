#include <Arduino.h>
#include <HardwareSerial.h>

HardwareSerial TxSerial(1);

void setup() {
  // put your setup code here, to run once:
  TxSerial.begin(2400, SERIAL_8N1, 16, 17);
}

void loop() {
  // put your main code here, to run repeatedly:
  TxSerial.flush();
  TxSerial.println("LIGMA");
  delay(1000);
}