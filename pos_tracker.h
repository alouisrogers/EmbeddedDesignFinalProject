#ifndef POS_TRACKER_H_
#define POS_TRACKER_H_
#include <sys/time.h>

// Got ride of #include acc_event_handler here -- not sure if we need to add something - AP

class PosTracker {
	double t;
	double ti;
	double a[3];
	double v[3];
	float* p;
  float* data_not_ready;
	bool pos_state [3];
	double ms;
	double s;
  double g;
    public:
	    PosTracker();
	    ~PosTracker();
	    float* PositionTracker(int code, short value);	
	    double GetTime();	
};

#endif  // POS_TRACKER_H_
