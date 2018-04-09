from time import sleep
from scipy.optimize import fsolve
import serial
import sys
ser = serial.Serial('/dev/ttyUSB0', 115200) # Establish the connection on a specific port
#counter = 32 # Below 32 everything in ASCII is gibberish
pointA = [130,225,0] #these values will likely have to change
pointB = [0,0,0]
pointC = [260,0,0]
#lengthA = 0.1
#lengthB = 0.1
#lengthC = 0.1
initializing = True

def lengthCalc(output):
	a,b = output.split("*")#removes the */r/n end characters
	i=0
	for line in a.split(","):
		if i==0:
			global lengthA
			lengthA = float(line)*0.1159
			print lengthA
		if i==1:
			global lengthB
			lengthB = float(line)*0.1159
			print lengthB
		if i==2:
			global lengthC
			lengthC = float(line)*0.1159
			print lengthC
		if i>=3:
			break
		i+=1
	print ("lengths A,B,C are ", lengthA, lengthB, lengthC)
	
def equations(guess):
	x, y, z = guess
	
	return (
		( landerX - pointA[1] )**2 + ( landerY - pointA[2] )**2 + (landerZ - pointA[3])**2 -(lengthA)**2,
		( landerX - pointB[1] )**2 + ( landerY - pointB[2] )**2 + (landerZ - pointB[3])**2 -(lengthB)**2,
		( landerX - pointC[1] )**2 + ( landerY - pointC[2] )**2 + (landerZ - pointC[3])**2 -(lengthC)**2,
	)

####################################################################################################

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
	lengthCalc(output)
	print ("lengths A,B,C are ", lengthA, lengthB, lengthC)
	#initial_guess = ( 30, 30, -10)
	#result = fsolve( equations, initial_guess )
	#print("(x,y,z)=", result)


