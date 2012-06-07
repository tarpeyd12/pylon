# import the stuffs
try:
	import time
	import random
	import math
	
	# normal pylon interface
	#import pylon
	# pylon versions interface
	#import _pylon
	#import _pylon_calc
	#import _pylon_draw
	
	# for comparing the versions
	import shlex
	
	import sys
	
	#sys.path.append('./Data/')
	sys.path.append('./Data/code/')
	
	from pylonsupport.classes import *
	from pylonsupport.classes.camera import *
	from pylonsupport.classes.hud import *
	from pylonsupport.classes.simulation import *
	from pylonsupport.classes.objects import *
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

#declare the 'counter' will be incrimented by 0.1 every script cycle
counter = 0

# setup the camera
cam = Camera(0,0,0,0,0,0)

# declare the way in which the simple object movement example moves objects
movestatetype = 0

# a randomly placed variable
going = True

# random number from -1 to 1
def rnd_n1p1():
	return (random.random() * 2) - 1

# random number from -0.2 to 0.2
def rnd():
	return rnd_n1p1() * 0.2

# loop i number of times
def waitcalc(i):
	time.sleep(i*0.001)

# create objects for the mouse cursor and dragbox
Mouse = Quad(0,0,pylon.mouse_pos_x(),pylon.mouse_pos_y(),'{[Data/images/mouse_pointer.png],[2]}')
ClickLine = Quad(0,0,pylon.mouse_pos_x(),pylon.mouse_pos_y(),'{[Data/images/red_square.bmp],[0]}')
ClickLine.setproperties(32)

# extract some other files
print pylon.requestfile('Data/objectdata/log125_tga.txt')
print pylon.requestfile('Data/worlddata/bob.wld')
print pylon.requestfile('Data/worlddata/Default.wld')

# declare a simulation
sim2 = Simulation("simulation2",True)

# pogel-formated triangle data for a small clear blue hexagon
objtridat = '{[108],{[0.000000000000000000000000000],[0.025000000372529029846191406],[0.000000000000000000000000000],[0.500000],[1.000000],{[0.000000000000000000000000000],[1.000000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000],[0.500000],[0.500000],{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.021650634706020355224609375],[0.012500000186264514923095703],[0.000000000000000000000000000],[0.933013],[0.750000],{[0.866025388240814208984375000],[0.500000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[1.000000000000000000000000000]},{[Data/images/particle.bmp],[32],[32],[1]}},{[108],{[0.021650634706020355224609375],[0.012500000186264514923095703],[0.000000000000000000000000000],[0.933013],[0.750000],{[0.866025388240814208984375000],[0.500000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000],[0.500000],[0.500000],{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.021650634706020355224609375],[-0.012500000186264514923095703],[0.000000000000000000000000000],[0.933013],[0.250000],{[0.866025388240814208984375000],[-0.500000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[1.000000000000000000000000000]},{[Data/images/particle.bmp],[32],[32],[1]}},{[108],{[0.021650634706020355224609375],[-0.012500000186264514923095703],[0.000000000000000000000000000],[0.933013],[0.250000],{[0.866025388240814208984375000],[-0.500000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000],[0.500000],[0.500000],{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000002334529952301],[-0.025000000372529029846191406],[0.000000000000000000000000000],[0.500000],[0.000000],{[0.000000000000093381194703895],[-1.000000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[1.000000000000000000000000000]},{[Data/images/particle.bmp],[32],[32],[1]}},{[108],{[0.000000000000002334529952301],[-0.025000000372529029846191406],[0.000000000000000000000000000],[0.500000],[0.000000],{[0.000000000000093381194703895],[-1.000000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000],[0.500000],[0.500000],{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[-0.021650634706020355224609375],[-0.012500000186264514923095703],[0.000000000000000000000000000],[0.066987],[0.250000],{[-0.866025388240814208984375000],[-0.500000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[1.000000000000000000000000000]},{[Data/images/particle.bmp],[32],[32],[1]}},{[108],{[-0.021650634706020355224609375],[-0.012500000186264514923095703],[0.000000000000000000000000000],[0.066987],[0.250000],{[-0.866025388240814208984375000],[-0.500000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000],[0.500000],[0.500000],{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[-0.021650634706020355224609375],[0.012500000186264514923095703],[0.000000000000000000000000000],[0.066987],[0.750000],{[-0.866025388240814208984375000],[0.500000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[1.000000000000000000000000000]},{[Data/images/particle.bmp],[32],[32],[1]}},{[108],{[-0.021650634706020355224609375],[0.012500000186264514923095703],[0.000000000000000000000000000],[0.066987],[0.750000],{[-0.866025388240814208984375000],[0.500000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000],[0.500000],[0.500000],{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[-0.000000000000004669059904601],[0.025000000372529029846191406],[0.000000000000000000000000000],[0.500000],[1.000000],{[-0.000000000000186762389407791],[1.000000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[-0.000000000000000000000000000],[0.000000000000000000000000000],[1.000000000000000000000000000]},{[Data/images/particle.bmp],[32],[32],[1]}}'

