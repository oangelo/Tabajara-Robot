#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H 

#include "Arduino.h"

class Motor{
  public:
    Motor(int en, int in1, int in2);
    void Forward();
    void Backward();
    void Off();
    void SetVel(double v); //from 0 to 1
  private:
    // motor A 
    int en;
    int in1;
    int in2;
    int vel;
};

#endif /* MOTOR_CONTROL_H */
