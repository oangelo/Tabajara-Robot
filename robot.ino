// connect motor controller pins to Arduino digital pins
// motor one

#include "./motor_control.h"
#define RESETPIN 12

byte data;
Motor motor;

void WatchUpload() {
  //From what I understand of C++ the second condition will only be evaluated if the first is true.
  if ( Serial.available() > 1 && Serial.peek() == '0')
  {
    //If we have the restart condition, we can read data from the buffer
    if ( Serial.read() == '0' && Serial.read() == ' ' )
    {
      digitalWrite(13, HIGH); //Turn on the led, so we can see if the board resets
      digitalWrite(RESETPIN, LOW);  // RESET (turn on the relay to ground the reset pin)
      digitalWrite(13, HIGH); //if reset happens this should never be executed
    }
  }
}

void CommandControl(){
  int time = 200;
  if (Serial.available()){
    data = Serial.read();
//    Serial.println((char)data);

    if(data == 'r'){
      motor.Right();
      delay(time);
      motor.Off();
    }
    if(data == 'l')
    {
      motor.Left();
      delay(time);
      motor.Off();
    }
    if(data == 's'){
      motor.Off();
    }  
    if(data == 'f'){
      motor.Foward();
      delay(time);
      motor.Off();
    }  
    if(data == 'b'){
      motor.Backward();
      delay(time);
      motor.Off();
    }  
  }  

}


void setup()
{
  digitalWrite(RESETPIN, HIGH);
  pinMode(RESETPIN, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.begin(57600); //The specific baud rate of my devices
  Serial.println("Robot Initializing!");
  motor.Off();
}

void loop()
{
  CommandControl();
  WatchUpload();
} 
