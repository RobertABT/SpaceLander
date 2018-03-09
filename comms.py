from time import sleep
import serial
import sys
ser = serial.Serial('/dev/ttyUSB0', 115200) # Establish the connection on a specific port
#counter = 32 # Below 32 everything in ASCII is gibberish
sleep(.2)
ser.flushInput()
ser.flushOutput()
sleep(.1)
while True:
	c = raw_input('What way do you want to move?')
	ser.write(c[0]) # send it to the Arduino
	while ser.in_waiting > 0:
		bytesToRead = ser.in_waiting
		print bytesToRead
		print ser.readline() # Read the newest output from the Arduino
	#while ser.in_waiting > 0:
	#	ser.write('f')
	#	bytesToRead = ser.in_waiting
	#	print ser.read(bytesToRead)
	#sleep(.1) # Delay for one tenth of a second	
