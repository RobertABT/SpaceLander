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
	sleep(0.1)
	c = raw_input('What way do you want to move?')
	ser.write(c[0]) # send it to the Arduino
	sleep(.1)
	i=0
	print ser.in_waiting
	while i <= ser.in_waiting:
		c=ser.read(1)
		if c=='*':
			print ser.read(2)
			print 'EOT'
			break
		print c
		i = i + 1
		#bytesToRead = ser.in_waiting
		#print bytesToRead
		#print ser.readline() # Read the newest output from the Arduino
