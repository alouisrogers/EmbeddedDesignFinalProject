main: main.o servo.o pos_tracker.o wiimote.o arm.o button_event.o
	g++ main.o servo.o pos_tracker.o wiimote.o arm.o button_event.o -o main

main.o: main.cc servo.h pos_tracker.h wiimote.h arm.h button_event.h
	g++ -c main.cc

servo.o: servo.cc servo.h
	g++ -c servo.cc

pos_tracker.o: pos_tracker.cc pos_tracker.h
	g++ -c pos_tracker.cc

wiimote.o: wiimote.cc pos_tracker.h wiimote.h button_event.h
	g++ -c wiimote.cc

arm.o: arm.cc arm.h
	g++ -c arm.cc

button_event.o: button_event.cc button_event.h
	g++ -c button_event.cc 

clean: 
	rm *o main
               

