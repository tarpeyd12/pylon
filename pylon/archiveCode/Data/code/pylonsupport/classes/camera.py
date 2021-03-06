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
	
	from pylonclasses import *
	from position import *
	
except ImportError:
	print 'Importing failure for the required modules in \"classes.camera.py\".'
	print _pylon.exit(-1)
	quit()


class Camera:
	def __init__(self,p,r):
		self.posstr = ""#pylon.camera_set_pos_3f( ax, ay, az )
		self.rotstr = ""#pylon.camera_set_rot_3f( bx, by, bz )
		
		self.anglex = 0.0
		self.angley = 0.0
		self.panglex = 0.0
		self.pangley = 0.0
		self.radus = 1.0
		self.pradus = 0.0
		
		#_pos = pylon.camera_get_pos_3f()
		#_rot = pylon.camera_get_rot_3f()
		
		#self.pos = Position( _pos[0], _pos[1], _pos[2] )
		#self.rot = Position( _rot[0], _rot[1], _rot[2] )
		self.pos = p
		self.rot = r
		
		self.center = Position( 0, 0, 0 )
	
	@classmethod
	def makeCopy(cls,other):
		cm = cls(other.pos,other.rot)
		cm.posstr = other.posstr
		cm.rotstr = other.rotstr
		cm.anglex = other.anglex
		cm.angley = other.angley
		cm.panglex = other.panglex
		cm.pangley = other.pangley
		cm.radus = other.radus
		cm.pradus = other.pradus
		cm.center = other.center
		return cm
	
	def mradus(self,amt):
		self.radus = self.radus + amt
	
	def setforcenter(self,cnt,r,ax,ay):
		self.pos.x = cnt.x+float( (self.radus+r) * math.sin(dtr(ax)) * math.sin(dtr(ay)) )
		self.pos.z = cnt.z+float( (self.radus+r) * math.sin(dtr(ax)) * math.cos(dtr(ay)) )
		self.pos.y = cnt.y+float( (self.radus+r) * math.cos(dtr(ax)) )
		self.rot.x = ax-90
		self.rot.y = 180-ay
		self.rot.z = 0.0
	
	def centerset(self):
		self.setforcenter(self.center,self.radus,self.anglex-90+180,360-(self.angley+180))
	
	def getcamstrs(self):
		self.posstr = pylon.camera_set_pos_3f( self.pos.x, self.pos.y, self.pos.z )
		self.rotstr = pylon.camera_set_rot_3f( self.rot.x, self.rot.y, self.rot.z )
	
	def mouserot(self):
		if pylon.mouse_ispressed():
			if pylon.mouse_getbutton() == 0:
				difx = ( pylon.mouse_pos_sx() - pylon.mouse_pos_x() ) * -1
				dify = ( pylon.mouse_pos_sy() - pylon.mouse_pos_y() ) * -1
				self.anglex = ( ( float(dify) / float(pylon.window_height()) ) * 180.0 ) + self.panglex
				self.angley = ( ( float(difx) / float(pylon.window_width())  ) * 360.0 ) + self.pangley
				self.setforcenter(self.center,self.radus,self.anglex-90+180,360-(self.angley+180))
		else:
			self.panglex = self.anglex
			self.pangley = self.angley
		#self.getcamstrs()
		#return self.rotstr
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
				self.setforcenter(self.center,self.radus,self.anglex-90+180,360-(self.angley+180))
		else:
			self.pradus = self.radus
		#self.getcamstrs()
		#return self.posstr
		#if pylon.mouse_ispressed():
		#	if pylon.mouse_getbutton() == 2:
		#		self.posz = float(pylon.mouse_pos_sy() - pylon.mouse_pos_y()) / float(pylon.window_height()) * 100 + self.prevz
		#else:
		#	self.prevz = self.posz
		#self.getcamstrs()
		#return self.posstr
	
	def moveto(self,x,y,z):
		self.pos.x = x
		self.pos.y = y
		self.pos.z = z
		self.getcamstrs()
		return self.posstr
	
	def turnto(self,x,y,z):
		self.rot.x = x
		self.rot.y = y
		self.rot.z = z
		self.getcamstrs()
		return self.rotstr
	
	def moveby(self,x,y,z):
		self.pos.x = self.pos.x + x
		self.pos.y = self.pos.y + y
		self.pos.z = self.pos.z + z
		self.getcamstrs()
		return self.posstr
	
	def turnby(self,x,y,z):
		self.rot.x = self.rot.x + x
		self.rot.y = self.rot.y + y
		self.rot.z = self.rot.z + z
		self.getcamstrs()
		return self.rotstr

