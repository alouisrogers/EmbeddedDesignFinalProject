#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include <poll.h>
#include "pos_tracker.h"
#include "wiimote.h"
#include "button_event.h"

Wiimote::Wiimote(PosTracker *pt, ButtonEvent *be){
 acc_fd = open("/dev/input/event0", O_RDONLY);
 if(acc_fd == -1){
        std::cerr<< "Error: Could not open the event file - forgot sudo?\n";
        exit(1);
 }
  btn_fd = open("/dev/input/event2", O_RDONLY);
  if(btn_fd == (-1)) {
	std::cerr<< "Error: Could not open the event file = forgot sudo?\n";
	std::cout << "in the wiimode cc" << std::endl;
	exit(1);
  }
  pos = new float[8];
  this->pt = pt;
  this->be = be;
}

Wiimote::~Wiimote() {
  close(acc_fd);
  close(btn_fd);
  delete[] xyz;
  delete[] pos;
}
bool Wiimote::has_more_to_read(int fd){
	struct pollfd pfd;
	pfd.fd = fd;
	pfd.events =POLLIN;

	int res = poll(&pfd, 1, 1);
	if(res == -1){
	  perror("poll");
	} 
	else if (res == 0){
	  return false;
	}
	return true;
}

bool Wiimote::ReadBtn(int *code, int *value){
	if(!has_more_to_read(btn_fd)){
	  return false;
	}
	char buf[32];
	read(btn_fd, buf, 32);
	
	*code = buf[10];
	*value = buf[12];

	return true;
}

float*  Wiimote::Listen() {
        //read a packet of 32 bytes from wiimote
        char buffer[32];
        read (acc_fd, buffer, 32);
        //extract code (byte 10) and value (byte 12)
        int acc_code = buffer[10];
        short acc_value = *(short *)(buffer+12);
	//We need to not wait if there is not data 
	//check the end of the data
	int btn_code;
	int btn_value; 
	bool pressed = ReadBtn(&btn_code, &btn_value);
        //get the data
        xyz = pt->PositionTracker(acc_code, acc_value);
        if(pressed||!pressed){
	  ab = be->ButtonPress(&btn_code, &btn_value);
	}
	//when data is ready pu
  //return the packaged array 
  //that will be sent to the arm
  std::cout<<ab[0]<<" "<<ab[1]<<" "<<ab[2]<<" "<<ab[3]<<" "<<ab[4]<<"\n"; 
  return ab;
}  	

       
