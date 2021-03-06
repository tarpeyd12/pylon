# import the stuffs
try:
	import time
	import random
	import math
	
	# normal pylon interface
	import pylon
	# pylon versions interface
	import _pylon
	import _pylon_calc
	import _pylon_draw
	
	# for comparing the versions
	import shlex
	
	import sys
	
	#sys.path.append('./Data/')
	sys.path.append('./Data/code/')
	
	#from pylonsupport.classes import *
	from pylonsupport.classes.camera import *
	from pylonsupport.classes.hud import *
	from pylonsupport.classes.simulation import *
	from pylonsupport.classes.objects import *
	from pylonsupport.classes.subrenderer import *
	from pylonsupport.classes.pylonclasses import *
	import game
			
except ImportError as bob:
	# complete failure:
	print 'ERROR: Master import failure'
	print '       Importing failure for the required modules in \"init.py\".'
	print bob
	print 'Exiting ...'
	# exit cleanly
	print _pylon.exit(-1)
	quit()

# the main Initialization things ...

NumInitObjs = 5

#declare the 'counter' will be incrimented by 0.1 every script cycle
counter = 0

# setup the camera
cam = Camera( Position( 0, 0, 0 ), Position( 0, 0, 0 ) )

# declare the way in which the simple object movement example moves objects
movestatetype = 0

# a randomly placed variable
going = True

# random number from -1 to 1
def rnd_n1p1():
	return (random.random() * 2) - 1

# create objects for the mouse cursor and dragbox
Mouse = Quad(0,0,pylon.mouse_pos_x(),pylon.mouse_pos_y(),'{[Data/images/mouse_pointer.png]}')
ClickLine = Quad(0,0,pylon.mouse_pos_x(),pylon.mouse_pos_y(),'{[Data/images/red_square.bmp]}')
ClickLine.setproperties( pylon.triangle_transparent )

# declare a simulation
sim2 = Simulation("simulation2",True)

# create collidable simulation 'sim'
sim = Simulation("sim",True)

zeropos = makepos(0,0,0)

possibleImages = [ '{[Data/images/earth.bmp]}', '{[Data/images/Glass.bmp]}', '{[Data/images/lava8.bmp]}', '{[Data/images/mandel_2.png]}', '{[Data/images/pogel_runner_galax_color_1.png]}', '{[Data/images/default_2.bmp]}', '{[Data/images/mouse_pointer.png]}' ]

tvn = pylon.triangle_vertex_normals
tlt = pylon.triangle_lit
tcl = pylon.triangle_transparent
tdb = pylon.triangle_doublesided

possibleTriProps = [ tvn, tvn|tcl|tdb, tvn, tvn, tvn, tlt, tvn|tdb ]

if True:
	loop = 0
	mass = 5
	maxrad = 1
	minrad = 0.5
	numOSpheres = NumInitObjs
	while loop < numOSpheres:
		positionrange = 1.5
		rpos = Position(rnd_n1p1(),rnd_n1p1(),rnd_n1p1()) * positionrange
		rot  = Position(rnd_n1p1(),rnd_n1p1(),rnd_n1p1()) * 360.0
		currentObject = sim2.newObject( "Object"+str(loop) )
		currentObject.setPos(rpos)
		currentObject.setRot(rot)
		currentObject.setMass(20000)
		currentObject.setBounce(0.25)
		currentObject.setFriction(0.5)
		currentObject.setOptions( pylon.solid_volatile | pylon.solid_convex | pylon.solid_sphere )
		currentObject.setProperties( pylon.object_draw_children )
		rnum = 1
		print pylon.object_add_sphere( currentObject.simname, currentObject.name, .25, 10, 10, possibleImages[rnum], 1, 1, possibleTriProps[rnum] )
		currentObject.setCollisionCallBack( "game", "collisionfunction1" )
		currentObject.setStepCallBack( "game", "stepfunction1" )
		currentObject.setHitFilterCallBack( "game", "hitfilter1" )
		currentObject.build()
		loop = loop + 1

sim2.setCollisionIterations( 3 )

cam.radus = 2

TestSphereSim = Simulation("TestSphereSim",True)

loop = 0
rnum = 0
numOSpheres = NumInitObjs
while loop < numOSpheres:
	positionrange = 1.5
	rpos = Position(rnd_n1p1(),rnd_n1p1(),rnd_n1p1()) * positionrange
	rot  = Position(rnd_n1p1(),rnd_n1p1(),rnd_n1p1()) * 360.0
	currentObject = TestSphereSim.newObject( "Object"+str(loop) )
	currentObject.setPos(rpos)
	currentObject.setRot(rot)
	currentObject.setMass(.02)
	currentObject.setBounce(0.25)
	currentObject.setFriction(0.5)
	currentObject.setOptions( pylon.solid_volatile | pylon.solid_convex | pylon.solid_sphere )
	currentObject.setProperties( pylon.object_draw_children )
	rnum = 6
	print pylon.object_add_sphere( currentObject.simname, currentObject.name, .07, 10, 10, possibleImages[rnum], 1, 1, possibleTriProps[rnum] )
	currentObject.build()
	loop = loop + 1