# pogel-formated data for a solid object header with triangle data, without the name
objdat = '],[22],[136],[0],[0],{[2.187638521194458007812500000],[-164.624237060546875000000000000],[-47.653999328613281250000000000]},{[179.100006103515625000000000000],[125.449783325195312500000000000],[0.000000000000000000000000000]},{[0.000212223967537283897399902],[-0.012018831446766853332519531],[-0.003399600507691502571105957]},{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000]},{[1.000000],[0.750000],[5000.000000],[1.000000],[1.000000],[1.000000],[0],[-1.000000]},<'+objtridat+'>}'

# create an object data string with name: 'sphere0'
sph0dat = '{[sphere0'+objdat

# add object to  simulation sim2
#sim2.addobject(sph0dat)

# retreive object instance for object 'sphere0'
sphere0 = sim2.obj("sphere0")

# turn off object-to-object gravitation
#print pylon.togglesimweight(sim2.name,False)

# create collidable simulation 'sim'
sim = Simulation("sim",True)

zeropos = makepos(0,0,0)

possibleImages = '{[Data/images/earth.bmp],[2]}', '{[Data/images/Glass.bmp],[2]}', '{[Data/images/lava8.bmp],[2]}', '{[Data/images/mandel_2.png],[1]}', '{[Data/images/pogel_runner_galax_color_1.png],[2]}', '{[Data/images/default_2.bmp],[0]}', '{[Data/images/mouse_pointer.png],[0]}'
possibleTriProps = 8, 8|32|64, 8, 8, 8, 2, 8|64
#possibleTriProps = 8, 8, 8, 8, 8, 2, 8

def makeObjectString(vect1,vect2,vect3,vect4,name,p1,p2,mass,tridat):
	return '{['+str(name)+'],['+str(p1)+'],['+str(p2)+'],[0],[0],'+vect1+','+vect2+','+vect3+','+vect4+',{[0.5],[0.25],['+str(float(mass))+'],[1.0],[1.0],[1.0],[0],[-1.0]},<'+tridat+'>}'

if True:
	loop = 0
	loopmax = 10
	mass = 5
	maxrad = 1
	minrad = 0.5
	numOSpheres = 10
	while loop < numOSpheres:
		sc1 = 1.5
		#rpos = makepos(rnd_n1p1()*sc1*0, float(loop)/5.0+.01-(numOSpheres/5.0/2), rnd_n1p1()*sc1*0)
		rpos = makepos(rnd_n1p1()*sc1, rnd_n1p1()*sc1, rnd_n1p1()*sc1)	
		rot = makepos(rnd_n1p1()*360,rnd_n1p1()*360,rnd_n1p1()*360)
		print "\nstart Object"+str(loop)
		print sim2.addobject( makeObjectString(rpos,rot,zeropos,zeropos,"Object"+str(loop),2|4|16,8,20000,"") )
		print 'add'
		rnum = 1 #int(random.random()*7)
		print pylon.object_add_sphere(sim2.name,"Object"+str(loop),.25,10,10,possibleImages[rnum],1,1,possibleTriProps[rnum])
		print 'ball'
		pylon.callback_set_collfunc(sim2.name,"Object"+str(loop),"game","collisionfunction1")
		pylon.callback_set_stepfunc(sim2.name,"Object"+str(loop),"game","stepfunction1")
		pylon.callback_set_hitfilter(sim2.name,"Object"+str(loop),"game","hitfilter1")
		#if rnum == 6 or rnum == 1:
			#pylon.object_options(sim2.name,"Object"+str(loop),"add option",64)
		print pylon.object_build(sim2.name,"Object"+str(loop))
		#print 'build'
		loop = loop + 1

print pylon.setsimulationcollitters(sim2.name,3)

cam.radus = 2

TestSphereSim = Simulation("TestSphereSim",True)

loop = 0
rnum = 0
numOSpheres = 10
while loop < numOSpheres:
	sc1 = 1.5
	#rpos = makepos(rnd_n1p1()*sc1*0, float(loop)/5.0+.01-(numOSpheres/5.0/2), rnd_n1p1()*sc1*0)
	rpos = makepos(rnd_n1p1()*sc1, rnd_n1p1()*sc1, rnd_n1p1()*sc1*0)
	rot = makepos(rnd_n1p1()*360,rnd_n1p1()*360,rnd_n1p1()*360)
	print "\nstart Object"+str(loop)
	print TestSphereSim.addobject( makeObjectString(rpos,rot,zeropos,zeropos,"Object"+str(loop),2|4|16,8,0.02,"") )
	print 'add'
	rnum = 6 #int(random.random()*7)
	print pylon.object_add_sphere("TestSphereSim","Object"+str(loop),0.07,10,10,possibleImages[rnum],1,1,possibleTriProps[rnum])
	print 'ball'
	print pylon.object_build("TestSphereSim","Object"+str(loop))
	#pylon.object_set_visibility("TestSphereSim","Object"+str(loop),False)
	print 'build'
	loop = loop + 1

