# SpaceLader
Dissertation Project

Dependencies

This project is built to run under python 2.7 and requires the following package(s):
  -scipy

This/These can be installed by running the following (this may be different based on your OS) :
  - apt install python2.7 python-pip
  - pip install scipy

Ports

You will also need to be able to upload to an arduino, and detect what port it is on. In the python code in this project this port is hardcoded as "/dev/ttyUSB0", but this may well need to be edited for your setup. "ls /dev/ | grep tty" should return the possible ports under linux.

Hardware

In most cases the IR sensors need to be precisely tuned before you use them to automatically set the start point, this must be done on the hardware.

Hardware setup

If you want to customise the size of the landing area that is doable, however any changes must be added to the python code, the below values are the defaults, coordinates are measured from point B (this is arbitrary, and could be measured from any point). Length values are measured from lander (where the three strings meet) to where they enter the motor assemblies.
All of these values are in mm.
pointA = [130,225,656] 
pointB = [0,0,661]
pointC = [260,0,666]
initial_guess = (130,110,570)
initLengthA = 178.0
initLengthB = 171.0
initLengthC = 162.0

Running the program

First upload the most up to date completed arduino script (currently Test_Script.ino) to the Aduino nano then run the corresponding python script (in this case python serialComm.py). This will give you your interface.

Common Issues

If the system isn't moving as far as it should for each instruction it is possible that the string has come off of the drum, in which case you either need to completly unwind it by reversing your previous instructyions or by disassembling the system and moving the motor by hand until the fault is resolved. After doing this you will likely need to use Test_Script_no_endstops to reset the system to a satisfactory location

Slack in the strings may cause issues in the geometry data being returned, as will starting at a point that doesn't have roughly the string lengths and pole positions that are laid out in serialComm.py

Future versions

Future versions will include joystick control.
