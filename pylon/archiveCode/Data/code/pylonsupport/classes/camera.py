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
	
except ImportError:
	print 'Importing failure for the required modules in \"classes.camera.py\".'
	print _pylon.exit(-1)
	quit()


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

