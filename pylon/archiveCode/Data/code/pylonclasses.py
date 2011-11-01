try:
	import calc
	import draw
	import pylon
	import shlex
	import thread
	import math
	from threading import *
	"""import pygame
	from pygame import Rect
	from pygame.locals import *"""
	
except ImportError:
	print 'Importing failure for the required modules in \"pylonclasses.py\".'
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

class Camera:
	def __init__(self,ax,ay,az,bx,by,bz):
		self.posstr = pylon.camera_set_pos_3f( ax, ay, az )
		self.rotstr = pylon.camera_set_rot_3f( bx, by, bz )
		self.posx = getposcoord(self.posstr,0)
		self.posy = getposcoord(self.posstr,1)
		self.posz = getposcoord(self.posstr,2)
		self.rotx = getposcoord(self.rotstr,0)
		self.roty = getposcoord(self.rotstr,1)
		self.rotz = getposcoord(self.rotstr,2)
		self.prevx = 0.0
		self.prevy = 0.0
		self.prevz = 0.0
		
		self.anglex = 0.0
		self.angley = 0.0
		self.panglex = 0.0
		self.pangley = 0.0
		self.radus = 1.0
		self.pradus = 0.0
	
	def mradus(self,amt):
		self.radus = self.radus + amt
	
	def setforcenter(self,x,y,z,r,ax,ay):
		self.posx = x+float( (self.radus+r) * math.sin(dtr(ax)) * math.sin(dtr(ay)) )
		self.posz = z+float( (self.radus+r) * math.sin(dtr(ax)) * math.cos(dtr(ay)) )
		self.posy = y+float( (self.radus+r) * math.cos(dtr(ax)) )
		self.rotx = ax-90
		self.roty = 180-ay
		self.rotz = 0.0
	
	def centerset(self):
		self.setforcenter(0,0,0,self.radus,self.anglex-90+180,360-(self.angley+180))
	
	def getcamstrs(self):
		self.posstr = pylon.camera_set_pos_3f( self.posx, self.posy, self.posz )
		self.rotstr = pylon.camera_set_rot_3f( self.rotx, self.roty, self.rotz )
	
	def mouserot(self):
		if pylon.mouse_ispressed():
			if pylon.mouse_getbutton() == 0:
				difx = ( pylon.mouse_pos_sx() - pylon.mouse_pos_x() ) * -1
				dify = ( pylon.mouse_pos_sy() - pylon.mouse_pos_y() ) * -1
				self.anglex = ( ( float(dify) / float(pylon.window_height()) ) * 180.0 ) + self.panglex
				self.angley = ( ( float(difx) / float(pylon.window_width())  ) * 360.0 ) + self.pangley
				self.setforcenter(0,0,0,self.radus,self.anglex-90+180,360-(self.angley+180))
		else:
			self.panglex = self.anglex
			self.pangley = self.angley
		self.getcamstrs()
		return self.rotstr
		#if pylon.mouse_ispressed():
		#	if pylon.mouse_getbutton() == 0:
		#		difx = ( pylon.mouse_pos_sx() - pylon.mouse_pos_x() ) * -1
		#		dify = ( pylon.mouse_pos_sy() - pylon.mouse_pos_y() ) * -1
		#		self.rotx = ( ( float(dify) / float(pylon.window_height()) ) * 180.0 ) + self.prevx
		#		self.roty = ( ( float(difx) / float(pylon.window_width())  ) * 360.0 ) + self.prevy
		#else:
		#	self.prevx = self.rotx
		#	self.prevy = self.roty
		#self.getcamstrs()
		#return self.rotstr
		
	def mousepos(self):
		if pylon.mouse_ispressed():
			if pylon.mouse_getbutton() == 2:
				self.radus = float(pylon.mouse_pos_sy() - pylon.mouse_pos_y()) / float(pylon.window_height()) * -100 + self.pradus
				self.setforcenter(0,0,0,self.radus,self.anglex-90+180,360-(self.angley+180))
		else:
			self.pradus = self.radus
		self.getcamstrs()
		return self.posstr
		#if pylon.mouse_ispressed():
		#	if pylon.mouse_getbutton() == 2:
		#		self.posz = float(pylon.mouse_pos_sy() - pylon.mouse_pos_y()) / float(pylon.window_height()) * 100 + self.prevz
		#else:
		#	self.prevz = self.posz
		#self.getcamstrs()
		#return self.posstr
	
	def moveto(self,x,y,z):
		self.posx = x
		self.posy = y
		self.posz = z
		self.getcamstrs()
		return self.posstr
	
	def turnto(self,x,y,z):
		self.rotx = x
		self.roty = y
		self.rotz = z
		self.getcamstrs()
		return self.rotstr
	
	def moveby(self,x,y,z):
		self.posx = self.posx + x
		self.posy = self.posy + y
		self.posz = self.posz + z
		self.getcamstrs()
		return self.posstr
	
	def turnby(self,x,y,z):
		self.rotx = self.rotx + x
		self.roty = self.roty + y
		self.rotz = self.rotz + z
		self.getcamstrs()
		return self.rotstr


