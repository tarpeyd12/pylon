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
	from objects import *
	
except ImportError:
	print 'Importing failure for the required modules in \"classes.simulation.py\".'
	print _pylon.exit(-1)
	quit()


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


