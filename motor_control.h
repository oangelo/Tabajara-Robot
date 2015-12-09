#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H 

#include "Arduino.h"

class Motor{
  public:
    Motor();
    void Foward();
    void Backward();
    void Left();
    void Right();
    void Off();
    void set_velocity(double v); //from 0 to 1
  private:
    // motor one 
    int enA;
    int in1;
    int in2;
    // motor two
    int enB;
    int in3;
    int in4;
    int velocity;
};

#endif /* MOTOR_CONTROL_H */
