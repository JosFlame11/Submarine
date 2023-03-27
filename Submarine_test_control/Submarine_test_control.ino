
#include <SPI.h>
#include <LoRa.h>

#define in1 4
#define in2 2 //cambiar
#define PWM1 15
#define in4 18
#define in3 5
#define PWM2 19 //cambiar pin
#define in5 22
#define in6 23//cambiar pin

#define ss 5
#define rst 14
#define dio0 2

const int vel = 175;
const int freq = 1000; //the frecuency of the motor, could be up to 1000hz
const int motorChannel_A = 0;

const int resolution = 8;

int opc = 1;
void foward(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
void left(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
void right(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
void stop(){
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  digitalWrite(in5, LOW);
  digitalWrite(in6, LOW);
}
void up(){
  digitalWrite(in5, HIGH);
  digitalWrite(in6, LOW);
}

void down(){
  digitalWrite(in5, LOW);
  digitalWrite(in6, HIGH);
}
void setup() {
Serial.begin(115200);

  while (!Serial);
  Serial.println("LoRa Sender");

  //setup LoRa transceiver module
  LoRa.setPins(ss, rst, dio0);
  
  //replace the LoRa.begin(---E-) argument with your location's frequency 
  //433E6 for Asia
  //866E6 for Europe
  //915E6 for North America
  while (!LoRa.begin(915E6)) {
    Serial.println(".");
    delay(500);
  }
   // Change sync word (0xF3) to match the receiver
  // The sync word assures you don't get LoRa messages from other LoRa transceivers
  // ranges from 0-0xFF
  LoRa.setSyncWord(0xFA);
  Serial.println("LoRa Initializing OK!");


  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(in5, OUTPUT);
  pinMode(in6, OUTPUT);
  
  ledcSetup(motorChannel_A, freq, resolution);
  ledcAttachPin(PWM1, motorChannel_A);
  ledcAttachPin(PWM2, motorChannel_A);

}

void loop() {

  int packetSize = LoRa.parsePacket();
  if (packetSize){
    
    while (LoRa.available()) {
      String LoRaData = LoRa.readString();
      Serial.print(LoRaData);
    }
  }
  ledcWrite(motorChannel_A, vel);
  if (LoRaData == "1")
  {
    foward();
  }
  else if (opc == "2")
  {
    left();
  }
  else if (opc == "3")
  {
    right();
  } 
  else if (opc == "4")
  {
    down(); 
  }
  else if (opc == "5")
  {
    up();
  }
  
  else {
    stop();
  }

}
