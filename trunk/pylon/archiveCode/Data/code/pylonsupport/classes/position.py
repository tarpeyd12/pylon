try:
	import pylon
	import _pylon
	import _pylon_calc
	import _pylon_draw
	
	import shlex
	import thread
	import math
	from threading import *
	
	from pylonclasses import *
	
except ImportError:
	print 'Importing failure for the required modules in \"classes.position.py\".'
	print _pylon.exit(-1)
	quit()

class Position:
	def __init__(self,a,b,c):
		self.x = a
		self.y = b
		self.z = c

	def __str__(self):
		return '{['+str(self.x)+'],['+str(self.y)+'],['+str(self.z)+']}'

	def fromstring(self,string):
		splitter = shlex.shlex(string, posix = True)
		splitter.whitespace += "{},[]"
		splitter.whitespace_split = True
		axis = list(splitter)
		return self(axis[0],axis[1],axis[2])

	def from3f(self,a,b,c):
		return self(a,b,c)

	def __eq__(self,other):
		# is equal to
		return self.x==other.x and self.y==other.y and self.z==other.z

	def __ne__(self,other):
		# is not equal to
		return self.x!=other.x or self.y!=other.y or self.z!=other.z






