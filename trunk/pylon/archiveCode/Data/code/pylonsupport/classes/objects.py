try:
	import pylon
	import _pylon
	import _pylon_calc
	import _pylon_draw
	
	import math
	
	from pylonclasses import *
	from position import *
	
except ImportError:
	print 'Importing failure for the required modules in \"classes.objects.py\".'
	print _pylon.exit(-1)
	quit()


class Object:
	def __init__(self,name,simname):
		self.name = name
		self.simname = simname
		
		if not self.check() and pylon.object_new(self.simname,self.name):
			print "Cannot create object:'",self.name,"' in sim:'",self.simname,"'"
	
	def check(self):
		if pylon.object_check(self.simname,self.name):
			return True
		return False
	
	
	def isVisable(self):
		return pylon.object_get_visibility( self.simname, self.name )
	
	def setVisibility(self,vis):
		pylon.object_set_visibility( self.simname, self.name, vis )
	
	def setInvisible(self):
		pylon.object_set_visibility( self.simname, self.name, False )
	
	def setVisible(self):
		pylon.object_set_visibility( self.simname, self.name, True )
	
	
	def getPos(self):
		pos = pylon.object_get_pos_3f( self.simname, self.name )
		return Position( pos[0], pos[1], pos[2] )
	
	def getRot(self):
		rot = pylon.object_get_rot_3f( self.simname, self.name )
		return Position( rot[0], rot[1], rot[2] )
	
	def getDir(self):
		dirc = pylon.object_get_dir_3f( self.simname, self.name )
		return Position( dirc[0], dirc[1], dirc[2] )
	
	def getSpin(self):
		spin = pylon.object_get_spin_3f( self.simname, self.name )
		return Position( spin[0], spin[1], spin[2] )
	
	
	def setPos(self,pos):
		pylon.object_set_pos_3f( self.simname, self.name, pos.x, pos.y, pos.z )
	
	def setRot(self,rot):
		pylon.object_set_rot_3f( self.simname, self.name, rot.x, rot.y, rot.z )
	
	def setDir(self,dirc):
		pylon.object_set_dir_3f( self.simname, self.name, dirc.x, dirc.y, dirc.z )
	
	def setSpin(self,spin):
		pylon.object_set_spin_3f( self.simname, self.name, spin.x, spin.y, spin.z )
	
	
	def getOptions(self):
		return pylon.object_options( self.simname, self.name, "get option", 0 )
	
	def setOptions(self,option):
		return pylon.object_options( self.simname, self.name, "set option", option )
	
	def addOption(self,option):
		return pylon.object_options( self.simname, self.name, "add option", option )
	
	def removeOption(self,option):
		return pylon.object_options( self.simname, self.name, "rm option", option )
	
	def hasOption(self,option):
		if pylon.object_options( self.simname, self.name, "has option", option ) > 0:
			return True
		return False
	
	def getProperties(self):
		return pylon.object_options( self.simname, self.name, "get property", 0 )
	
	def setProperties(self,option):
		return pylon.object_options( self.simname, self.name, "set property", option )
	
	def addProperty(self,option):
		return pylon.object_options( self.simname, self.name, "add property", option )
	
	def removeProperty(self,option):
		return pylon.object_options( self.simname, self.name, "rm property", option )
	
	def hasProperty(self,option):
		if pylon.object_options( self.simname, self.name, "has property", option ) > 0:
			return True
		return False
	
	
	def setMass(self,mass):
		pylon.object_set_mass( self.simname, self.name, mass )
	
	def getMass(self):
		return pylon.object_get_mass( self.simname, self.name )
	
	
	def setBounce(self,bounce):
		pylon.object_set_bounce( self.simname, self.name, bounce )
	
	def getBounce(self):
		return pylon.object_get_bounce( self.simname, self.name )
	
	
	def setFriction(self,friction):
		pylon.object_set_friction( self.simname, self.name, friction )
	
	def getFriction(self):
		return pylon.object_get_friction( self.simname, self.name )
	
	
	def addPosKey(self,key,time):
		return pylon.object_add_key( self.simname, self.name, "pos", key.x, key.y, key.z, time )
	
	def addRotKey(self,key,time):
		return pylon.object_add_key( self.simname, self.name, "rot", key.x, key.y, key.z, time )
	
	def addScaleKey(self,key,time):
		return pylon.object_add_key( self.simname, self.name, "scale", key.x, key.y, key.z, time )
	
	
	def addAnimation(self,starttime,stoptime,animname):
		return pylon.object_add_animation( self.simname, self.name, starttime, stoptime, animname )
	
	def setAnimation(self,animname):
		return pylon.object_set_animation( self.simname, self.name, animname )
	
	def getAnimationCurrent(self):
		return pylon.object_get_animation( self.simname, self.name )
	
	def hasAnimation(self,animname):
		return pylon.object_has_animation( self.simname, self.name, animname )
	
	def setAnimationStart(self):
		return pylon.object_set_animtime( self.simname, self.name )
	
	def getAnimationLength(self,animname):
		return pylon.object_get_animlen( self.simname, self.name, animname )
	
	def getAnimationRuntime(self):
		return pylon.object_get_animsince( self.simname, self.name )
	
	
	def setCollisionCallBack(self,modname,funcname):
		return pylon.object_callback_set_collfunc( self.simname, self.name, modname, funcname )
	
	def setStepCallBack(self,modname,funcname):
		return pylon.object_callback_set_stepfunc( self.simname, self.name, modname, funcname )
	
	def setHitFilterCallBack(self,modname,funcname):
		return pylon.object_callback_set_hitfilter( self.simname, self.name, modname, funcname )
	
	
	def build(self):
		return pylon.object_build( self.simname, self.name )
	

