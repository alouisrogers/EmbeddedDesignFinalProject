#ifndef WIIMOTE_H_
#define WIIMOTE_H_
#include "pos_tracker.h"
#include "button_event.h"
#include <stdio.h>

// got rid of acc_event_handler here -AP

/**
 * Wiimote encapsulates the interaction with the wiimote hardware
 */
class Wiimote {
	//accleration
	int  acc_fd;
	//button
	int  btn_fd;
	//output array
	float* pos;
	//position array of x y z values
	float* xyz;
	//button array
	float* ab;
	//create the has more to read
	bool has_more_to_read(int fd); 
	PosTracker* pt;
	//create the ButtonEvent
	ButtonEvent* be;
  public:
	Wiimote(PosTracker* pt, ButtonEvent* be);
	~Wiimote();
	float* Listen();
	
	bool ReadBtn(int *code, int *value);
	
};

#endif  // WIIMOTE_H_
