#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>

//define X and Y for the joystick
#define POTX 26
#define POTY 27

//define Button 1 and 2
#define btn1 32
#define btn2 33

const int ss = 5;
const int rst = 25;
const int di0 = 2;

const long frequency = 915E6;

//timer for send data
uint32_t DataSendInitMillis;
uint32_t DataSendCurrentMillis;
uint32_t DataInverval = 100UL;

//POT values
uint16_t XValue = 0;
uint16_t NewXValue;

uint16_t YValue = 0;
uint16_t NewYValue;

int opc = 0;
void Buttons();

void setup() {
  Serial.begin(115200); // For debugging
  
  //init timer
  DataSendInitMillis = millis();

  //Set buttons as inputs with a pullup resistance
  pinMode(btn1, PULLUP);
  pinMode(btn2, PULLUP);

  //set joystick as input
  pinMode(POTX, INPUT);
  pinMode(POTY, INPUT);

  pinMode(ss, OUTPUT);

  //init LoRa pins
  LoRa.setPins(ss, rst, di0);

  //init LoRa module
  while (!LoRa.begin(frequency)){
    Serial.println("LoRa init failed. Check connection");
    delay(500);
  }
  Serial.println("LoRa initialize correctly");
}

void loop() {
  
  NewXValue = (float)analogRead(POTX)/4095 * 30;
  if (NewXValue > XValue + 1 || NewXValue < XValue - 1){
    XValue = NewXValue;
    Serial.println(XValue);
  }
  NewYValue = (float)analogRead(POTY)/4095 * 30;
  if (NewYValue > YValue + 1 || NewYValue < YValue - 1){
    YValue = NewYValue;
    Serial.println(YValue);
  }
  if (YValue >= 15 && YValue <= 30){
    opc = 1;
  }
  else if (XValue > 15 && YValue <= 30){
    opc = 2;
  }
  else if (XValue >= 0 && XValue <= 15){
    opc = 3;
  }
  else{
    Buttons();
  }
  Serial.println(opc);
}//establecer una funciona que diga, cuando Xpot esta en estos valores, devolver 2 o 3
  //Si Ypot tiene estos valores devolver 1 o 0
  //Crear funciones para los botones, si btn1 es high, devolver 4; si btn2 es high, devolver 5.
  //que btn1 y btn2 no puedan ser presionados a la misma vez.

void LoRaSendData(int Data){
  LoRa.disableInvertIQ();
  LoRa.beginPacket();
  LoRa.print(Data);
  LoRa.endPacket();
}
void Buttons(){
  if (btn1 == HIGH && btn2 == LOW){
    opc = 4;
  }
  else if (btn1 == LOW && btn2 == HIGH){
    opc = 5;
  }
}