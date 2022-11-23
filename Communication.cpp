#include <Arduino.h>
#include <RH_ask.h>
#include <HardwareSerial.h>

RH_ASK rf;
HardwareSerial TxSerial(1);

void setup() {
  // put your setup code here, to run once:
rf.init();
  TxSerial.begin(2400, SERIAL_8N1, 16, 17);
}

void loop() {
  // put your main code here, to run repeatedly:

  const char *msg = "Ligma";
  rf.send((uint8_t*)msg, strlen(msg));
  rf.waitPacketSent();
  delay(1000);
}