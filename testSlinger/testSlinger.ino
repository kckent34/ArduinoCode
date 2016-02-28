// This is currently the code to dispense a blister pack with a digital input from
// a push button 

#include "MotorDriver.h"

int inputPin = 7; // pushbutton connected to digital pin 7 
int frontSensorPin = 0;
int backSensorPin = 2;
float valBack = 0;
float valFront = 0;
float valPrev = 0;
int dispense = 0;
float threshFront = 33.0;
float threshBack = 33.0;
int frontFlag = 0;

void setup()
{
  motordriver.init();
  motordriver.setSpeed(200,MOTORB);
  motordriver.setSpeed(75,MOTORA);
  pinMode(inputPin, INPUT);
  threshFront = analogRead(frontSensorPin);
  threshBack = analogRead(backSensorPin);
  Serial.begin(9600);
}
  
  
void loop()
{
//  Serial.print("thresh back:   ");
//  Serial.println(threshBack);
//  valBack = analogRead(backSensorPin);
//   Serial.print("sensor back:    ");
//   Serial.println(valBack);
   
//   valFront = analogRead(frontSensorPin);
//   Serial.print("sensor front:    ");
//   Serial.println(valFront);
   

  valBack = analogRead(backSensorPin);
  // if button is pressed 
  if(digitalRead(inputPin) == HIGH) { 
    while(valBack < threshBack+100.0) {
    valBack = analogRead(backSensorPin); // update back sensor reading
    Serial.println(valBack);
    motordriver.rotateWithID(0,MOTORB); //move back motor
    Serial.println("Im in here");
    }
    motordriver.rotateWithID(1,MOTORA);
    delay(300);
    motordriver.stop();
    dispense = 1;  
  }
  
  //while pack is covering sensor 
  if(dispense == 1) {
    Serial.println("moving front motor");
    valFront = analogRead(frontSensorPin); // update sensor reading 
    Serial.println(valFront);
    
    while(valFront < threshFront+50.0)
    {
      valFront = analogRead(frontSensorPin);
      motordriver.rotateWithID(1,MOTORA);
      Serial.println("Going until front sensor covered");
    }
    
    while(valFront > threshFront+20.0)
    {
      valFront = analogRead(frontSensorPin);
      Serial.println("Front sensor covered, moving until not covered");
      motordriver.rotateWithID(1,MOTORA);
    }
    motordriver.stop();
    dispense = 0;
    Serial.println("Dispensed a pack!");
 
    
  }
 
  
  
}

