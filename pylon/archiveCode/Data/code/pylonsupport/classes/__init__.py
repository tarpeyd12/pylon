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
	
except ImportError as bob:
	print 'Importing failure for the required modules in package \"pylonsuport.classes\".'
	print bob
	print _pylon.exit(-1)
	quit()

__all__ = ["camera","hud","objects","simulation","pylonclasses"]

#__all__ = ["Camera","Quad","Object","Simulation","pylonclasses"]

