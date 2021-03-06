try:
	import pylon
	import _pylon
	import _pylon_calc
	import _pylon_draw
	
	import math
	
	from pylonclasses import *
	from objects import *
	from position import *
	
except ImportError:
	print 'Importing failure for the required modules in \"classes.simulation.py\".'
	print _pylon.exit(-1)
	quit()

class Simulation:
	def __init__(self,name,col):
		self.name = name
		self._collisions = col
		pylon.sim_new(self.name,self._collisions)
		pylon.sim_weight(self.name,True)
		self.start()
	
	
	def addObjectFromString(self,objstr):
		return pylon.sim_add_object_s(self.name,objstr)
	
	def newObject(self,obj):
		if pylon.object_new(self.name,obj) or not self.hasObject(obj):
			print "Cannot create object:'",obj,"' in sim:'",self.name,"'"
			return None
		return Object(obj,self.name)
	
	def newObjectFromFile(self,objname,filename,filetype):
		if pylon.object_new_fromfile(self.name,objname,filename,filetype) or not pylon.object_check(self.name,objname):
			print "Cannot create object:'",objname,"' in sim:'",self.name,"' from file:'",filename,"' of type:'",filetype,"'"
			return None
		return Object(objname,self.name)
	
	
	def hasObject(self,objname):
		if pylon.object_check(self.name,objname):
			return True
		return False
	
	def getObject(self,objname):
		return Object(objname,self.name)
	
	def clearAllObjects(self):
		return pylon.sim_clear(self.name)
	
	def removeObject(self,objname):
		if pylon.sim_remove_object(self.name,objname):
			print "pylon.sim_remove_object(",self.name,",",objname,")"
			return False
		return True
	
	
	def setNewtonianGravity(self,chs):
		pylon.sim_weight(self.name,chs)
	
	def newtonianGravityOn(self):
		pylon.sim_weight(self.name,True)
	
	def newtonianGravityOff(self):
		pylon.sim_weight(self.name,False)
	
	
	def setGravityVector(self,vect):
		pylon.sim_set_gravity_3f( self.name, vect.x, vect.y, vect.z )
	
	def getGravityVector(self):
		vect = pylon.sim_get_gravity_3f( self.name )
		return Position( vect[0], vect[1], vect[2] )
	
	
	def canCollide(self):
		return self._collisions
	
	def setCollisionIterations(self,iters):
		if self._collisions:
			pylon.sim_set_itter(self.name,iters)
	
	def getCollisionIterations(self):
		if self._collisions:
			return pylon.sim_get_itter(self.name)
		return 0
	
	
	def stop(self):
		pylon.sim_toggle(self.name,False)
	
	def restart(self):
		pylon.sim_toggle(self.name,True)
	
	def start(self):
		pylon.sim_toggle(self.name,True)

	
	def halt(self):
		pylon.sim_halt(self.name)
	
	def resume(self):
		pylon.sim_toggle(self.name,True)
		pylon.sim_visibility(self.name,True)
	
	
