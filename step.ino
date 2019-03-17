int StepsY = 0;
void stepY(int xw){
  boolean Direction = xw>0;
  xw = abs(xw);
  for (int x=0;x<xw;x++){
switch(StepsY){
   case 0:
     digitalWrite(S11, LOW); 
     digitalWrite(S12, LOW);
     digitalWrite(S13, LOW);
     digitalWrite(S14, HIGH);
   break; 
   case 1:
     digitalWrite(S11, LOW); 
     digitalWrite(S12, LOW);
     digitalWrite(S13, HIGH);
     digitalWrite(S14, HIGH);
   break; 
   case 2:
     digitalWrite(S11, LOW); 
     digitalWrite(S12, LOW);
     digitalWrite(S13, HIGH);
     digitalWrite(S14, LOW);
   break; 
   case 3:
     digitalWrite(S11, LOW); 
     digitalWrite(S12, HIGH);
     digitalWrite(S13, HIGH);
     digitalWrite(S14, LOW);
   break; 
   case 4:
     digitalWrite(S11, LOW); 
     digitalWrite(S12, HIGH);
     digitalWrite(S13, LOW);
     digitalWrite(S14, LOW);
   break; 
   case 5:
     digitalWrite(S11, HIGH); 
     digitalWrite(S12, HIGH);
     digitalWrite(S13, LOW);
     digitalWrite(S14, LOW);
   break; 
     case 6:
     digitalWrite(S11, HIGH); 
     digitalWrite(S12, LOW);
     digitalWrite(S13, LOW);
     digitalWrite(S14, LOW);
   break; 
   case 7:
     digitalWrite(S11, HIGH); 
     digitalWrite(S12, LOW);
     digitalWrite(S13, LOW);
     digitalWrite(S14, HIGH);
   break; 
   default:
     digitalWrite(S11, LOW); 
     digitalWrite(S12, LOW);
     digitalWrite(S13, LOW);
     digitalWrite(S14, LOW);
   break; 
}
SetDirectionY(Direction);
delay(10);
}
stopMotors();
} 
void SetDirectionY(boolean Direction){
if(Direction==1){ StepsY++;}
if(Direction==0){ StepsY--; }
if(StepsY>7){StepsY=0;}
if(StepsY<0){StepsY=7; }
}




int StepsX = 0;
void stepX(int xw){
  boolean Direction = xw>0;
  xw = abs(xw);
  for (int x=0;x<xw;x++){
switch(StepsX){
   case 0:
     digitalWrite(S21, LOW); 
     digitalWrite(S22, LOW);
     digitalWrite(S23, LOW);
     digitalWrite(S24, HIGH);
   break; 
   case 1:
     digitalWrite(S21, LOW); 
     digitalWrite(S22, LOW);
     digitalWrite(S23, HIGH);
     digitalWrite(S24, HIGH);
   break; 
   case 2:
     digitalWrite(S21, LOW); 
     digitalWrite(S22, LOW);
     digitalWrite(S23, HIGH);
     digitalWrite(S24, LOW);
   break; 
   case 3:
     digitalWrite(S21, LOW); 
     digitalWrite(S22, HIGH);
     digitalWrite(S23, HIGH);
     digitalWrite(S24, LOW);
   break; 
   case 4:
     digitalWrite(S21, LOW); 
     digitalWrite(S22, HIGH);
     digitalWrite(S23, LOW);
     digitalWrite(S24, LOW);
   break; 
   case 5:
     digitalWrite(S21, HIGH); 
     digitalWrite(S22, HIGH);
     digitalWrite(S23, LOW);
     digitalWrite(S24, LOW);
   break; 
     case 6:
     digitalWrite(S21, HIGH); 
     digitalWrite(S22, LOW);
     digitalWrite(S23, LOW);
     digitalWrite(S24, LOW);
   break; 
   case 7:
     digitalWrite(S21, HIGH); 
     digitalWrite(S22, LOW);
     digitalWrite(S23, LOW);
     digitalWrite(S24, HIGH);
   break; 
   default:
     digitalWrite(S21, LOW); 
     digitalWrite(S22, LOW);
     digitalWrite(S23, LOW);
     digitalWrite(S24, LOW);
   break; 
}
SetDirectionX(Direction);
delay(1);
}
stopMotors();
} 
void SetDirectionX(boolean Direction){
if(Direction==1){ StepsX++;}
if(Direction==0){ StepsX--; }
if(StepsX>7){StepsX=0;}
if(StepsX<0){StepsX=7; }
}


void stopMotors(){
  digitalWrite(S11, LOW); 
     digitalWrite(S12, LOW);
     digitalWrite(S13, LOW);
     digitalWrite(S14, LOW);
     digitalWrite(S21, LOW); 
     digitalWrite(S22, LOW);
     digitalWrite(S23, LOW);
     digitalWrite(S24, LOW);
}

