#include "motor_control.h"

Motor::Motor(int en, int in1, int in2)
:en(en), in1(in1), in2(in2), vel(255)
{
  // set all the motor control pins to outputs
  pinMode(en, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  digitalWrite(en, HIGH);
}

void Motor::SetVel(double v){
  if(v < 0){
    vel= 0; 
  }else if (v > 1){
    vel= 255;
  }else{
    vel = static_cast<int>(v * 255);
  }
  analogWrite(en, vel);
}


void Motor::Forward(){
  // turn on motor A
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
}

void Motor::Backward(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
}

void Motor::Off(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
}
