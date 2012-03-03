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
	def __init__(self,x_1,y_1,x_2,y_2,im,vis):
		self.visable = vis
		self.x1 = x_1
		self.y1 = y_1
		self.x2 = x_2
		self.y2 = y_2
		self.image = im
		self.properties = 0
		self.quadID = -5
		if(self.visable == True):
			self.makeVisable()
	
	def setproperties(self,p):
		self.properties = p
	
	def makeVisable(self):
		if(self.quadID < 0):
			idtmp = pylon.addquadi(self.x1,self.y1,self.x2,self.y2,self.image,self.properties)
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
			idtmp = pylon.updatequadi(self.x1,self.y1,self.x2,self.y2,self.image,self.properties,self.quadID)
		return idtmp

