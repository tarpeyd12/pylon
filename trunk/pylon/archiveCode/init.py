# import the stuffs
try:
	import time
	import random
	import math
	
	# normal pylon interface
	import pylon
	# pylon versions interface
	import _pylon
	
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

#declare the 'counter' will be incrimented by 0.1 evert script cycle
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

# extract images for the mouse cursor and dragbox
print pylon.requestfile('Data/images/particle.tga')
print pylon.requestfile('Data/images/mouse_pointer.png')

# create objects for the mouse cursor and dragbox
ClickLine = Quad(0,0,pylon.mouse_pos_x(),pylon.mouse_pos_y(),'{[Data/images/default_2.bmp],[2]}',True)
Mouse = Quad(0,0,pylon.mouse_pos_x(),pylon.mouse_pos_y(),'{[Data/images/mouse_pointer.png],[2]}',True)

# extract some other files
print pylon.requestfile('Data/objectdata/log125_tga.txt')
print pylon.requestfile('Data/worlddata/bob.wld')
print pylon.requestfile('Data/worlddata/Default.wld')

# declare a simulation
sim2 = Simulation("simulation2",True)

# pogel-formated triangle data for a small clear blue hexagon
objtridat = '{[36],{[0.000000000000000000000000000],[0.025000000372529029846191406],[0.000000000000000000000000000],[0.500000],[1.000000],{[0.000000000000000000000000000],[1.000000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000],[0.500000],[0.500000],{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.021650634706020355224609375],[0.012500000186264514923095703],[0.000000000000000000000000000],[0.933013],[0.750000],{[0.866025388240814208984375000],[0.500000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[1.000000000000000000000000000]},{[Data/images/particle.bmp],[32],[32],[1]}},{[36],{[0.021650634706020355224609375],[0.012500000186264514923095703],[0.000000000000000000000000000],[0.933013],[0.750000],{[0.866025388240814208984375000],[0.500000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000],[0.500000],[0.500000],{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.021650634706020355224609375],[-0.012500000186264514923095703],[0.000000000000000000000000000],[0.933013],[0.250000],{[0.866025388240814208984375000],[-0.500000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[1.000000000000000000000000000]},{[Data/images/particle.bmp],[32],[32],[1]}},{[36],{[0.021650634706020355224609375],[-0.012500000186264514923095703],[0.000000000000000000000000000],[0.933013],[0.250000],{[0.866025388240814208984375000],[-0.500000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000],[0.500000],[0.500000],{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000002334529952301],[-0.025000000372529029846191406],[0.000000000000000000000000000],[0.500000],[0.000000],{[0.000000000000093381194703895],[-1.000000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[1.000000000000000000000000000]},{[Data/images/particle.bmp],[32],[32],[1]}},{[36],{[0.000000000000002334529952301],[-0.025000000372529029846191406],[0.000000000000000000000000000],[0.500000],[0.000000],{[0.000000000000093381194703895],[-1.000000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000],[0.500000],[0.500000],{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[-0.021650634706020355224609375],[-0.012500000186264514923095703],[0.000000000000000000000000000],[0.066987],[0.250000],{[-0.866025388240814208984375000],[-0.500000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[1.000000000000000000000000000]},{[Data/images/particle.bmp],[32],[32],[1]}},{[36],{[-0.021650634706020355224609375],[-0.012500000186264514923095703],[0.000000000000000000000000000],[0.066987],[0.250000],{[-0.866025388240814208984375000],[-0.500000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000],[0.500000],[0.500000],{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[-0.021650634706020355224609375],[0.012500000186264514923095703],[0.000000000000000000000000000],[0.066987],[0.750000],{[-0.866025388240814208984375000],[0.500000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[1.000000000000000000000000000]},{[Data/images/particle.bmp],[32],[32],[1]}},{[36],{[-0.021650634706020355224609375],[0.012500000186264514923095703],[0.000000000000000000000000000],[0.066987],[0.750000],{[-0.866025388240814208984375000],[0.500000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000],[0.500000],[0.500000],{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[-0.000000000000004669059904601],[0.025000000372529029846191406],[0.000000000000000000000000000],[0.500000],[1.000000],{[-0.000000000000186762389407791],[1.000000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[-0.000000000000000000000000000],[0.000000000000000000000000000],[1.000000000000000000000000000]},{[Data/images/particle.bmp],[32],[32],[1]}}'

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