subrenderer1 = SubRenderer( "steve", float(pylon.window_width())/float(pylon.window_height()) )
subrenderer1.bindSimulation(sim2)

rnum = 5
TestSphereOutset = TestSphereSim.newObject("Outset")
TestSphereOutset.setOptions( pylon.solid_stationary | pylon.solid_concave | pylon.solid_sphere )
#TestSphereOutset.setProperties( pylon.object_draw_children )
#TestSphereOutset.setProperties( pylon.object_debug )
TestSphereOutset.setProperties( 0 )
pylon.object_add_sphere( TestSphereOutset.simname, TestSphereOutset.name, 2.0, 20, 20, possibleImages[rnum], 1, 1, possibleTriProps[rnum]|pylon.triangle_invert_normals )
#pylon.object_add_sphere( TestSphereOutset.simname, TestSphereOutset.name, 2.0, 20, 20, possibleImages[rnum], 1, 1, possibleTriProps[rnum]|pylon.triangle_doublesided )

#pylon.object_add_sphere( TestSphereOutset.simname, TestSphereOutset.name, 2.0, 20, 20, subrenderer1, 1, 1, possibleTriProps[rnum]|pylon.triangle_invert_normals )
TestSphereOutset.build()

TestSphereSim.setGravityVector( Position( 0, -9.8, 0 ) )
TestSphereSim.setCollisionIterations( 3 )
TestSphereSim.newtonianGravityOff()

rnum = 3
sim2Outset = sim2.newObject("sim2Outset_0.0")
sim2Outset.setOptions( pylon.solid_stationary | pylon.solid_concave | pylon.solid_sphere )
#sim2Outset.setProperties( pylon.object_draw_children )
#sim2Outset.setProperties( pylon.object_debug )
sim2Outset.setProperties( 0 )
pylon.object_add_sphere( sim2Outset.simname, sim2Outset.name, 1.5, 20, 20, possibleImages[rnum], 1, 1, possibleTriProps[rnum]|pylon.triangle_invert_normals )
sim2Outset.setInvisible()
sim2Outset.build()

#subrenderer1 = pylon.subrender_new("steve",float(pylon.window_width())/float(pylon.window_height()))
#pylon.subrender_bind_sim( subrenderer1, sim2.name )

Bloop = Quad( 0, pylon.window_height(), pylon.window_width(), 0, subrenderer1 )
#Bloop.setproperties( pylon.triangle_transparent )
Bloop.makeInvisable()

animscale = 0.01

AnimationSim = Simulation("AnimationSimulation",True)
animationname = "beast"
#animationfilename = "Data/objectdata/"+animationname+".ms3d"
#pylon.requestfile(animationfilename)

pylon.requestfile("Data/objects/beast.pylon")

print "making beast"

#pylon.object_new_fromfile( AnimationSim.name, "beast", "Data/objects/beast.pylon", "pylon" )
Beast = AnimationSim.newObjectFromFile( animationname, "Data/objects/beast.pylon", "pylon" )
Beast.build()

#Beast = AnimationSim.newObjectFromFile( animationname, animationfilename, "ms3d" )
#Beast.addScaleKey( Position(1,1,1)*animscale, 0.0 )
#Beast.setProperties( 0 )
#Beast.setOptions( pylon.solid_stationary )
#Beast.setMass( 0.1 )
#Beast.setBounce( 0.0 )
#Beast.addAnimation(1.0,25.0-1,"Walk")
#Beast.addAnimation(25.0-1,1.0,"WalkReverse")
#Beast.addAnimation(71.0,80.0-1,"ToWalk")
#Beast.addAnimation(82.0,100.0-1,"Jump")
#Beast.addAnimation(332.0,380.0-1,"Idle")
#Beast.addAnimation(152.0,180.0-1,"Look")
#Beast.addAnimation(122.0,150.0-1,"Rear")
#Beast.setAnimation("Idle")
#Beast.setAnimationStart()
#Beast.build()
Beast.setPos( Position(0,0,0) )
#Beast.setInvisible()


ObjectImportSimulation = Simulation("ObjectImportSimulation",False)
objimportname = "lamp"
objimportsimfilename = "Data/objectdata/"+objimportname+".obj"
pylon.requestfile(objimportsimfilename)
pylon.requestfile("Data/objectdata/"+objimportname+".mtl")

