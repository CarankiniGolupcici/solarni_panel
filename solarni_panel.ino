#include <Stepper.h>
const int stepsPerRevolution = 4096;

const int maxX = stepsPerRevolution;
const int maxY = stepsPerRevolution/4;
const int stepAmount = 20;
const int errorAmount = 30;
const int fullRotationTreshold = 50;
int currentY = 0;
int currentX = 0;
//TODO polish out values

boolean runningStepper = false;
int incomingByte = 0;

//Servo1 Y
const int S11 = 6;
const int S12 = 7;
const int S13 = 8;
const int S14 = 9;
//Servo2 X
const int S21 = 2;
const int S22 = 3;
const int S23 = 4;
const int S24 = 5;

const int LR1 = A0;//TL
const int LR2 = A1;//TR
const int LR3 = A2;//BL
const int LR4 = A3;//BR

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Starting");
  pinMode(S11, OUTPUT);
  pinMode(S12, OUTPUT);
  pinMode(S13, OUTPUT);
  pinMode(S14, OUTPUT);

  pinMode(S21, OUTPUT);
  pinMode(S22, OUTPUT);
  pinMode(S23, OUTPUT);
  pinMode(S24, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0){
    incomingByte = Serial.read();
    if(incomingByte == 97){//a
      Serial.println("Starting");
      runningStepper = true;
      stopMotors();
    }else if(incomingByte == 98){//b
      Serial.println("Stopping");
      runningStepper = false;
      stopMotors();
    }else if(incomingByte == 99){//c
      Serial.println("Resetting");
      stepX(-currentX);
      stepY(-currentY);
      currentX = 0;
      currentY = 0;
    }else if(incomingByte == 100){//d
      stepX(stepAmount);
    }else if(incomingByte == 101){//e
      stepX(-stepAmount);
    }else if(incomingByte == 102){//f
      stepY(stepAmount);
      Serial.println("ccw");
    }else if(incomingByte == 103){//g
      stepY(-stepAmount);
      Serial.println("cw");
    }
  }

  if(runningStepper){
    int LR1V = analogRead(LR1);
    int LR2V = analogRead(LR2);
    int LR3V = analogRead(LR3);
    int LR4V = analogRead(LR4);
    int Ymove = getYMove(LR1V, LR2V, LR3V, LR4V);
    int Xdiff = getXMove(LR1V, LR2V, LR3V, LR4V);
    int Xmove = Xdiff/abs(Xdiff);


  
    if(Ymove != 0){
      int stepValue = Ymove * stepAmount;
    
      if(currentY + stepValue > 0){
        stepValue = -currentY;
      }else if(currentY + stepValue < -maxY){
        stepValue = -maxY-currentY;
      }
      currentY += stepValue;
        stepY(stepValue);
        Serial.print("Current Y: ");
        Serial.println(currentY);
        Serial.print("StepY: ");
        Serial.println(stepValue);
    }
    
    if(Xmove != 0){
      //TODO also add max amount and rotate back using treshold value
      //TODO if is too much
      int stepValue = 0;
      if(Xdiff != 0){
        stepValue = Xmove * stepAmount;
      }else{
        stepValue = 0;
      }
      //int stepValue = Xdiff != 0 ? Xmove * stepAmount : 0;
      if(currentX + stepValue > maxX){
        //TODO check if over threshold for rotation
        if(Xdiff > fullRotationTreshold){
          stepValue=-currentX;
          
        }else{
          stepValue=maxX-currentX;
        }
        
      }else if(currentX + stepValue < -maxX){
        //TODO check for threshold
        if(Xdiff < fullRotationTreshold){
          stepValue=-currentX;          
        }else{
          stepValue=-maxX-currentX;
        }
      }
        currentX += stepValue;
        //Serial.print("X move: ");
        //Serial.println(stepValue);
        stepX(stepValue);
      
    }
  
    delay(20);
  }
}

int getYMove(int LR1V, int LR2V, int LR3V, int LR4V){
  int topAvg = (LR1V + LR2V) / 2;
  int botAvg = (LR3V + LR4V) / 2;
  int diffAvg = topAvg - botAvg;
  //Serial.print("Y diff: ");
  //Serial.println(diffAvg);
  if(abs(diffAvg)>errorAmount){
    return diffAvg/abs(diffAvg);
  }else{
    return 0;
  }
}

int getXMove(int LR1V, int LR2V, int LR3V, int LR4V){
  int leftAvg = (LR1V + LR3V) / 2;
  int rightAvg = (LR2V + LR4V) / 2;
  int diffAvg = leftAvg - rightAvg;
  Serial.print("X diff: ");
  Serial.println(diffAvg);
  if(abs(diffAvg)>errorAmount){
    return diffAvg;
  }else{
    return 0;
  }
}

