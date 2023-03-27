//variables for LORA module: tranceiver part for submarine
//pins to connect:
/*
DIO0 = 
rst = 
NSS = 
SCK = 
MOSI  = GPIO23 or 23
MISO = GPIO19 or 19
just one gnd pin to GND
Create an annthena and solder it to the ANN pin

*/
#include <SPI.h>
#include <LoRa.h>

#define ss = 5
#define rst = 14
#define dio0 = 2


void setup() {
  Serial.begin (9600);
  while (!Serial);
  Serial.println("LoRa Tranceiver");
  LoRa.setPins(ss, rst, dio0);

  while (!LoRa.begin(915E6)){
    Serial.println(".");
    delay(500);
  }

  LoRa.setSyncWord(0xFA);
  Serial.println("LoRa initiallized");

}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize){
    Serial.print("Received packet ");

    while (LoRa.available()) {
      String LoRaData = LoRa.readString();
      Serial.print(LoRaData);
    }
    
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());

  }

}
