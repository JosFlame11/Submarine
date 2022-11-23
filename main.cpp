#include <Arduino.h>
#include <RH_ask.h>

RH_ASK rf;

void setup() {
  // put your setup code here, to run once:
rf.init();

}

void loop() {
  // put your main code here, to run repeatedly:

  const char *msg = "Ligma";
  rf.send((uint8_t*)msg, strlen(msg));
  rf.waitPacketSent();
  delay(1000);
}