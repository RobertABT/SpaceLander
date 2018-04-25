from time import sleep
from scipy.optimize import fsolve
import serial
import sys
ser = serial.Serial('/dev/ttyUSB0', 115200) # Establish the connection on a specific port
#counter = 32 # Below 32 everything in ASCII is gibberish
pointA = [130,225,656] #these values will likely have to change
pointB = [0,0,661]
pointC = [260,0,666]
initial_guess = (130,110,570)
initLengthA = 178.0
initLengthB = 171.0
initLengthC = 162.0
initializing = True
coord = []

def valCalc(output):
	a,b = output.split("*")#removes the */r/n end characters
	i=0
	for line in a.split(","):
		if i==0:
			global lengthA
			lengthA = initLengthA + (float(line)*0.1159)
			#print lengthA
		if i==1:
			global lengthB
			lengthB = initLengthB + (float(line)*0.1159)
			#print lengthB
		if i==2:
			global lengthC
			lengthC = initLengthC + (float(line)*0.1159)
			#print lengthC
		if i==3:
			global joyX
			joyX = float(line)
			#print lengthB
		if i==4:
			global joyY
			joyY = float(line)
			#print lengthC
		if i>=5:
			break
		i+=1
	print ("lengths A,B,C are ", lengthA, lengthB, lengthC)
	print ("joy X,Y are: ", joyX, joyY)


def lenCoords(guess):
	landerX, landerY, landerZ = guess
	
	return (
		( landerX - pointA[0] )**2 + ( landerY - pointA[1] )**2 + (landerZ - pointA[2])**2 -(lengthA)**2,
		( landerX - pointB[0] )**2 + ( landerY - pointB[1] )**2 + (landerZ - pointB[2])**2 -(lengthB)**2,
		( landerX - pointC[0] )**2 + ( landerY - pointC[1] )**2 + (landerZ - pointC[2])**2 -(lengthC)**2,
	)

def coordsLen(guess):
	lenA, lenB, lenC = guess
	return (
		( coord_w[0] - pointA[0] )**2 + ( coord_w[1] - pointA[1] )**2 + (coord[2] - pointA[2])**2 -(lenA)**2,
		( coord_w[0] - pointB[0] )**2 + ( coord_w[1] - pointB[1] )**2 + (coord[2] - pointB[2])**2 -(lenB)**2,
		( coord_w[0] - pointC[0] )**2 + ( coord_w[1] - pointC[1] )**2 + (coord[2] - pointC[2])**2 -(lenC)**2,
	)
		
def readVal():
	output = ""
	while ser.in_waiting == 0:
		sleep(0.1)
	while ser.in_waiting:
		c=ser.readline()
		output += c
		if c=="*":
			print 'EOT'
			break
	valCalc(output)

def addCoord():
	global coord_w = []
	coord_w[0] = coord[0] + joyX
	coord_w[1] = coord[1] + joyY
	
def processLen(lengths)
	global x, y, z = lengths
	
	x -= 178.0
	x = x/0.1159
	y -= 171.0
	y = y/0.1159
	z -= 162.0
	z = z/0.1159
	
def reset():
	while lengthA >=189.58 and lengthB >=182.58 and lengthC >=173.58:
		sendChar('a')
		sendChar('b')
		sendChar('c')
	sendChar('r')
####################################################################################################

while initializing:
	if ser.readline() == 'Ready\r\n':
		initializing = False
		print 'Ready'
while True:
	readVal() #reads all values, and stores them
	result = fsolve( lenCoords, initial_guess )
	print("(x,y,z)=", result)
	coord = result
	addCoord()
	strlen_guess = (lengthA,lengthB,lengthC)
	derivedLen = fsolve(coordsLen, strlen_guess)
	print ("guessed length is", derivedLen)
	processLen(derivedLen) #turn string length into steps
	Serial.print(x,y,z)
	
	#inputChar = raw_input('What way do you want to move?')
	#if inputChar=="exit":
	#	reset()
	#	result = fsolve( lenCoords, initial_guess )
	#	print result
	#	sys.exit()
	#else:
	#	sendChar(inputChar[0])
	
