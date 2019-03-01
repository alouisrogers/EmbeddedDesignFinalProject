#include <unistd.h>
#include "servo.h"
#include "pos_tracker.h"
#include "wiimote.h"
#include "arm.h"
#include "button_event.h"

int main() {
  // Instantiate objects here.
  float* pos;
  //angle = new float [5];
  //create the arm
  Arm arm;
  //create the PosTracker statically 
  PosTracker pt;
  //create the ButtonEvent statically
  ButtonEvent be;
  //Call the wii remote and pass the pointer of the 
  //position tracker and the button event 
  Wiimote wiimote(&pt, &be);
  //infinite loop to read and write to registers
  while(true){
    pos = wiimote.Listen();
    arm.Move_To(pos);
  }
  //delete the position array
  return 0;
}
