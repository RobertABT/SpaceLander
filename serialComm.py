from time import sleep
from scipy.optimize import fsolve
import serial
import sys
ser = serial.Serial('/dev/ttyUSB0', 115200) # Establish the connection on a specific port
#counter = 32 # Below 32 everything in ASCII is gibberish
pointA = [130,225,0] #these values will likely have to change
pointB = [0,0,0]
pointC = [260,0,0]
initial_guess = (50,50,10)
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
	landerX, landerY, landerZ = guess
	
	return (
		( landerX - pointA[0] )**2 + ( landerY - pointA[1] )**2 + (landerZ - pointA[2])**2 -(lengthA*0.1159)**2,
		( landerX - pointB[0] )**2 + ( landerY - pointB[1] )**2 + (landerZ - pointB[2])**2 -(lengthB*0.1159)**2,
		( landerX - pointC[0] )**2 + ( landerY - pointC[1] )**2 + (landerZ - pointC[2])**2 -(lengthC*0.1159)**2,
	)
def sendChar(c):
	ser.write(c[0]) # send it to the Arduino
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
	
def reset():
	while lengthA >=12:
		sendChar('a')
	while lengthB >=12:
		sendChar('b')
	while lengthC >=12:
		sendChar('c')

####################################################################################################

while initializing:
	if ser.readline() == 'Ready\r\n':
		initializing = False
		print 'Ready'
while True:
	#print("guess is: ", initial_guess)
	ser.flush
	sleep(0.01)
	inputChar = raw_input('What way do you want to move?')
	if inputChar=="exit":
		reset()
	else:
		sendChar(inputChar[0])
	print ("lengths A,B,C are ", lengthA, lengthB, lengthC)
	result = fsolve( equations, initial_guess )
	print("(x,y,z)=", result)
	print fsolve( equations, initial_guess, full_output=1)
	#initial_guess=result
	