#print pylon.object_set_dir_3f("TestSphereSim","Object0",0,0.02,0)
#print pylon.object_set_dir_3f("TestSphereSim","Object1",0,0.02,0)
#print pylon.object_set_dir_3f("TestSphereSim","Object2",0,0.02,0)
#print pylon.object_set_dir_3f("TestSphereSim","Object3",0,0.02,0)

rnum = 5
print TestSphereSim.addobject( makeObjectString(zeropos,zeropos,zeropos,zeropos,"Outset",1|8|16,8,0,"") )
#print pylon.object_add_sphere("TestSphereSim","Outset",2.0,20,20,possibleImages[rnum],1,1,possibleTriProps[rnum]|64)
print pylon.object_add_sphere("TestSphereSim","Outset",2.0,20,20,possibleImages[rnum],1,1,possibleTriProps[rnum]|16)
#if rnum!=6 and not False:
#print pylon.object_add_sphere("TestSphereSim","Outset",2.0,20,20,possibleImages[rnum],1,1,possibleTriProps[rnum]|32)
#print pylon.object_add_sphere("TestSphereSim","Outset",2.1,20,20,'{[Data/images/earthcloudmap.png],[2]}',1,1,8|32)
#pylon.object_set_spin_3f("TestSphereSim","Outset",0,10,0)
print pylon.object_build("TestSphereSim","Outset")

#print TestSphereSim.addobject( makeObjectString(zeropos,zeropos,zeropos,zeropos,"Aura",1|8|16,128,0,"") )
#print pylon.object_add_disk("TestSphereSim","Aura",40,1,4.0,2.0,possibleImages[5],1,1,0,True)
#print pylon.object_build("TestSphereSim","Aura")

print pylon.setsimulationgravity_3f("TestSphereSim",0,-9.8,0)

print pylon.setsimulationcollitters("TestSphereSim",3)
print pylon.togglesimweight("TestSphereSim",False)

rnum = 3
print sim2.addobject( makeObjectString(zeropos,zeropos,zeropos,zeropos,"Outset",1|8|16,8,0,"") )
print pylon.object_add_sphere(sim2.name,"Outset",2.0,20,20,possibleImages[rnum],1,1,possibleTriProps[rnum]|16)
print pylon.object_build(sim2.name,"Outset")
pylon.object_set_visibility(sim2.name,"Outset",False)

subrenderer1 = pylon.subrender_new("steve",float(pylon.window_width())/float(pylon.window_height()))
pylon.subrender_bind_sim(subrenderer1, sim2.name)

Bloop = Quad(0,pylon.window_height(),pylon.window_width(),0,subrenderer1)
#Bloop.setproperties(32)
#Bloop.makeInvisable()

#print "setting light"
#pylon.subrender_set_light(subrenderer1, 0, 0,0,-50, "{[0.28],[0.333],[0.38],[1.0]}","{[0.855],[0.55],[0.15],[1.0]}","{[0.925],[0.925],[0.0],[1.0]}",False)
#print "light set"



Animation = Simulation("AnimationSimulation",True)
animationname = "beast"
animationfilename = "Data/objectdata/"+animationname+".ms3d"
pylon.requestfile(animationfilename)

animscale = 0.01

if pylon.object_new_fromfile( Animation.name, animationname, animationfilename, "ms3d") != 0:
	print 'failed to load object file, exiting'
	print _pylon.exit(0)
	quit()
pylon.object_add_key(Animation.name,animationname, "scale", animscale,animscale,animscale,0.0)
#pylon.object_options(Animation.name,animationname,"add property",64)
pylon.object_options(Animation.name,animationname,"add option",1)
pylon.object_set_bounce(Animation.name,animationname,0.0)
pylon.object_set_mass(Animation.name,animationname,0.1)
pylon.object_add_animation(Animation.name,animationname,1.0,25.0-1,"Walk")
pylon.object_add_animation(Animation.name,animationname,25.0-1,1.0,"WalkReverse")
pylon.object_add_animation(Animation.name,animationname,71.0,80.0-1,"ToWalk")
pylon.object_add_animation(Animation.name,animationname,82.0,100.0-1,"Jump")
pylon.object_add_animation(Animation.name,animationname,332.0,380.0-1,"Idle")
pylon.object_add_animation(Animation.name,animationname,152.0,180.0-1,"Look")
pylon.object_add_animation(Animation.name,animationname,122.0,150.0-1,"Rear")
pylon.object_set_animation(Animation.name,animationname,"Idle")
pylon.object_set_animtime(Animation.name,animationname)
print pylon.object_build(Animation.name,animationname)
pylon.object_move_3f(Animation.name,animationname, 0, 0, 0)



