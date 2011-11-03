# import the stuffs

try:
	from time import time,ctime
	import random
	import math
	import pylon
	import _pylon
	
	try:
		print pylon.requestfile('Data/code/pylonclasses.py')
		from pylonclasses import *
	except ImportError:
		print 'Could not find \"pylonclasses.py\", adding data directory in an attempt to correct ...'
		
		# system import just cannot fail, if it did then I've got bigger problems to wory about
		import sys
		
		sys.path.append('./Data/')
		sys.path.append('./Data/code/')
		
		try:
			from pylonclasses import *
		except ImportError:
			print 'correction failed attempting file request instead ...'
			print 'requesting file: \"Data/code/pylonclasses.py\"'
			print pylon.requestfile('Data/code/pylonclasses.py')
			#print pylon.requestfile('Data/code/pylonclasses.pyc')
			from pylonclasses import *
			
except ImportError as bob:
	print 'ERROR: Master import failure'
	print '       Importing failure for the required modules in \"init.py\".'
	print type(bob)
	print 'Exiting ...'
	quit()

# the main Initialization things ...

counter = 0

print 'brains'

def versioncompare_dig(ver,spot):
	my_splitter = shlex.shlex(ver, posix = True)
	my_splitter.whitespace += "_.abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
	my_splitter.whitespace_split = True
	dig = list(my_splitter)
	return int(dig[spot])

def versioncompare(vera,verb):
	a = bool(versioncompare_dig(vera,0) >= versioncompare_dig(verb,0))
	b = bool(versioncompare_dig(vera,1) >= versioncompare_dig(verb,1))
	c = bool(versioncompare_dig(vera,2) >= versioncompare_dig(verb,2))
	d = bool(versioncompare_dig(vera,3) >= versioncompare_dig(verb,3))
	return bool(a and b and c and d)

if versioncompare(_pylon.version(),'0.1.161.829'):
	print 'Pylon version meets or exceeds minimum requirements ...'
else:
	print 'ERROR: Version dose not meet minimum requirements,'
	print '       this pylon archive cannot be executed for this reason.'
	print ''
	print 'Exiting program at time: ',ctime(time())
	quit()

cam = Camera(0,0,0,0,0,0)

movestatetype = 0

going = True

def rnd_n1p1():
	return (random.random() * 2) - 1

def rnd():
	return rnd_n1p1() * 0.2

def waitcalc(i):
	a = 0
	while a < i:
		a = a + 1

print pylon.requestfile('Data/images/particle.tga')
print pylon.requestfile('Data/images/mouse_pointer.png')

ClickLine = Quad(0,0,pylon.mouse_pos_x(),pylon.mouse_pos_y(),'{[Data/images/default_2.bmp],[2]}',True)
Mouse = Quad(0,0,pylon.mouse_pos_x(),pylon.mouse_pos_y(),'{[Data/images/mouse_pointer.png],[2]}',True)

#print 'Data/log125.txt not found importing from database pylon'
print pylon.requestfile('Data/objectdata/log125_tga.txt')
print pylon.requestfile('Data/worlddata/bob.wld')
print pylon.requestfile('Data/worlddata/Default.wld')

#NullSim = Simulation("NULL",False)

sim2 = Simulation("simulation2",True)

objtridat = '{[36],{[0.000000000000000000000000000],[0.025000000372529029846191406],[0.000000000000000000000000000],[0.500000],[1.000000],{[0.000000000000000000000000000],[1.000000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000],[0.500000],[0.500000],{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.021650634706020355224609375],[0.012500000186264514923095703],[0.000000000000000000000000000],[0.933013],[0.750000],{[0.866025388240814208984375000],[0.500000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[1.000000000000000000000000000]},{[Data/images/particle.bmp],[32],[32],[1]}},{[36],{[0.021650634706020355224609375],[0.012500000186264514923095703],[0.000000000000000000000000000],[0.933013],[0.750000],{[0.866025388240814208984375000],[0.500000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000],[0.500000],[0.500000],{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.021650634706020355224609375],[-0.012500000186264514923095703],[0.000000000000000000000000000],[0.933013],[0.250000],{[0.866025388240814208984375000],[-0.500000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[1.000000000000000000000000000]},{[Data/images/particle.bmp],[32],[32],[1]}},{[36],{[0.021650634706020355224609375],[-0.012500000186264514923095703],[0.000000000000000000000000000],[0.933013],[0.250000],{[0.866025388240814208984375000],[-0.500000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000],[0.500000],[0.500000],{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000002334529952301],[-0.025000000372529029846191406],[0.000000000000000000000000000],[0.500000],[0.000000],{[0.000000000000093381194703895],[-1.000000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[1.000000000000000000000000000]},{[Data/images/particle.bmp],[32],[32],[1]}},{[36],{[0.000000000000002334529952301],[-0.025000000372529029846191406],[0.000000000000000000000000000],[0.500000],[0.000000],{[0.000000000000093381194703895],[-1.000000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000],[0.500000],[0.500000],{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[-0.021650634706020355224609375],[-0.012500000186264514923095703],[0.000000000000000000000000000],[0.066987],[0.250000],{[-0.866025388240814208984375000],[-0.500000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[1.000000000000000000000000000]},{[Data/images/particle.bmp],[32],[32],[1]}},{[36],{[-0.021650634706020355224609375],[-0.012500000186264514923095703],[0.000000000000000000000000000],[0.066987],[0.250000],{[-0.866025388240814208984375000],[-0.500000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000],[0.500000],[0.500000],{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[-0.021650634706020355224609375],[0.012500000186264514923095703],[0.000000000000000000000000000],[0.066987],[0.750000],{[-0.866025388240814208984375000],[0.500000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[1.000000000000000000000000000]},{[Data/images/particle.bmp],[32],[32],[1]}},{[36],{[-0.021650634706020355224609375],[0.012500000186264514923095703],[0.000000000000000000000000000],[0.066987],[0.750000],{[-0.866025388240814208984375000],[0.500000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000],[0.500000],[0.500000],{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[-0.000000000000004669059904601],[0.025000000372529029846191406],[0.000000000000000000000000000],[0.500000],[1.000000],{[-0.000000000000186762389407791],[1.000000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[-0.000000000000000000000000000],[0.000000000000000000000000000],[1.000000000000000000000000000]},{[Data/images/particle.bmp],[32],[32],[1]}}'

