#include <Arduino.h>
#include <HardwareSerial.h>

#define in1 4
#define in2 2
#define PWM1 15
#define in4 18
#define in3 5
#define PWM2 19
#define in5 22
#define in6 23

const int vel = 175;
const int freq = 2000; //the frecuency of the motor, could be up to 1000hz
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
  ledcWrite(motorChannel_A, vel);
  if (opc == 1)
  {
    foward();
  }
  else if (opc == 2)
  {
    left();
  }
  else if (opc == 3)
  {
    right();
  } 
  else if (opc == 4)
  {
    down(); 
  }
  else if (opc == 5)
  {
    up();
  }
  
  else {
    stop();
  }

}
