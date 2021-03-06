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
	print 'Importing failure for the required modules in \"classes.hud.py\".'
	print _pylon.exit(-1)
	quit()


class Quad:
	def __init__(self,x_1,y_1,x_2,y_2,im):
		self.x1 = x_1
		self.y1 = y_1
		self.x2 = x_2
		self.y2 = y_2
		self.image = im
		self.properties = 0
		self.quadID = -5
		self.quadID = pylon.addquadi(self.x1,self.y1,self.x2,self.y2,self.image,self.properties)
		if self.quadID < 0:
			print 'quad does not exist',self.quadID
	
	def setproperties(self,p):
		self.properties = p
		self.update()
	
	def visable(self):
		ret = pylon.quadgetvis(self.quadID)
		if ret < 0:
			print "ERROR",self.quadID,ret
		return ret
	
	def makeVisable(self):
		if self.quadID >= 0:
			ret = pylon.quadsetvis(self.quadID, True)
			if ret < 0:
				print 'quad does not exist', ret, self.quadID
	
	def makeInvisable(self):
		if self.quadID >= 0:
			ret = pylon.quadsetvis(self.quadID, False)
			if ret < 0:
				print 'quad does not exist', ret, self.quadID

	def update(self):
		idtmp = -2
		if self.visable():
			idtmp = pylon.updatequadi(self.x1,self.y1,self.x2,self.y2,self.image,self.properties,self.quadID)
		return idtmp

