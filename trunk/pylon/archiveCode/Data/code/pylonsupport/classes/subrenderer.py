try:
	import pylon
	import _pylon
	import _pylon_calc
	import _pylon_draw
	
	import shlex
	import math
	
	from pylonclasses import *
	from simulation import *
	from position import *
	from camera import *
	
except ImportError:
	print 'Importing failure for the required modules in \"classes.subrenderer.py\".'
	print _pylon.exit(-1)
	quit()


class SubRenderer(str):
	def __new__( self, tex, ar ):
		return super( SubRenderer, self ).__new__( self, pylon.subrender_new( tex, ar ) )
	
	
	def bindSimulation( self, sim ):
		pylon.subrender_bind_sim( self, sim.name )
	
	def releaseSimulation( self, sim ):
		pylon.subrender_release_sim( self, sim.name )
	
	def releaseAll( self ):
		pylon.subrender_release_all( self )
	
	
	def setLight( self, lightnum, pos, amb, spc, dif, op ):
		pylon.subrender_set_light( self, lightnum, pos.x, pos.y, pos.z, amb, spc, dif, op )
	
	
	def setCamera( self, cam ):
		pylon.subrender_set_cam( self, cam.posx, cam.posy, cam.posz, cam.rotx, cam.roty, cam.rotz )
	
	
	def setRatio( self, ar ):
		pylon.subrender_set_ratio( self, ar )