objimportsim = Simulation("ObjectImportSimulation",False)
objimportname = "lamp"
objimportsimfilename = "Data/objectdata/"+objimportname+".obj"
pylon.requestfile(objimportsimfilename)
pylon.requestfile("Data/objectdata/"+objimportname+".mtl")

if pylon.object_new_fromfile( objimportsim.name, objimportname, objimportsimfilename, "objmtl" ) != 0:
	print 'failed to load object file, exiting'
	print _pylon.exit(0)
	quit()
pylon.object_add_key(objimportsim.name,objimportname, "scale", animscale,animscale,animscale,0.0)
#pylon.object_options(objimportsim.name,objimportname,"add property",64)
pylon.object_options(objimportsim.name,objimportname,"add option",1)
pylon.object_set_bounce(objimportsim.name,objimportname,0.0)
pylon.object_set_mass(objimportsim.name,objimportname,0.1)
print pylon.object_build(objimportsim.name,objimportname)
pylon.object_move_3f(objimportsim.name,objimportname, 0, 0, 0)
pylon.object_set_rot_3f(objimportsim.name,objimportname, -90, 90, 0)


loop = 0
rnum = 0
numOSpheres = 10
while loop < numOSpheres:
	sc1 = 1.5
	#rpos = makepos(rnd_n1p1()*sc1*0, float(loop)/5.0+.01-(numOSpheres/5.0/2), rnd_n1p1()*sc1*0)
	rpos = makepos(rnd_n1p1()*sc1, rnd_n1p1()*sc1-2, rnd_n1p1()*sc1)
	rot = makepos(rnd_n1p1()*360,rnd_n1p1()*360,rnd_n1p1()*360)
	print "\nstart Object"+str(loop)
	print Animation.addobject( makeObjectString(rpos,rot,zeropos,zeropos,"Object"+str(loop),2|4|16,8,0.02,"") )
	print 'add'
	rnum = 5
	print pylon.object_add_sphere(Animation.name,"Object"+str(loop),0.07,10,10,possibleImages[rnum],1,1,possibleTriProps[rnum])
	print 'ball'
	print pylon.object_build(Animation.name,"Object"+str(loop))
	print 'build'
	loop = loop + 1

rnum = 3
print Animation.addobject( makeObjectString(zeropos,zeropos,zeropos,zeropos,"Outset",1|8|16,8|64,0,"") )
print pylon.object_add_sphere(Animation.name,"Outset",2.0,20,20,possibleImages[rnum],1,1,possibleTriProps[rnum]|16)
pylon.object_set_visibility(Animation.name,"Outset",False)
print pylon.object_build(Animation.name,"Outset")

print pylon.setsimulationgravity_3f(Animation.name,0,-9.8,0)
print pylon.setsimulationcollitters(Animation.name,3)
print pylon.togglesimweight(Animation.name,False)

Sky = Simulation("Sky",False)
print Sky.addobject( makeObjectString(zeropos,zeropos,zeropos,zeropos,"Sky",1|8|16,8,0,"") )
print pylon.object_add_sphere(Sky.name,"Sky",750.0,20,20,"{[Data/images/sky/Sky_horiz_"+str(int(random.random()*11+1))+"_2048.jpg],[0]}",2,1,0|16)
print pylon.object_build(Sky.name,"Sky")
#print pylon.object_set_visibility(Sky.name,"Sky",False)
#print pylon.setsimulationcollitters(Sky.name,0)
#print pylon.togglesimweight(Sky.name,False)
print Sky.stop()

relocateobjscounter = 0

numOSpheres = 10

def doOBJECTrelocate():
	#pass
	global relocateobjscounter
	relocateobjscounter += 1
	if relocateobjscounter%2 == 1:
		return
	c = int((counter/2)*1.0)%numOSpheres
	oname = "Object"+str(c)
	sc1 = 0.025
	rpos = makepos(rnd_n1p1()*sc1, rnd_n1p1()*sc1, rnd_n1p1()*sc1)
	pylon.object_set_pos_s("TestSphereSim",oname,rpos)
	pylon.object_set_dir_3f("TestSphereSim",oname,0.025*20,0.15*20,0)
	
	sc1 = 0.25
	rpos = makepos(rnd_n1p1()*sc1, rnd_n1p1()*sc1+1.5, rnd_n1p1()*sc1)
	pylon.object_set_pos_s(Animation.name,oname,rpos)
	pylon.object_set_dir_3f(Animation.name,oname,0,0,0)

previouslastkey = '1'
lastkey = '2'

waitcalc(1000)

