try:
	import calc
	import draw
	import pylon
	import shlex
	
except ImportError:
	print 'Importing failure for the required modules in \"pylonclasses.py\".'
	quit()	

def getstrthing(st):
	if pylon.key_ispressed(pylon.key_last()):
		st = st + str(pylon.key_last())
		a = 0
		while a < 10000000:
			a = a + 1
	return st


def getposcoord(pos,cord):
	my_splitter = shlex.shlex(pos, posix = True)
	my_splitter.whitespace += "{},[]"
	my_splitter.whitespace_split = True
	axis = list(my_splitter)
	return float(axis[cord])

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

	def getcamstrs(self):
		self.posstr = pylon.camera_set_pos_3f( self.posx, self.posy, self.posz )
		self.rotstr = pylon.camera_set_rot_3f( self.rotx, self.roty, self.rotz )
		
	def mouserot(self):
		if pylon.mouse_ispressed():
			if pylon.mouse_getbutton() == 0:
				difx = ( pylon.mouse_pos_sx() - pylon.mouse_pos_x() ) * -1
				dify = ( pylon.mouse_pos_sy() - pylon.mouse_pos_y() ) * -1
				self.rotx = ( ( float(dify) / float(pylon.window_height()) ) * 180.0 ) + self.prevx
				self.roty = ( ( float(difx) / float(pylon.window_width())  ) * 360.0 ) + self.prevy
		else:
			self.prevx = self.rotx
			self.prevy = self.roty
		self.getcamstrs()
		return self.rotstr
		
	def mousepos(self):
		if pylon.mouse_ispressed():
			if pylon.mouse_getbutton() == 2:
				self.posz = float(pylon.mouse_pos_sy() - pylon.mouse_pos_y()) / float(pylon.window_height()) * 100 + self.prevz
		else:
			self.prevz = self.posz
		self.getcamstrs()
		return self.posstr
	
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

class Simulation:
	def __init__(self,name,col):
		self.name = name
		self.collisions = col
		pylon.addsimulation(self.name,col)
		
	def addfile(self,filename):
		objfile = open(filename,'r')
		objfile.seek(0,0)
		lines = objfile.readlines()
		# avoid thrashing
		self.stop()
		a = 0
		while a < 100000:
			a = a + 1
		#get the objects
		line = 0
		for obj in lines:
			line = line + 1
			print self.addobject(obj)
			# avoid thrashing
			a = 0
			while a < 10000:
				a = a + 1
			#if pylon.hasproperty(2):
				#print line
		self.restart()
		return line
			
	def addobject(self,objstr):
		return pylon.addobject(self.name,objstr)
		
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


