// connect motor controller pins to Arduino digital pins
// motor one

#include "./motor_control.h"
#include "GY_85.h"
#include <Wire.h>


#define RESETPIN 12

byte data;
Motor motor_a(3, 4, 5);
Motor motor_b(9, 7, 8);
unsigned long real_time;
GY_85 GY85;
int timer_motor, timer;
bool flag;


void WatchUpload() {
  //From what I understand of C++ the second condition will only be evaluated if the first is true.
  if ( Serial.available() > 1 && Serial.peek() == '0')
  {
    //If we have the restart condition, we can read data from the buffer
    if ( Serial.read() == '0' && Serial.read() == ' ' )
    {
      Serial.flush();
      digitalWrite(13, HIGH); //Turn on the led, so we can see if the board resets
      digitalWrite(RESETPIN, LOW);  // RESET (turn on the relay to ground the reset pin)
      digitalWrite(13, HIGH); //if reset happens this should never be executed
    }
  }
}

void CommandControl(int& time_motor, bool& flag){
  if (Serial.available() and Serial.peek() != '0'){
    data = Serial.read();
//    Serial.println((char)data);

    if(data == 'v'){
      float v(Serial.parseFloat());
      motor_a.SetVel(v);
      motor_b.SetVel(v);
      Serial.println(v);
    }

    if(data == 'r'){
      float threshold(3);
      float kp(1.0/100.0);
      float ki(1.0/1.0);
      float kd(6.0/1.0);
      float f_angle(Serial.parseFloat());
      float i_angle(GY85.AngleGyroDegreeX()); 
      Serial.print("f_angle ");
      Serial.println(f_angle);
      Serial.print("i_angle ");
      Serial.println(i_angle);
      float v(0.75);
      float theta(GY85.AngleGyroDegreeX() - i_angle);
      float error(f_angle - theta);
      float old_error(error);
      Serial.print("error ");
      Serial.println(fabs(error));
      float sum = 0;
      unsigned flag(0);
      while(fabs(error) > threshold or flag < 100){
        theta = GY85.AngleGyroDegreeX() - i_angle;
        old_error = error;
        error = f_angle - theta;
        sum += error;
        if(sum > 1.0){
          sum = 1.0;
        }else if (sum < -1.0){
          sum = -1.0;
        }
        float delta_error = old_error - error;
        v = kp*error + ki*sum + kd*delta_error; //PID
        if(v > 1 or v < -1)
          v = 1;
        motor_a.SetVel(fabs(v*0.96));
        motor_b.SetVel(fabs(v*0.96));
        if(theta < f_angle){
          Serial.print("right ");
          motor_b.Forward();
          motor_a.Backward();
        }else{
          Serial.print("left ");
          motor_a.Forward();
          motor_b.Backward();
        }
        delay(2);
        Serial.print(" delta_error: ");
        Serial.print(kd*delta_error);
        Serial.print(" sum error: ");
        Serial.print(ki*sum);
        Serial.print(" error: ");
        Serial.print(kp*error);
        Serial.print(" vel: ");
        Serial.println(v);
        if(fabs(error) < threshold)
          ++flag;
      }
      motor_a.Off();
      motor_b.Off();
    }

    if(data == 'f'){
      float threshold(3);
      float kp(1.0/100.0);
      float ki(1.0/10000.0);
      float f_angle(0);
      float i_angle(GY85.AngleGyroDegreeX()); 
      Serial.print("f_angle ");
      Serial.println(f_angle);
      Serial.print("i_angle ");
      Serial.println(i_angle);
      float v(0.85);
      float theta(GY85.AngleGyroDegreeX() - i_angle);
      float error(f_angle - theta);
      Serial.print("error ");
      Serial.println(fabs(error));
      float sum = 0;
      unsigned flag(0);
      motor_b.Forward();
      motor_a.Forward();
      while(flag < 1000){
        sum += error;
        v = kp*fabs(error)+ki*sum;
        if(theta < f_angle + threshold / 2.0){
          Serial.print("right ");
          motor_b.SetVel(fabs(0.85+v));
          motor_a.SetVel(fabs(0.85-v));
        }else{
          Serial.print("left ");
          motor_b.SetVel(fabs(0.85+v));
          motor_a.SetVel(fabs(0.85-v));
        }
        delay(2);
        theta = GY85.AngleGyroDegreeX() - i_angle;
        error = f_angle - theta;
        Serial.print("error: ");
        Serial.print(fabs(error));
        Serial.print(" vel: ");
        Serial.println(v);
        ++flag;
      }
      motor_a.Off();
      motor_b.Off();
    }

    motor_a.SetVel(1);
    motor_b.SetVel(1);


    if(data == 's'){
      motor_a.Off();
      motor_b.Off();
      flag = true;
    }  

    if(data == 'b'){
      motor_a.Backward();
      motor_b.Backward();
      flag = true;
    }  
    if(data == 'l'){
      motor_a.Forward();
      motor_b.Backward();
      flag = true;
    }  
//    if(data == 'r'){
//      motor_b.Forward();
//      motor_a.Backward();
//      flag = true;
//    }  

    if(time_motor > 1000){
      flag = false;
      time_motor = 0;
      motor_a.Off();
      motor_b.Off();
    }
  }  
}


void setup()
{
  digitalWrite(RESETPIN, HIGH);
  pinMode(RESETPIN, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.begin(57600); //The specific baud rate of my devices
  Wire.begin();
  GY85.init();
  motor_a.Off();
  motor_b.Off();
  timer_motor = 0;
  timer = 0;
  flag = false;
  delay(2);
  Serial.println("Robot Initializing!");
}

void loop()
{
  WatchUpload();
  ++timer;
  if(flag){
    ++timer_motor;
  }


//  if(timer == 10000){
//    Serial.println(GY85.AngleGyroDegreeX());
//  }
  CommandControl(timer_motor, flag);

} 
