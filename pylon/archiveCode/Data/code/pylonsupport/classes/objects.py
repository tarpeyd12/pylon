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
	print 'Importing failure for the required modules in \"classes.objects.py\".'
	print _pylon.exit(-1)
	quit()


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

