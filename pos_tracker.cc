#include <sys/time.h>
#include <iostream>
#include "pos_tracker.h"
// Position Tracker
PosTracker::PosTracker(){
  //Get the initial time 
	ti = GetTime();
  //set the intial values of the state array to false 
	pos_state[0] = false;
	pos_state[1] = false;
	pos_state[2] = false; 
  //set the gravity constant to cancel out gravity in the y
  g = 9.8039;
  //set the data_not_ready to "true"
  //THIS NEVER CHANGES
  //We just return this instead of the array of data in the event
  //the data is not ready and the wiimote function waits to run its 
  //code until the data_not_ready is false
  p = new float[4];
  //first index is the data ready bit 
	p[0] = 0.0;
  //index 1-3 are data
	p[1] = 0.0;
	p[2] = 0.0;
 	p[3] = 0.0;
  //velocity data
	v[0] = 0.0;
	v[1] = 0.0;
	v[2] = 0.0;
}
PosTracker::~PosTracker(){
  delete[] p;
}

double PosTracker::GetTime(){
	struct timeval tv;
	gettimeofday(&tv,NULL);
	ms = (tv.tv_usec)/1000000.0;
	s = tv.tv_sec; 
	return ms+s;
}		
		   	
	
float* PosTracker::PositionTracker(int code, short value){
  //SETS THE DATA READY BIT TO FALSE
  p[0] = 0;
  /*State machine, check the code and gets the acceleration data accordingly then 
  processes it all at once when it has all the acceleration values from the wiimote
  and sets the values in the state machine to true to got the next step*/
	if (code == 3){
		pos_state[0] = true;
		a[0] = (double)value;
	}
	else if (code == 4){
		pos_state[1] = true;
		a[1] = (double)value;
	}
	else if (code == 5){
		pos_state[2] = true;
		a[2] = (double)value;
	}
	if (pos_state[0] == true &&
	    pos_state[1] == true &&
	    pos_state[2] == true){
		//intialize t;
		t = GetTime();
		v[0] = v[0] + a[0]*(t-ti);
		v[1] = v[1] + a[1]*(t-ti);
		v[2] = v[2] + a[2]*(t-ti);
		//get the postions using the kinematic equations:
    //Equation in the X
		p[1] = p[1] + v[0]*(t-ti) + (0.5)* a[0]*(t-ti)*(t-ti);
    //Equation in the Y
		p[2] = p[2] + v[1]*(t-ti) + (0.5)*(a[1] -  g)*(t-ti)*(t-ti);
    //Equation in the Z
		p[3] = p[3] + v[2]*(t-ti) + (0.5)*a[2]*(t-ti)*(t-ti);
		//print out the positions 
		//std::cout << "The XYZ Position is "
		//	 << p[1] << ", " << p[2] << ", " << p[3] << "\n";
		//change the t value to make the initial the final 
		pos_state[0] = false;
		pos_state[1] = false;
		pos_state[2] = false;
    //SETS THE DATA READY BIT TO TRUE BEFORE SENDING
    p[0] = 1;
	}
  return p;
}

     
    

	

