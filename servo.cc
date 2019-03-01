#include "servo.h"
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <iostream>
#include <unistd.h>

Servo::Servo()
{
	//Open memory mapped I/O
	fd = open("/dev/mem", O_RDWR);
	
	//Map physical memory
	ptr = (char *) mmap(NULL, 0xff, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0x400d0000);

	//check success 
	if (ptr == (void *) -1)
	{
		std::cerr << "Error mapping memory - forgot sudo?\n";
		std::cout << "here"<< std::endl;
		exit(1);
	}
	
	//Initial servo positions
	for (int i = 0; i < 5; i++)
	{
		MoveServo(i, 90, 180);
	}
}

Servo::~Servo()
{
	//Unmap physical memory
	munmap(ptr, 0xff);
	
	//Close memory mapped I/O
	close(fd);
}

void Servo::RegisterWrite(unsigned offset, unsigned value)
{
	*(volatile unsigned *)(ptr + offset) = value;
}

void Servo::MoveServo(int id, int angle, int speed)
{
	//Check valid servo
	if (id < 0 || id > 4)
	{
		std::cerr << "Invalid servo ID\n";
		exit(1);
	}
	
	//verify valid angle 
	if(angle < 0 || angle > 180)
	{
		std::cerr << "Invalid angle\n";
		exit(1);
	}
	
	//Set memory locations
	RegisterWrite(0x100 + id * 8, angle);
	RegisterWrite(0x100 + id * 8 + 4, speed);
}

