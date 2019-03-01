#ifndef SERVO_H
#define SERVO_H

class Servo 
{
	// File descriptor for memory-mapped I/O
	int fd;
	
	//Mapped Address
	char *ptr;

	//Write a value into the given memory offset in the memory mapped I/O.
	void RegisterWrite(unsigned offset, unsigned value);

  public: 
	//Class constructor
	Servo();
	
	//Destructor
	~Servo();
	
	//Move a servo to the target position with the given speed. Arguement
	//'angle' is a value between 0 and 180. Arguement 'speed' in an integer
	//greater than 0, given in angles per second.
	//
	//Arguement 'id' can take the following values:
	//   0 - Base 
	//   1 - Bicep
	//   2 - Elbow
	//   3 - Wrist 
	//   4 - Gripper
	//
	void MoveServo(int id, int angle, int speed);
};
#endif


