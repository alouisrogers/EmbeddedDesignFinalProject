#include "button_event.h"
#include <iostream>

ButtonEvent::ButtonEvent(){
  p = new float[5];
  p[0] = 0.0;
  p[1] = 0.0;
  p[2] = 0.0;
  p[3] = 0.0;
  p[4] = 0.0;
  ButtonA = 48;
  ButtonB = 49;
  One = 1;
  Two = 2;
  Left = 105;
  Right = 106;
  Up = 103;
  Down = 108;
}
ButtonEvent::~ButtonEvent(){
  delete[] p;
}

float* ButtonEvent::ButtonPress(int *code, int *value){
  //if button A is pressed the first element of the array will reflect that 
  //A is for the gripper, binary open or close 
  if((*code == ButtonA)&&(*value==1)){
	p[4] = 180;
  }
  else if((*code == ButtonA)&&(*value == 0)){
	p[4] = 0;
  }
  if((*code == ButtonB)&&(*value==1)&&(p[3]<180)){
	p[3] += 5;
  }
  else if((*code == ButtonB)&&(*value == 0)&&(p[3]>0)){
 	p[3] -= 5;
  } 
  if((*code == Left)&&(*value == 1)&&(p[0]>0)){
	p[0] -= 5;
  }
  if((*code == Right)&&(*value == 1)&&(p[0]<180)){
	p[0] += 5;
  }
  if((*code == Up)&&(*value == 1)&&(p[2]<180)){
	p[2] += 5;
  }
  if((*code == Down)&&(*value == 1)&&(p[2]>0)){
	p[2] -= 5;
  }
  if((*code == One)&&(*value == 1)&&(p[1]<180)){
	p[1] += 5;
  }
  if((*code == Two)&&(*value == 1)&&(p[1]>0)){
	p[1] -= 5;
  }
  
  //if the button B is pressed the second element of the array reflects that
  //B is for the wrist, binary open or close
  //std::cout<<p[0] << " " << p[1]<<" "<< p[2]<<" "<< p[3]<<" "<< p[4]<< "\n";
  return p;
}