objdat = '],[22],[136],[0],[0],{[2.187638521194458007812500000],[-164.624237060546875000000000000],[-47.653999328613281250000000000]},{[179.100006103515625000000000000],[125.449783325195312500000000000],[0.000000000000000000000000000]},{[0.000212223967537283897399902],[-0.012018831446766853332519531],[-0.003399600507691502571105957]},{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000]},{[1.000000],[0.750000],[5000.000000],[1.000000],[1.000000],[1.000000],[0],[-1.000000]},<'+objtridat+'>}'

sph0dat = '{[sphere0'+objdat

#sim2.addobject(sph0dat)


sphere0 = sim2.obj("sphere0")

#print pylon.togglesimweight(sim2.name,False)

sim = Simulation("sim",True)
#print sim.addfile('Data/objectdata/log125_tga.txt')
#sim.addfilehere('Data/objectdata/log125_tga.txt')
#sphere8 = sim.obj("sphere8")

#cam.turnby(90,0,0)

st = ''

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
loop = 0
rnum = 0
numOSpheres = 15
while loop < numOSpheres:
	sc1 = 1.5
	#rpos = makepos(rnd_n1p1()*sc1*0, float(loop)/5.0+.01-(numOSpheres/5.0/2), rnd_n1p1()*sc1*0)
	rpos = makepos(rnd_n1p1()*sc1, rnd_n1p1()*sc1, rnd_n1p1()*sc1)
	rot = makepos(rnd_n1p1()*360,rnd_n1p1()*360,rnd_n1p1()*360)
	print "\nstart Object"+str(loop)
	print TestSphereSim.addobject( makeObjectString(rpos,rot,zeropos,zeropos,"Object"+str(loop),2|4|16,8,30000,"") )
	print 'add'
	rnum = int(random.random()*7)
	print pylon.object_add_sphere("TestSphereSim","Object"+str(loop),0.07,6,10,possibleImages[rnum],1,1,possibleTriProps[rnum])
	print 'ball'
	print pylon.object_build("TestSphereSim","Object"+str(loop))
	print 'build'
	loop = loop + 1


#print pylon.object_set_dir_3f("TestSphereSim","Object0",0,0.02,0)
#print pylon.object_set_dir_3f("TestSphereSim","Object1",0,0.02,0)
#print pylon.object_set_dir_3f("TestSphereSim","Object2",0,0.02,0)
#print pylon.object_set_dir_3f("TestSphereSim","Object3",0,0.02,0)

rnum = 5
#print TestSphereSim.addobject( makeObjectString(zeropos,zeropos,zeropos,zeropos,"Outset",1|8|16,8|64,0,"") )
#print pylon.object_add_sphere("TestSphereSim","Outset",2.0,20,20,possibleImages[rnum],1,1,possibleTriProps[rnum]|16)
#if rnum!=6 and not False:
#print pylon.object_add_sphere("TestSphereSim","Outset",2.0,20,20,possibleImages[rnum],1,1,possibleTriProps[rnum]|32)
#print pylon.object_add_sphere("TestSphereSim","Outset",2.1,20,20,'{[Data/images/earthcloudmap.png],[2]}',1,1,8|32)
#print pylon.object_build("TestSphereSim","Outset")

#print TestSphereSim.addobject( makeObjectString(zeropos,zeropos,zeropos,zeropos,"Aura",1|8|16,128,0,"") )
#print pylon.object_add_disk("TestSphereSim","Aura",40,1,4.0,2.0,possibleImages[5],1,1,0,True)
#print pylon.object_build("TestSphereSim","Aura")

#print pylon.setsimulationgravity_3f("TestSphereSim",0,-0.8,0)

print pylon.setsimulationcollitters("TestSphereSim",2)

relocateobjscounter = 0

def doOBJECTrelocate():
	global relocateobjscounter
	relocateobjscounter = relocateobjscounter + 1
	if relocateobjscounter%2 == 1:
		return
	c = int((counter/2)*10.0)%numOSpheres
	oname = "Object"+str(c)
	sc1 = 0.025
	rpos = makepos(rnd_n1p1()*sc1, rnd_n1p1()*sc1, rnd_n1p1()*sc1*0)
	pylon.object_set_pos_s("TestSphereSim",oname,rpos)
	pylon.object_set_dir_3f("TestSphereSim",oname,0.005,0.05,0)

waitcalc(10000)
#TestSphereSim.stop()

