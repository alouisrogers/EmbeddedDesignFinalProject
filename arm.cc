#include <iostream>
#include <cmath>
#include <algorithm>
#include "arm.h"


Arm::Arm() {
 //Set all the angles to 0 to start
  base_angle = 0;
  elbow_angle = 0;
  bicep_angle = 0;
  wrist_angle = 0;
  gripper_angle = 0; 
}
Arm::~Arm(){
}
    

//void Arm::move_to(float x, float y, float z, float gripper, float wrist){	
void Arm::Move_To(float* pos){
  //calculate the base angle using the x and y coordinates
  //base_angle =  atan2(pos[1], pos[0]) * 180 / 3.14159;
  //calculate the elbow angle using the y and z angles
  //elbow_angle = atan2(pos[2], pos[1]) * 180 / 3.14159;
  //cast the 1 or 0 float to a boolean and set gripper to max or min angle 
  //showing open or close 
  base_angle = pos[0];
  bicep_angle = pos[1];
  elbow_angle = pos[2];
  wrist_angle = pos[3];
  gripper_angle = pos [4];
 	//Move the robotic arm at max speed
  std::cout<<"Moving the Arms\n"; 
  servo.MoveServo(0, base_angle, 180);
  servo.MoveServo(1, bicep_angle, 180);
  servo.MoveServo(2, elbow_angle, 180);
  servo.MoveServo(3, wrist_angle, 180);
  servo.MoveServo(4, gripper_angle, 180);
  std::cout<<"the arms have been moved\n";    
 }

 
