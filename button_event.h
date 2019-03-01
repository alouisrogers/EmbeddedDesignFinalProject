#ifndef BUTTON_EVENT_H_
#define BUTTON_EVENT_H_

class ButtonEvent {
    //will go to the gripper 
    int  ButtonA;
    //will go to the wrist
    int  ButtonB;
    int Up;
    int Down;
    int Left;
    int Right;
    int One; 
    int Two; 
    //is the button pressed
    int value;
   
   public:
    //button (bool)float array
    float* p;
     ButtonEvent();
     ~ButtonEvent();
     //Takes care of the button presses and returns a 2 element array
     float* ButtonPress(int *code, int *value);     
};

#endif //BUTTON_EVENT_H_
