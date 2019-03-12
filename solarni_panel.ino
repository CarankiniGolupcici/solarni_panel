#include <Stepper.h>
const int stepsPerRevolution = 200;

const int maxX = stepsPerRevolution;
const int maxY = stepsPerRevolution/4;
const int stepAmount = 10;
const int errorAmount = 10;
int currentY = 0;
int currentX = 0;
//TODO polish out values

boolean runningStepper = false;
int incomingByte = 0;
Stepper xStepper(stepsPerRevolution, 2,3, 4, 5);
Stepper yStepper(stepsPerRevolution, 6, 7, 8, 9);
const int LR1 = A0;//TL
const int LR2 = A1;//TR
const int LR3 = A2;//BL
const int LR4 = A3;//BR

void setup() {
  // put your setup code here, to run once:
  xStepper.setSpeed(60);
  yStepper.setSpeed(60);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    incomingByte = Serial.read();
    //TODO
  }
  
  int LR1V = analogRead(LR1);
  int LR2V = analogRead(LR2);
  int LR3V = analogRead(LR3);
  int LR4V = analogRead(LR4);
  int Ymove = getYMove(LR1V, LR2V, LR3V, LR4V);
  int Xmove = getXMove(LR1V, LR2V, LR3V, LR4V);
  
  if(Ymove != 0){
    int stepValue = Ymove * stepAmount;
  
    if(currentY + stepValue > maxY){
      stepValue = maxY-currentY;
      currentY = maxY;
      yStepper.step(stepValue);
    }else if(currentY + stepValue < -maxY){
      stepValue = -maxY - currentY;
      currentY = -maxY;
      yStepper.step(stepValue);
    }else{
      currentY =+ stepValue;
      yStepper.step(stepValue);
    }
  }
  
  if(Xmove != 0){
    xStepper.step(Xmove * stepAmount);
  }

  delay(500);
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
    return diffAvg/abs(diffAvg);
  }else{
    return 0;
  }
}

