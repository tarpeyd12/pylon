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
	def __init__(self,a=0,b=0,c=0):
		self.x = a
		self.y = b
		self.z = c

	def __str__(self):
		return '{['+str(self.x)+'],['+str(self.y)+'],['+str(self.z)+']}'
	
	def tostring(self):
		return '{['+str(self.x)+'],['+str(self.y)+'],['+str(self.z)+']}'
	
	def tostr(self):
		return '{['+str(self.x)+'],['+str(self.y)+'],['+str(self.z)+']}'
	
	def fromstring(self,string):
		splitter = shlex.shlex(string, posix = True)
		splitter.whitespace += "{},[]"
		splitter.whitespace_split = True
		axis = list(splitter)
		self.x = float(axis[0])
		self.y = float(axis[1])
		self.z = float(axis[2])
		#return self.__init__(axis[0],axis[1],axis[2])
		
	def fromstr(self,string):
		splitter = shlex.shlex(string, posix = True)
		splitter.whitespace += "{},[]"
		splitter.whitespace_split = True
		axis = list(splitter)
		self.x = float(axis[0])
		self.y = float(axis[1])
		self.z = float(axis[2])
		#return self.__init__(axis[0],axis[1],axis[2])

	def from3f(self,a,b,c):
		self.x = a
		self.y = b
		self.z = c
		#return self.__init__(a,b,c)
	
	def distance(self,other):
		return math.sqrt( (other.x-self.x)**2 + (other.y-self.y)**2 + (other.z-self.z)**2 )
	
	def distancesquared(self,other):
		return (other.x-self.x)**2 + (other.y-self.y)**2 + (other.z-self.z)**2
	
	def length(self):
		return math.sqrt( self.x**2 + self.y**2 + self.z**2 )
	
	def lengthsquared(self):
		return self.x**2 + self.y**2 + self.z**2
	
	def __sub__(self,other):
		return Position(self.x-other.x,self.y-other.y,self.z-other.z)
	
	def __isub__(self,other):
		self.x -= other.x
		self.y -= other.y
		self.z -= other.z
		return self
	
	def __add__(self,other):
		return Position(self.x+other.x,self.y+other.y,self.z+other.z)
	
	def __iadd__(self,other):
		self.x += other.x
		self.y += other.y
		self.z += other.z
		return self
		
	def __mul__(self,val):
		return Position(self.x*val,self.y*val,self.z*val)
	
	def __imul__(self,val):
		self.x *= val
		self.y *= val
		self.z *= val
		return self
	
	def __div__(self,val):
		return Position(self.x/val,self.y/val,self.z/val)
	
	def __imul__(self,val):
		self.x /= val
		self.y /= val
		self.z /= val
		return self
	
	def __eq__(self,other):
		# is equal to
		return self.x==other.x and self.y==other.y and self.z==other.z

	def __ne__(self,other):
		# is not equal to
		return self.x!=other.x or self.y!=other.y or self.z!=other.z






