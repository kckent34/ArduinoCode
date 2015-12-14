// Motor driver code 

#include "MotorDriver.h"

int inputPin = 7; // pushbutton connected to digital pin 7 
int analogPin = 0;
float val = 0;
float valPrev = 0;
int dispense = 0;
float thresh = 33.0;

void setup()
{
  motordriver.init();
  motordriver.setSpeed(600,MOTORB);
  motordriver.setSpeed(600,MOTORA);
  pinMode(inputPin, INPUT);
  thresh = analogRead(analogPin);
  Serial.begin(9600);
}
  
  
void loop()
{
  val = analogRead(analogPin); // update sensor reading
  Serial.println(val); 
    Serial.print("thresh: ");
    Serial.println(thresh);
  // if button is pressed 
  if(digitalRead(inputPin) == HIGH) { 
    while(val < thresh+10.0) {
    val = analogRead(analogPin); // update sensor reading 
    motordriver.goForward(); //move motor forward 
    Serial.println("Im in here");
    }
    dispense = 1;  
  }
  
  //while pack is covering sensor 
  while(dispense == 1) {
    val = analogRead(analogPin); // update sensor reading 
    Serial.println(val);
    
    // if pack is covering sensor 
    if( val > thresh){
      motordriver.goForward(); //move motor forward 
    }
    //if pack is dispensed val should be less than thresh 
    else{ 
      motordriver.stop(); // stop the motor 
      dispense = 0; // no longer dispensing 
      Serial.println("Pack Dispensed!");
    }
    
  }
 
  
  
}