class RunFunctionAsThread(Thread):
	def __init__(self,function, args):
		Thread.__init__(self)
		self.func = function
		self.args = args
	def run(self):
		arguments = self.args
		self.func(*arguments)

class Simulation:
	def __init__(self,name,col):
		self.name = name
		self.collisions = col
		self.adding = False
		pylon.addsimulation(self.name,col)
		print pylon.togglesimweight(self.name,True)
		self.start()
		
	def addfile(self,filename):
		self.adding = True
		objfile = open(filename,'r')
		objfile.seek(0,0)
		lines = objfile.readlines()
		# avoid thrashing
		self.stop()
		a = 0
		while a < 1000:
			a = a + 1
		#get the objects
		line = 0
		for obj in lines:
			line = line + 1
			res = pylon.addobject(self.name,obj)
			# avoid thrashing
			a = 0
			while a < 1000:
				a = a + 1
			if pylon.hasproperty(2):
				print res,line
		a = 0
		while a < 1000:
			a = a + 1
		self.restart()
		self.adding = False
		return line
	
	def _thrd(self,string,filename):
		try:
			self.addfile(filename)
		except IOError as steve:
			print type(steve)
			print pylon.requestfile(filename)
			try:
				self.addfile(filename)
			except:
				print 'Failed!'
	
	def addfilehere(self,filename):
		if not self.adding:
			thrd = RunFunctionAsThread(self._thrd,("thrd",filename))
			thrd.start()
	
	def addobject(self,objstr):
		#self.stop()
		ret = pylon.addobject(self.name,objstr)
		#self.restart()
		return ret
		
	def obj(self,objname):
		return Object(objname,self.name)
		
	def stop(self):
		pylon.togglesim(self.name,False)
		
	def restart(self):
		pylon.togglesim(self.name,True)
		
	def start(self):
		pylon.togglesim(self.name,True)


class Object:
	def __init__(self,name,simname):
		self.name = name
		self.simname = simname
		
	def move(self,pos):
		return pylon.object_move_s(self.simname,self.name,pos)
		
	def move(self,x,y,z):
		return pylon.object_move_3f(self.simname,self.name,x,y,z)
		
	def setdir(self,direct):
		return pylon.object_set_dir_s(self.simname,self.name,direct)
		
	def setdir(self,x,y,z):
		return pylon.object_set_dir_3f(self.simname,self.name,x,y,z)

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

class Quad:
	def __init__(self,x_1,y_1,x_2,y_2,im,vis):
		self.visable = vis
		self.x1 = x_1
		self.y1 = y_1
		self.x2 = x_2
		self.y2 = y_2
		self.image = im
		self.quadID = -5
		if(self.visable == True):
			self.makeVisable()

	def makeVisable(self):
		if(self.quadID < 0):
			idtmp = pylon.addquad(self.x1,self.y1,self.x2,self.y2,self.image)
			if(idtmp >= 0):
				self.quadID = idtmp
				self.visable = True
				if pylon.hasproperty(2):
					print 'new quad with ID: ',idtmp
			else:
				self.quadID = -5
				if pylon.hasproperty(2):
					if(idtmp == -1):
						print 'not a valid quad slot ',idtmp
					elif(idtmp == -3):
						print 'destination slot taken ',idtmp
			return idtmp
		else:
			if pylon.hasproperty(2):
				print 'quad ',self.quadID,' already visable'
		return self.quadID
	
	def makeInvisable(self):
		if(self.quadID >= 0):
			rettmp = pylon.removequad(self.quadID)
			#pylon.removequad(self.quadID)
			if(rettmp < 0):
				if pylon.hasproperty(2):
					print 'cannot remove quad',self.quadID,' for some reason ',rettmp
			else:
				if pylon.hasproperty(2):
					print 'quad to be removed next cycle: ',self.quadID,':',rettmp
				self.quadID = -5
				self.visable = False
			return rettmp
		return 'ok'

	def update(self):
		idtmp = -2
		if self.visable:
			idtmp = pylon.updatequad(self.x1,self.y1,self.x2,self.y2,self.image,self.quadID)
		return idtmp

