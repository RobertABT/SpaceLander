import serial
import sys
#import io
ser = serial.Serial(serial.tools.list_ports,115200, timeout = 0)
ser.open()
while ser.is_open():
	print ser.read()
	#stdInput  = sys.stdin.readlines()
	#if stdInput != "":
	#	ser.write(stdInput)
	#	stdInput=""
	#	print "input sent"

