#include "pos_tracker.h"
#include "servo.h"
#include <stdint.h>

class Arm {
    //instantiate the angle measurements
    uint8_t base_angle;
    uint8_t elbow_angle;
    uint8_t bicep_angle;
    uint8_t wrist_angle;
    uint8_t gripper_angle; 
    //instantiate the base 
    int base_id;
    int bicep_id;
    int elbow_id;
    int wrist_id;
    int gripper_id;
    //instantiate the servo class to be able to move the servos
    Servo servo;
    
  public:
    //constructor
  	Arm();
    //Function that moves the servos 
  	void Move_To(float* pos); 
    //destructor
  	~Arm();
};
