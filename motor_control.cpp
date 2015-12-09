#include "motor_control.h"

Motor::Motor()
:enA(3), in1(4), in2(5), enB(9), in3(7), in4(8), velocity(255)
//:enA(10), in1(9), in2(8), enB(5), in3(7), in4(6), velocity(255)
{
  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  digitalWrite(enB, HIGH);
  digitalWrite(enA, HIGH);

}

void Motor::set_velocity(double v){
  if(v < 0){
    velocity = 0; 
  }else if (v > 1){
    velocity = 255;
  }else{
    velocity = static_cast<int>(v * 255);
  }
}

void Motor::Foward(){
  // turn on motor A
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // set speed to velocity out of possible range 0~255
//  analogWrite(enA, velocity);
  // turn on motor B
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  // set speed to velocity out of possible range 0~255
//  analogWrite(enB, velocity);

}

void Motor::Backward(){
  // this function will run the motors in both directions at a fixed speed
  // turn on motor A
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  // set speed to velocity out of possible range 0~255
//  analogWrite(enA, velocity);
  // turn on motor B
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  // set speed to velocity out of possible range 0~255
//  analogWrite(enB, velocity);
}

void Motor::Left(){
  // turn on motor A
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // set speed to velocity out of possible range 0~255
//  analogWrite(enA, velocity);
  // turn on motor B
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  // set speed to velocity out of possible range 0~255
//  analogWrite(enB, velocity);
}

void Motor::Right(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  // set speed to velocity out of possible range 0~255
//  analogWrite(enA, velocity);
  // turn on motor B
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  // set speed to velocity out of possible range 0~255
//  analogWrite(enB, velocity);
}

void Motor::Off(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
