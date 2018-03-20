from time import sleep
import serial
import sys
ser = serial.Serial('/dev/ttyUSB0', 115200) # Establish the connection on a specific port
#counter = 32 # Below 32 everything in ASCII is gibberish

initializing = True
while initializing:
	if ser.readline() == 'Ready\r\n':
		initializing = False
		print 'Ready'
while True:
	ser.flush
	sleep(0.01)
	sentChar = raw_input('What way do you want to move?')
	ser.write(sentChar[0]) # send it to the Arduino
	ser.flushOutput()
	i=1
	output = ""
	while ser.in_waiting == 0:
		sleep(0.1)
	while ser.in_waiting:
		c=ser.readline()
		output += c
		if c=="*":
			print 'EOT'
			break
	print output
