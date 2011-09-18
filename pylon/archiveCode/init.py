# import the stuffs

try:
	from time import time,ctime
	import random
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

cam = Camera(0,0,-10,0,0,0)

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

ClickLine = Quad(0,0,pylon.mouse_pos_x(),pylon.mouse_pos_y(),'{[Data/images/particle.tga],[2]}',True)
Mouse = Quad(0,0,pylon.mouse_pos_x(),pylon.mouse_pos_y(),'{[Data/images/mouse_pointer.png],[2]}',True)

sim = Simulation("sim",True)
sim.start()
#print 'Data/log125.txt not found importing from database pylon'
print pylon.requestfile('Data/objectdata/log125_tga.txt')
print pylon.requestfile('Data/images/particle.bmp')
print pylon.requestfile('Data/images/particle.tga')
print pylon.requestfile('Data/worlddata/bob.wld')
print pylon.requestfile('Data/worlddata/Default.wld')



sim2 = Simulation("sim2",False)

objtridat = '{[4],{[0.000000000000000000000000000],[0.025000000372529029846191406],[0.000000000000000000000000000],[0.500000],[1.000000],{[0.000000000000000000000000000],[1.000000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000],[0.500000],[0.500000],{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.021650634706020355224609375],[0.012500000186264514923095703],[0.000000000000000000000000000],[0.933013],[0.750000],{[0.866025388240814208984375000],[0.500000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[1.000000000000000000000000000]},{[Data/images/particle.bmp],[32],[32],[1]}},{[4],{[0.021650634706020355224609375],[0.012500000186264514923095703],[0.000000000000000000000000000],[0.933013],[0.750000],{[0.866025388240814208984375000],[0.500000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000],[0.500000],[0.500000],{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.021650634706020355224609375],[-0.012500000186264514923095703],[0.000000000000000000000000000],[0.933013],[0.250000],{[0.866025388240814208984375000],[-0.500000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[1.000000000000000000000000000]},{[Data/images/particle.tga],[32],[32],[1]}},{[4],{[0.021650634706020355224609375],[-0.012500000186264514923095703],[0.000000000000000000000000000],[0.933013],[0.250000],{[0.866025388240814208984375000],[-0.500000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000],[0.500000],[0.500000],{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000002334529952301],[-0.025000000372529029846191406],[0.000000000000000000000000000],[0.500000],[0.000000],{[0.000000000000093381194703895],[-1.000000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[1.000000000000000000000000000]},{[Data/images/particle.bmp],[32],[32],[1]}},{[4],{[0.000000000000002334529952301],[-0.025000000372529029846191406],[0.000000000000000000000000000],[0.500000],[0.000000],{[0.000000000000093381194703895],[-1.000000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000],[0.500000],[0.500000],{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[-0.021650634706020355224609375],[-0.012500000186264514923095703],[0.000000000000000000000000000],[0.066987],[0.250000],{[-0.866025388240814208984375000],[-0.500000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[1.000000000000000000000000000]},{[Data/images/particle.tga],[32],[32],[1]}},{[4],{[-0.021650634706020355224609375],[-0.012500000186264514923095703],[0.000000000000000000000000000],[0.066987],[0.250000],{[-0.866025388240814208984375000],[-0.500000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000],[0.500000],[0.500000],{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[-0.021650634706020355224609375],[0.012500000186264514923095703],[0.000000000000000000000000000],[0.066987],[0.750000],{[-0.866025388240814208984375000],[0.500000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[1.000000000000000000000000000]},{[Data/images/particle.bmp],[32],[32],[1]}},{[4],{[-0.021650634706020355224609375],[0.012500000186264514923095703],[0.000000000000000000000000000],[0.066987],[0.750000],{[-0.866025388240814208984375000],[0.500000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000],[0.500000],[0.500000],{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[-0.000000000000004669059904601],[0.025000000372529029846191406],[0.000000000000000000000000000],[0.500000],[1.000000],{[-0.000000000000186762389407791],[1.000000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[-0.000000000000000000000000000],[0.000000000000000000000000000],[1.000000000000000000000000000]},{[Data/images/particle.tga],[32],[32],[1]}}'

objdat = '],[22],[136],[0],[0],{[2.187638521194458007812500000],[-164.624237060546875000000000000],[-47.653999328613281250000000000]},{[179.100006103515625000000000000],[125.449783325195312500000000000],[0.000000000000000000000000000]},{[0.000212223967537283897399902],[-0.012018831446766853332519531],[-0.003399600507691502571105957]},{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000]},{[1.000000],[0.750000],[5000.000000],[1.000000],[1.000000],[1.000000],[0],[-1.000000]},<'+objtridat+'>}'

sph0dat = '{[sphere0'+objdat

sim2.addobject(sph0dat)

sphere0 = sim2.obj("sphere0")

#pylon.togglesimweight(sim2.name,True)

print sim.addfile('Data/objectdata/log125_tga.txt')
sphere8 = sim.obj("sphere8")

#cam.turnby(90,0,0)