if False:
	loop = 0
	loopmax = 500
	mass = 5
	maxrad = 1
	minrad = 0.5
	while loop < loopmax:
		loop += 1
		# position
		rad = random.random()*(minrad+maxrad)/2+minrad
		p1 = rnd_n1p1()*3.14159*2
		p2 = rnd_n1p1()*3.14159*2
		vect1 = makepos(math.sin(p1)*rad,math.cos(p1)*rad,0)
		# Rotation
		vect2 = makepos(0,0,0)
		# Direction
		spd = ((mass*loopmax)/(rad*rad)/1000)/1000
		vect3 = makepos(math.sin(p1+3.14159/2)*spd,math.cos(p1+3.14159/2)*spd,0)
		# Spin
		vect4 = makepos(0,0,0)
		newobjdat = '{[obj'+str(loop)+'],[22],[136],[0],[0],'+vect1+','+vect2+','+vect3+','+vect4+',{[1.000000],[0.000000],['+str(mass)+'],[1.000000],[1.000000],[1.000000],[0],[-1.000000]},<'+objtridat+'>}'
		print sim2.addobject(newobjdat)
	#sim2.stop()

print pylon.setsimulationcollitters(sim2.name,2)

cam.radus = 2

def makeObjectString(vect1,vect2,vect3,vect4,name,p1,p2,mass,tridat):
	return '{['+str(name)+'],['+str(p1)+'],['+str(p2)+'],[0],[0],'+vect1+','+vect2+','+vect3+','+vect4+',{[0.5],[0.25],['+str(float(mass))+'],[1.0],[1.0],[1.0],[0],[-1.0]},<'+tridat+'>}'

TestSphereSim = Simulation("TestSphereSim",True)

zeropos = makepos(0,0,0)

possibleImages = '{[Data/images/earth.bmp],[2]}', '{[Data/images/Glass.bmp],[2]}', '{[Data/images/lava8.bmp],[2]}', '{[Data/images/mandel_2.png],[1]}', '{[Data/images/pogel_runner_galax_color_1.png],[2]}', '{[Data/images/default_2.bmp],[0]}', '{[Data/images/mouse_pointer.png],[0]}'
possibleTriProps = 8, 8|32, 8, 8, 8, 2, 8|64
#possibleTriProps = 8, 8, 8, 8, 8, 2, 8

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
	rnum = int(random.random()*7)
	print pylon.object_add_sphere("TestSphereSim","Object"+str(loop),0.07,10,10,possibleImages[rnum],1,1,possibleTriProps[rnum])
	print 'ball'
	print pylon.object_build("TestSphereSim","Object"+str(loop))
	print 'build'
	loop = loop + 1

#print pylon.object_set_dir_3f("TestSphereSim","Object0",0,0.02,0)
#print pylon.object_set_dir_3f("TestSphereSim","Object1",0,0.02,0)
#print pylon.object_set_dir_3f("TestSphereSim","Object2",0,0.02,0)
#print pylon.object_set_dir_3f("TestSphereSim","Object3",0,0.02,0)

rnum = 5
print TestSphereSim.addobject( makeObjectString(zeropos,zeropos,zeropos,zeropos,"Outset",1|8|16,8|64,0,"") )
print pylon.object_add_sphere("TestSphereSim","Outset",2.0,20,20,possibleImages[rnum],1,1,possibleTriProps[rnum]|16)
#if rnum!=6 and not False:
#print pylon.object_add_sphere("TestSphereSim","Outset",2.0,20,20,possibleImages[rnum],1,1,possibleTriProps[rnum]|32)
#print pylon.object_add_sphere("TestSphereSim","Outset",2.1,20,20,'{[Data/images/earthcloudmap.png],[2]}',1,1,8|32)
print pylon.object_build("TestSphereSim","Outset")

#print TestSphereSim.addobject( makeObjectString(zeropos,zeropos,zeropos,zeropos,"Aura",1|8|16,128,0,"") )
#print pylon.object_add_disk("TestSphereSim","Aura",40,1,4.0,2.0,possibleImages[5],1,1,0,True)
#print pylon.object_build("TestSphereSim","Aura")

print pylon.setsimulationgravity_3f("TestSphereSim",0,-9.8,0)

print pylon.setsimulationcollitters("TestSphereSim",3)
print pylon.togglesimweight("TestSphereSim",False)

relocateobjscounter = 0

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

waitcalc(1000)
#TestSphereSim.stop()