Lamp = ObjectImportSimulation.newObjectFromFile( objimportname, objimportsimfilename, "objmtl" )
Lamp.addScaleKey( Position(1,1,1)*animscale, 0.0 )
#Lamp.setProperties( pylon.object_sort_triangles )
Lamp.setOptions( pylon.solid_stationary )
Lamp.setMass( 0.1 )
Lamp.setBounce( 0.0 )
Lamp.build()
Lamp.setPos( Position(0,0,0) )
Lamp.setRot( Position(-90,90,0) )

ObjectImportSimulation.stop()

#pylon.requestfile("Data/objects/tree.pylon")
#Tree = ObjectImportSimulation.newObjectFromFile( "Tree", "Data/objects/tree.pylon", "pylon" )
#Tree.build()
#print "Tree built =)"

loop = 0
rnum = 0
numOSpheres = NumInitObjs
while loop < numOSpheres:
	
	positionrange = 1.5
	rpos = Position(rnd_n1p1(),rnd_n1p1(),rnd_n1p1()) * positionrange
	rpos.y -= 2
	rot  = Position(rnd_n1p1(),rnd_n1p1(),rnd_n1p1()) * 360.0
	print "new object ","Object"+str(loop)
	currentObject = AnimationSim.newObject( "Object"+str(loop) )
	print " created object"
	currentObject.setPos(rpos)
	currentObject.setRot(rot)
	currentObject.setMass(.02)
	currentObject.setBounce(0.25)
	currentObject.setFriction(0.5)
	currentObject.setOptions( pylon.solid_volatile | pylon.solid_convex | pylon.solid_sphere )
	currentObject.setProperties( pylon.object_draw_children )
	rnum = 5
	print pylon.object_add_sphere( currentObject.simname, currentObject.name, .07, 10, 10, possibleImages[rnum], 1, 1, possibleTriProps[rnum] )
	currentObject.build()
	loop = loop + 1

rnum = 3

AnimationSimOutset = AnimationSim.newObject("Outset")
AnimationSimOutset.setOptions( pylon.solid_stationary|pylon.solid_concave|pylon.solid_sphere )
AnimationSimOutset.setProperties( pylon.object_draw_children|pylon.object_sort_triangles )
pylon.object_add_sphere(AnimationSimOutset.simname,AnimationSimOutset.name,2.0,20,20,possibleImages[rnum],1,1,possibleTriProps[rnum]|pylon.triangle_invert_normals)
AnimationSimOutset.setInvisible()
AnimationSimOutset.build()

AnimationSim.setGravityVector( Position(0,-9.8,0) )
AnimationSim.setCollisionIterations( 3 )
AnimationSim.newtonianGravityOff()

SkySim = Simulation("Sky",False)
Sky = SkySim.newObject("Sky")
Sky.setOptions( pylon.solid_stationary|pylon.solid_concave|pylon.solid_sphere )
#Sky.setProperties( pylon.object_draw_children )
pylon.object_add_sphere(Sky.simname,Sky.name,750.0,20,20,"{[Data/images/sky/Sky_horiz_"+str(int(random.random()*11+1))+"_2048.jpg]}",2,1,pylon.triangle_invert_normals)
Sky.build()
#SkySim.stop()

pylon.requestfile("Data/objects/earth.pylon")

Earth = SkySim.newObjectFromFile( "earth", "Data/objects/earth.pylon", "pylon" )
#Earth.setSpin( Position(0,10.0,0) )
Earth.setPos( Position(0,-1,0) )
#Earth.setProperties( pylon.object_debug )
Earth.build()

relocateobjscounter = 0

numOSpheres = NumInitObjs

def doOBJECTrelocate():
	#pass
	global relocateobjscounter
	relocateobjscounter += 1
	if relocateobjscounter%2 == 1:
		return
	c = int((counter/2)*1.0)%numOSpheres
	oname = "Object"+str(c)
	sc1 = 0.025
	currentObject = TestSphereSim.getObject(oname)
	currentObject.setPos( Position(rnd_n1p1(),rnd_n1p1(),rnd_n1p1()) * sc1 )
	currentObject.setDir( Position( 0.025*20,0.15*20,0 ) )
	
	sc1 = 0.25
	currentObject = AnimationSim.getObject(oname)
	rpos = Position(rnd_n1p1(), rnd_n1p1(), rnd_n1p1())*sc1 + Position(0,1.5,0)
	currentObject.setPos( rpos )
	currentObject.setDir( Position( 0,0,0 ) )

previouslastkey = '1'
lastkey = '2'

