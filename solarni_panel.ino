#include <Stepper.h>
const int stepsPerRevolution = 4096;

const int maxX = stepsPerRevolution;
const int maxY = stepsPerRevolution/4;
const int stepAmount = 10;
const int errorAmount = 10;
const int fullRotationTreshold = 10;
int currentY = 0;
int currentX = 0;
//TODO polish out values

boolean runningStepper = false;
int incomingByte = 0;

//Servo1 Y
const int S11 = 2;
const int S12 = 3;
const int S13 = 4;
const int S14 = 5;
//Servo2 X
const int S21 = 6;
const int S22 = 7;
const int S23 = 8;
const int S24 = 9;

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
    }else if(incomingByte == 98){//b
      Serial.println("Stopping");
      runningStepper = false;
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
      stepY(4096);
      Serial.println("ccw");
    }else if(incomingByte == 103){//g
      stepY(-4096);
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
    
      if(currentY + stepValue > maxY){
        stepValue = maxY-currentY;
        currentY = maxY;
        stepY(stepValue);
      }else if(currentY + stepValue < 0){
        stepValue = -currentY;
        currentY = 0;
        stepY(stepValue);
      }else{
        currentY =+ stepValue;
        stepY(stepValue);
      }
    }
    
    if(Xmove != 0){
      //TODO also add max amount and rotate back using treshold value
      
      int stepValue = Xmove * stepAmount;
      if(currentX + stepValue > maxX){
        //TODO check if over threshold for rotation
        if(Xdiff > fullRotationTreshold){
          stepValue=-currentX;
          currentX=0;
          stepX(stepValue);
        }else{
          stepValue=maxX-currentX;
          currentX=maxX;
          stepX(stepValue);
        }
        
      }else if(currentX + stepValue < -maxX){
        //TODO check for threshold
        if(Xdiff < fullRotationTreshold){
          stepValue=-currentX;
          currentX=0;
          stepX(stepValue);
        }else{
          stepValue=-maxX-currentX;
          currentX=-maxX;
          stepX(stepValue);
        }
      }else{
        currentX =+ stepValue;
        stepX(stepValue);
      }
    }
  
    delay(500);
  }
}

int getYMove(int LR1V, int LR2V, int LR3V, int LR4V){
  int topAvg = (LR1V + LR2V) / 2;
  int botAvg = (LR3V + LR4V) / 2;
  int diffAvg = topAvg - botAvg;
  Serial.print("Y diff: ");
  Serial.println(diffAvg);
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

