#include <Arduino.h>

#define Ain1 2 
#define Ain2 15 
#define Bin1 16 
#define Bin2 17
//#define stby 4 conectar directamente a 5V
#define PWMA 26
#define PWMB 33

#define in5 19
#define in6 21

#define LED 32
#define Temp_pin 12
#define PH_pin 14

const int freq = 1000; //the frecuency of the motor, could be up to 1000hz
const int motorChannel_A = 0;
const int motorChannel_B = 1;
const int resolution = 8;

const int velocity = 150; //from 0 to 255

void setup() {
  pinMode(Ain1, OUTPUT);
  pinMode(Ain2, OUTPUT);
  pinMode(Bin1, OUTPUT);
  pinMode(Bin2, OUTPUT);
  ledcSetup(motorChannel_A, freq, resolution);
  ledcSetup(motorChannel_B, freq, resolution);
  ledcAttachPin(PWMA, motorChannel_A);
  ledcAttachPin(PWMB, motorChannel_B);
  //pinMode(PWMA, OUTPUT);
  //pinMode(PWMB, OUTPUT);
  pinMode(in5, OUTPUT);
  pinMode(in6, OUTPUT);
  pinMode(LED, OUTPUT);

  pinMode(Temp_pin, INPUT);
  pinMode(PH_pin, INPUT);
}

void loop() {
  //Si la antena recive 1
    //foward()
  //si recive 2
    //left()
  //si recive 3
    //right()
  //si recive 4
    //Down()
  //Si recive 5
    //UP()
  
}
void foward(void){
  ledcWrite(motorChannel_A, velocity);
  ledcWrite(motorChannel_B, velocity);
  digitalWrite(Ain1, HIGH);
  digitalWrite(Ain2, LOW);
  digitalWrite(Bin1, HIGH);
  digitalWrite(Bin2, LOW);
}
void left(void){
  ledcWrite(motorChannel_A, velocity-50);
  ledcWrite(motorChannel_B, velocity+50);
  digitalWrite(Ain1, LOW);
  digitalWrite(Ain2, HIGH);
  digitalWrite(Bin1, HIGH);
  digitalWrite(Bin2, LOW);
}
void right(void){
  ledcWrite(motorChannel_A, velocity+50);
  ledcWrite(motorChannel_B, velocity-50);
  digitalWrite(Ain1, HIGH);
  digitalWrite(Ain2, LOW);
  digitalWrite(Bin1, LOW);
  digitalWrite(Bin2, HIGH);
}
void Down(){
  digitalWrite(in5, HIGH);
  digitalWrite(in6, LOW);
}
void Up(){
  digitalWrite(in5, LOW);
  digitalWrite(in6, HIGH);
}
//Lecturas
void PH_Temp(){
  int t = analogRead(Temp_pin);
  int ph = digitalRead(PH_pin);
  int voltage = ph*(3.3 / 1023.0);
  float ph_value = -5.70 *(voltage + 21.34);
}