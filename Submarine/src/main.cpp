#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>


//LoRa constants
const long frequency = 915E6;
const int ss = 5;
const int rst = 25;
const int dio0 = 26;

//Motors
#define in1 16
#define in2 17
#define PWM1 3
#define in4 2
#define in3 4
#define PWM2 15

//Void motor
#define in5 32
#define in6 33

//Sensors
#define Sensor1 12
#define Sensor2 13
#define Sensor3 26
#define Sensor4 27
#define Sensor5 34
#define Sensor6 35
#define Sensor7 36
#define Sensor8 39


//init PWM for motors
const int vel = 175;
const int freq = 1000; //the frecuency of the motor, could be up to 1000hz
const int motorChannel_A = 0;
const int resolution = 8;

//init timers
uint32_t SensorReadInitMillis;
uint32_t SensorReadCurrentMillis;
const uint32_t SensorReadInterval = 500UL;

uint32_t ReceiverInitMillis;
uint32_t ReceiverCurrentMillis;
const uint32_t ReceiverInterval = 100UL;

uint32_t SendDataInitMillis;
uint32_t SendDataCurrentMillis;
const uint32_t SendDataInterval = 5000UL;

//Sensor Read Changes

uint16_t CurrentSensor1Read = 0;
u_int16_t NewSensor1Read;

uint16_t CurrentSensor2Read = 0;
u_int16_t NewSensor2Read;

uint16_t CurrentSensor3Read = 0;
u_int16_t NewSensor3Read;

uint16_t CurrentSensor4Read = 0;
u_int16_t NewSensor4Read;

uint16_t CurrentSensor5Read = 0;
u_int16_t NewSensor5Read;

uint16_t CurrentSensor6Read = 0;
u_int16_t NewSensor6Read;

uint16_t CurrentSensor7Read = 0;
u_int16_t NewSensor7Read;

uint16_t CurrentSensor8Read = 0;
u_int16_t NewSensor8Read;

void LoRaSendData(String Data){
  LoRa.disableInvertIQ();
  LoRa.beginPacket();
  LoRa.print(Data);
  LoRa.endPacket();
}

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
int movement = 5;

void setup() {
  SensorReadInitMillis = millis();
  SendDataInitMillis = millis();
  ReceiverInitMillis = millis();
  Serial.begin(115200); //For debugging

  /*init LoRa pins
  //LoRa.setPins(ss, rst, dio0);
  //if (!LoRa.begin(frequency)){
    Serial.println("LoRa init failed. Check connections.");
    while(true);
  }
  Serial.println("LoRa initialize correctly");
*/
  //Make motors as ouputs
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(in5, OUTPUT);
  pinMode(in6, OUTPUT);

  //Make Sensors as inputs
  pinMode(Sensor1, INPUT);
  pinMode(Sensor2, INPUT);
  pinMode(Sensor3, INPUT);
  pinMode(Sensor4, INPUT);
  pinMode(Sensor5, INPUT);
  pinMode(Sensor6, INPUT);
  pinMode(Sensor7, INPUT);
  pinMode(Sensor8, INPUT);
  
  ledcSetup(motorChannel_A, freq, resolution);
  ledcAttachPin(PWM1, motorChannel_A);
  ledcAttachPin(PWM2, motorChannel_A);

}

void loop() {
  ledcWrite(motorChannel_A, vel);
 /* 
  int packetSize = LoRa.parsePacket();
  if (packetSize){
    while (LoRa.available()) {
      movement = LoRa.read();
      Serial.print(movement);
    }
  }*/

//It would move depedending the value that thee controller receives

  if (movement != 0){
    if (movement == 1){
      Serial.println("1");
      foward();
    }
    else if (movement == 2){
      left();
      Serial.println("2");
    }
    else if (movement == 3){
      right();
      Serial.println("3");
    }
    else if (movement == 4){
      up();
    }
    else if (movement == 5){
      down();
    }
  }
  else{
    stop();
  }


  SensorReadCurrentMillis = millis();
  if (SensorReadCurrentMillis - SensorReadInitMillis >= SensorReadInterval){
    NewSensor1Read = (float)analogRead(Sensor1)/4095 * 3.3;
    NewSensor2Read = (float)analogRead(Sensor2)/4095 * 3.3;
    NewSensor3Read = (float)analogRead(Sensor3)/4095 * 3.3;
    NewSensor4Read = (float)analogRead(Sensor4)/4095 * 3.3;
    NewSensor5Read = (float)analogRead(Sensor5)/4095 * 3.3;
    NewSensor6Read = (float)analogRead(Sensor6)/4095 * 3.3;
    NewSensor7Read = (float)analogRead(Sensor7)/4095 * 3.3;
    NewSensor8Read = (float)analogRead(Sensor8)/4095 * 3.3;

    if (NewSensor1Read > CurrentSensor1Read + 1 || NewSensor1Read < CurrentSensor1Read -1){
      LoRaSendData("A#" + (NewSensor1Read));
      CurrentSensor1Read = NewSensor1Read;
    }
    if (NewSensor2Read > CurrentSensor2Read + 1 || NewSensor2Read < CurrentSensor2Read -1){
      LoRaSendData("B#" + (NewSensor2Read));
      CurrentSensor2Read = NewSensor2Read;
    }
    if (NewSensor3Read > CurrentSensor3Read + 1 || NewSensor3Read < CurrentSensor3Read -1){
      LoRaSendData("C#" + (NewSensor3Read));
      CurrentSensor3Read = NewSensor3Read;
    }
    if (NewSensor4Read > CurrentSensor4Read + 1 || NewSensor4Read < CurrentSensor4Read -1){
      LoRaSendData("D#" + (NewSensor4Read));
      CurrentSensor4Read = NewSensor4Read;
    }
    if (NewSensor5Read > CurrentSensor5Read + 1 || NewSensor5Read < CurrentSensor5Read -1){
      LoRaSendData("E#" + (NewSensor5Read));
      CurrentSensor5Read = NewSensor5Read;
    }
    if (NewSensor6Read > CurrentSensor6Read + 1 || NewSensor6Read < CurrentSensor6Read -1){
      LoRaSendData("F#" + (NewSensor6Read));
      CurrentSensor6Read = NewSensor6Read;
    }
    if (NewSensor7Read > CurrentSensor7Read + 1 || NewSensor7Read < CurrentSensor7Read -1){
      LoRaSendData("G#" + (NewSensor7Read));
      CurrentSensor7Read = NewSensor7Read;
    }
    if (NewSensor8Read > CurrentSensor8Read + 1 || NewSensor8Read < CurrentSensor8Read -1){
      LoRaSendData("H#" + (NewSensor8Read));
      CurrentSensor8Read = NewSensor8Read;
    }
    
  }

}
/*void onReceive(int PacketSize){
  String message = "";
  while (LoRa.available()){
    message += (char)LoRa.read();
  }
  Serial.println(message);
}*/