# controlling the pylon internal calculation thread
def keyfunc1( key, mx, my, tm ):
	# the exiting condition
	if chr(27) == key:
		print _pylon.exit( 0 )
	if key == '\r' or key == '\n':
		global going
		if going:
			print "Stopping Physics Calculation Thread"
			going = False
			_pylon_calc.lock()
		else:
			print "Starting Physics Calculation Thread"
			going = True
			_pylon_calc.unlock()
	
	if key == 'o':
		sim2.halt()
		l = 0
		while l < 10:
			#pylon.wait_sec_f(1.0/25.0)
			positionrange = 1.5
			rpos = Position(rnd_n1p1(),rnd_n1p1(),rnd_n1p1()) * positionrange
			rot  = Position(rnd_n1p1(),rnd_n1p1(),rnd_n1p1()) * 360.0
			currentObject = sim2.newObject( "Object_"+str(pylon.get_runtime()) )
			currentObject.setPos(rpos)
			currentObject.setRot(rot)
			currentObject.setMass(20000)
			currentObject.setBounce(0.25)
			currentObject.setFriction(0.5)
			currentObject.setOptions( pylon.solid_volatile | pylon.solid_convex | pylon.solid_sphere )
			currentObject.setProperties( pylon.object_draw_children )
			rnum = 1
			print pylon.object_add_sphere( currentObject.simname, currentObject.name, .25, 10, 10, possibleImages[rnum], 1, 1, possibleTriProps[rnum] )
			currentObject.setCollisionCallBack( "game", "collisionfunction1" )
			currentObject.setStepCallBack( "game", "stepfunction1" )
			currentObject.setHitFilterCallBack( "game", "hitfilter1" )
			currentObject.build()
			l += 1
		sim2.resume()
	
	if key == ',':
		#if pylon.sim_remove_object( sim2Outset.simname, sim2Outset.name ):
			#print " AKHBSDjkHAKJJSD"
		#sim2.halt()
		print "clearing sim2"
		if sim2.clearAllObjects():
			print "cannot clear sim2"
	
	if key == 'v':
		global sim2Outset
		sim2Outset.setVisible()

def keyfunc2( key, mx, my, tm ):
	if chr(27) == key:
		print _pylon.exit( 0 )
		
	global sim2Outset
	global sim2
	
	if key == ',':
		#pylon.wait_sec_f(10.0/25.0)
		#sim2.stop()
		rnum = 3
		sim2Outset = None
		print "'simulation2' =  ",pylon.sim_num_objects( "simulation2" )
		#while pylon.sim_num_objects( "simulation2" ) > 0:
			#print "'simulation2' =  ",pylon.sim_num_objects( "simulation2" )
			#pylon.wait_sec_f(0.1)
		sim2Outset = sim2.newObject("sim2Outset_"+str(tm))
		sim2Outset.setOptions( pylon.solid_stationary | pylon.solid_concave | pylon.solid_sphere )
		#sim2Outset.setProperties( pylon.object_draw_children )
		#sim2Outset.setProperties( pylon.object_debug )
		sim2Outset.setProperties( 0 )
		pylon.object_add_sphere( sim2Outset.simname, sim2Outset.name, 1.5, 20, 20, possibleImages[rnum], 1, 1, possibleTriProps[rnum]|pylon.triangle_invert_normals )
		sim2Outset.setVisibility(pylon.key_ispressed('v'))
		#sim2Outset.setInvisible()
		#sim2Outset.setVisible()
		sim2Outset.build()
		#sim2.resume()
	
	if key == 'v':
		sim2Outset.setInvisible()

def keyfunc3( key, mx, my, tm ):
	global sim2Outset
	if key == 'l':
		if pylon.sim_remove_object( sim2Outset.simname, sim2Outset.name ):
			print " AKHBSDjkHAKJJSD"
		rnum = 3
		sim2Outset = None
		while sim2Outset == None:
			sim2Outset = sim2.newObject("sim2Outset_"+str(tm))
		sim2Outset.setOptions( pylon.solid_stationary | pylon.solid_concave | pylon.solid_sphere )
		sim2Outset.setProperties( 0 )
		pylon.object_add_sphere( sim2Outset.simname, sim2Outset.name, 1.5, 20, 20, possibleImages[rnum], 1, 1, possibleTriProps[rnum]|pylon.triangle_invert_normals )
		sim2Outset.setVisibility(pylon.key_ispressed('v'))
		sim2Outset.build()

keyfunc1index = pylon.key_callback_add_downfunc("","keyfunc1")
print keyfunc1index
print pylon.key_callback_remove_downfunc(keyfunc1index)

pylon.key_callback_add_downfilters( pylon.key_callback_add_downfunc("","keyfunc1"), "\r\no,v"+str(chr(27)) )

pylon.key_callback_add_upfilters( pylon.key_callback_add_upfunc("","keyfunc2"), ",v"+str(chr(27)) )

pylon.key_callback_add_upfilters( pylon.key_callback_add_upfunc("","keyfunc3"), "l" )

