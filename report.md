# FINAL PROJECT: Controlling the Robotic Arm with a Wiimote
## Anthony Rogers and Alena Porter

### The purpose of this project is to combine hardware and software to move the robotic arm using a wii remote. We used the Simulink Design from Lab 11 and we took the C++ files from Lab 5 and altered them to serve a slightly different purpose. We also instantiated a few new classes to be able to combine hardware and software, and control the robotic arm with the wiimote. All files were created on the ECE lab desktop then transfered to the Zedboard. 

The Angle to PWM simply converted the angle into the appropirate pulse width that would move the arm to that degree position. The was done using simple math. The simulations were all done with the numbers divided by 100 so that the simulations would take faster. The results reflect this and must be mutiplyed by 100 to see what we would actually see on the Zedboard. The following images depict the output of a simulation of the simulink subsystem AngleToPWM at 0, 90, and 180 degrees—

For the pulse at 0°, we get a width 300 which multiplied by 100 gives us 30000 which is what we expect:

![ZERO](https://github.com/eece2160-fall17-s8/lab-11-group-9/blob/master/AngleToPWMScope0.PNG)

For the pulse at 90°, we get a width 750 which multiplied by 100 gives us 75000 which is what we expect:

![NINETY](https://github.com/eece2160-fall17-s8/lab-11-group-9/blob/master/AnglePWMScope90.PNG)

For the pulse at 180°, we get a width 1200 which multiplied by 100 gives us 120000 which is what we expect:

![ONE-EIGHTY](https://github.com/eece2160-fall17-s8/lab-11-group-9/blob/master/AngleToPWMScope180.PNG)

The following image is the simulink subsystem SpeedToPulse:

![SpeedToPulse](https://github.com/eece2160-fall17-s8/lab-11-group-9/blob/master/SpeedToPulse.svg)


The following images depict outputs from a simulation of the simulink subsytstem SpeedToPulse at 10 and 100 degrees per second—

10°/sec: 

![TEN](https://github.com/eece2160-fall17-s8/lab-11-group-9/blob/master/SpeedToPulse10.PNG)

100°/sec:

![ONE-HUNDRED](https://github.com/eece2160-fall17-s8/lab-11-group-9/blob/master/SpeedToPulse100.PNG)

The scope shows the simulation for the speed the SpeedToPulse Generator at 100 degrees per second. With our adjusted constants for the simulation, the HDL counter would count to the value of our constant 50e4 divided by the speed 100, 20 times per second. This is shown by the fact 50e4/100 = 50e2. And our time frame of one second is 1e4, normally 1e6, shows that there should be 1e4/50e2 pulses per second, or 20 pulses per second which is what is shown in the scope. These constant pulses will move the servo faster or slower depending on how many occur per cycle. This is exactly what we want to see and our simulation or this logic block matches what our output should be. 


The following image is the simulink subsystem AngleSpeedToPWM:

![AngleSpeed](https://github.com/eece2160-fall17-s8/lab-11-group-9/blob/master/AngleSpeedToPWM.svg)

The following image depicts an output of a simulation in which the angle is set to 80° and the speed is set to 10°/sec:

![AngleSpeedToPWM](https://github.com/eece2160-fall17-s8/lab-11-group-9/blob/master/AngleSpeedToPWM.PNG)

The AngleSpeedToPWM block pulses at the time intervals given by the SpeedToPulse making shorter time intervals between pulses to make the arm move faster. The increase or decrease in these pulse widths accounts for the change in angle. Because of the scale it can be hard to see, but in the following image has the simulation for the AngleSpeedToPWM at 10 degrees per second and angle of 80 degrees. The pulse widths increase from their start at 30000, which is 0 degrees to 70000, which is 80 degrees, again these numbers were adjusted for simulation purposes but this is the equivalent of what the Zedboard will see. The AngleSpeedToPWM pulses on every other SpeedToPulse pulse and if there was a greater speed inputed, these values would be closer together resulting in a faster movement of the arm and quicker increase in the pulse widths. 


The PWM Generator below uses all of the previous subsystems to control the servo speed and angle of each servo:

![PMW Generator](https://github.com/eece2160-fall17-s8/lab-11-group-9/blob/master/PWMGenerator.svg)

Much of the code used in this project was developed from previous labs, such as Lab 6 where we used the Wiimote to control the LEDs. 
We instantiated the classes Arm, Button_event, Servo, Pos_tracker and Wiimote. Our main functions creates an arm, a postracker, a button event, and a wiimote. The main function then takes in data from the wiimote and calls Move-To on the position. The Listen function is located in the wiimote.cc file and takes in data from the wiimote, so other files can take the data and move the robotic arm. Move_To is a function in the arm.cc file that changes the angle of the servos based on the data from the wiimote. 

The following commands and buttons were used on the wiimote to control the robotic arm:
- Left: move base counterclockwise
- Right: move base clockwise
- 1: Move bicep up
- 2: Move bicep down
- Up: Move elbow up
- Down: Move elbow down
- B: Move wrist up and down
- A: Open and close gripper

  The code implemented took information from the Wii remote and used that information to send angle and speed information to the FPGA on the Zedboard. First we had a simple script file to connect the wii remote to the computer. This was once the wii remote was connected, we used a Wiimote Class that would create a mapping of the device and read button events and acceleration events . The wiimote would take in event handlers as arguments to be able to send data to them for processing once the values had been read. The Wiimote would read a button and using the function has_more_to_read, it would keep reading buttons so as to get a continuous flow of information even with the blocking nature put in place by the reading of the acceleration events. The wiimote Listen function created a buffer to store the information and read in the codes and values of the data from the wiimote. The values returned by the button events and acceleration events were stored in two separate arrays and due to limiting hardware and time constraints we only returned the array of buttons from the function and left position values generated from acceleration unused. 

  The Wiimote class’s Listen function called on two function to process received data and what to do with the different kinds of events. The PosTracker class which was ultimately not used in the final implementation took the code and acceleration value in one access and used kinematics to get position values out of wiimote. The code used a state machine so it would wait until position values for X Y and Z were updated until it spit the data back out as an array of floats to the wiimote.listen function. The  other function called by the wiimote.listen function is one of the ButtenEvent class. This reads the buttons from the wiimote rather than acceleration values. Each button had a specific code and we processed the data based on the code using an if statement for each button press we wanted functionality for. The left and right buttons would increase and decrease, respectively, the angle of the base by 5 degrees to get the base rotate both ways. The One and Two buttons on the wiimote were set to increase or decrease the angle of the bicep by 5 degrees respectively if pushed.  The up and down buttons would increase or decrease the angle of the elbow by 5 degrees respectively if pushed. The wrist was set up so that holding the B button would increase the angle of the wrist by 5 degrees and letting of the wrist button would have the angle of the wrist continuously decrease by 5 degrees. The Gripper was a binary open and close with the push of the A button. All these movements had clauses in their if statements to keep the angle between 0 and 180 for the arm. These values were stored in a five element array where each index corresponded to a specific servo. This array was then returned after the function call, to the wiimote.listen function.

  There were two classes that took care of moving the servos. The Servo class had all the information to move a single servo. It created a memory map so the Zedboard to push the information to. It has only one other function and this check to make sure that the servo id is correct, that the angle is between the right values, and then then writes the speed and angle to correct place using the MoveServo function. The speed and angle values are then processed and handled by the Simulink code on the FPGA. The Arm class takes care of all of the movements. It takes in the array of button events which has the information about the angle each servo should be at. In the header, it creates and instant of the servo class so that it has the function to move all of the servos. In the Move_To function it sets each index value equal to the variables saying which angle corresponds to what. It then calls the MoveServo function of the servo class and gives it the proper angle always keeping the speed at 180 because we want the arm moving quickly to try and keep up with the command of the user. 

  In the main function call the event handlers were instantiated along with the arm and the wiimote, which took the two eventhandlers as its arguments. In the infinite while loop, the Wiimote Listen function is called so that code is constantly reading data from the movement and buttons presses of the wiimote. The values returned from the wiimote.listen function are pointed to a pointer called pos and Move_To function of the arm class is called with the pointer to the array of angles. The Move_To function uses this to move all of the servos and this repeats continuously as long as code is running.  



The following are videos of the robotic arm being controlled with the Wiimote. The arm moves with each press of a button. So in order to control different servos, different buttons are pressed repeatedly. 

[![Part 1](https://youtu.be/guwWDIlApGI)](https://youtu.be/guwWDIlApGI)

[![Part 2](https://youtu.be/Ki5UMyqpM3Q)](https://youtu.be/Ki5UMyqpM3Q)

[![Part 3](https://youtu.be/D_n2R8vUEnk)](https://youtu.be/D_n2R8vUEnk)

