try:
	import pylon
	import _pylon
	import _pylon_calc
	import _pylon_draw
	
	import shlex
	import thread
	import math
	from threading import *
	"""import pygame
	from pygame import Rect
	from pygame.locals import *"""
	
except ImportError:
	print 'Importing failure for the required modules in \"classes.pylonclasses.py\".'
	print _pylon.exit(-1)
	quit()

lastkey = chr(0)
lastkeycount = 0
def getstrthing(st):
	global lastkey
	global lastkeycount
	if pylon.key_ispressed(pylon.key_last()) and (not lastkey == pylon.key_last() or (lastkey == pylon.key_last() and lastkeycount > 5)):
		st = st + str(pylon.key_last())
		if not lastkey == pylon.key_last():
			lastkeycount = 0
			lastkey = pylon.key_last()
		#a = 0
		#while a < 500:
			#a = a + 1
	if lastkey == pylon.key_last():
		lastkeycount = lastkeycount + 1
	return st


def getposcoord(pos,cord):
	my_splitter = shlex.shlex(pos, posix = True)
	my_splitter.whitespace += "{},[]"
	my_splitter.whitespace_split = True
	axis = list(my_splitter)
	return float(axis[cord])

def makepos(x,y,z):
	return '{['+str(x)+'],['+str(y)+'],['+str(z)+']}'

def rtd(r):
	return float(r/math.pi)*float(180.0)
def dtr(d):
	return float(d/180.0)*float(math.pi)






	"""class XboxController:
	def __init__(self,joynum):
		if joynum >= pygame.joystick.get_count():
			print 'not a valid joystick.'
		self.joystickNumber = joynum
		self.joy = pygame.joystick.Joystick(self.joystickNumber)
		self.joy.init()
		
	def getAxisList(self):
		return [self.joy.get_axis(i) for i in [0, 1, 2, 3, 4, 5]]
	
	def getAxis(self, axis):
		return self.joy.get_axis(axis)
	
	def getLeftX(self):
		return self.joy.get_axis(0)
		
	def getLeftY(self):
		return self.joy.get_axis(1)
	
	def getRightX(self):
		return self.joy.get_axis(3)
		
	def getRightY(self):
		return self.joy.get_axis(4)
	
	def getLeftTrigger(self):
		return self.joy.get_axis(2)
	
	def getRightTrigger(self):
		return self.joy.get_axis(5)
	
	def getButton(self, button):
		return self.joy.get_button(button)"""


