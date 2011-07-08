try:
	from time import time,ctime
	import random
	import pylon
	import _pylon
	
	try:
		from pylonclasses import *
	except ImportError:
		print 'Could not find \"pylonclasses.py\", adding data directory in an attempt to correct'
		import sys
		sys.path.append('Data')
		try:
			from pylonclasses import *
		except ImportError:
			print pylon.requestfile('Data/pylonclasses.py')
			from pylonclasses import *

except ImportError:
	print 'Importing failure for the required modules in \"init.py\".'
	quit()

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

if versioncompare(_pylon.version(),'0.0.30.150'):
	print ''
else:
	print 'boo'
	quit()

movestatetype = 0

going = False

def rnd_n1p1():
	return (random.random() * 2) - 1

def rnd():
	return rnd_n1p1() * 0.2

def waitcalc(i):
	a = 0
	while a < i:
		a = a + 1

cam = Camera(0,0,-10,0,0,0)

sim = Simulation("sim",True)
#print 'Data/log125.txt not found importing from database pylon'
print pylon.requestfile('Data/log125.txt')
print pylon.requestfile('Data/particle.bmp')
print sim.addfile('Data/log125.txt')
print pylon.requestfile('Data/default_2.bmp')
print pylon.requestfile('Data/bob.wld')
print pylon.requestfile('Data/Default.wld')

sim2 = Simulation("sim2",True)

sphere8 = sim.obj("sphere8")

sim2.addobject('{[sphere0],[22],[136],[0],[0],{[2.187638521194458007812500000],[-164.624237060546875000000000000],[-47.653999328613281250000000000]},{[179.100006103515625000000000000],[125.449783325195312500000000000],[0.000000000000000000000000000]},{[0.000212223967537283897399902],[-0.012018831446766853332519531],[-0.003399600507691502571105957]},{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000]},{[1.000000],[0.750000],[5000.000000],[1.000000],[1.000000],[1.000000],[0],[-1.000000]},<{[4],{[0.000000000000000000000000000],[0.025000000372529029846191406],[0.000000000000000000000000000],[0.500000],[1.000000],{[0.000000000000000000000000000],[1.000000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000],[0.500000],[0.500000],{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.021650634706020355224609375],[0.012500000186264514923095703],[0.000000000000000000000000000],[0.933013],[0.750000],{[0.866025388240814208984375000],[0.500000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[1.000000000000000000000000000]},{[Data/particle.bmp],[32],[32],[1]}},{[4],{[0.021650634706020355224609375],[0.012500000186264514923095703],[0.000000000000000000000000000],[0.933013],[0.750000],{[0.866025388240814208984375000],[0.500000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000],[0.500000],[0.500000],{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.021650634706020355224609375],[-0.012500000186264514923095703],[0.000000000000000000000000000],[0.933013],[0.250000],{[0.866025388240814208984375000],[-0.500000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[1.000000000000000000000000000]},{[Data/particle.bmp],[32],[32],[1]}},{[4],{[0.021650634706020355224609375],[-0.012500000186264514923095703],[0.000000000000000000000000000],[0.933013],[0.250000],{[0.866025388240814208984375000],[-0.500000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000],[0.500000],[0.500000],{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000002334529952301],[-0.025000000372529029846191406],[0.000000000000000000000000000],[0.500000],[0.000000],{[0.000000000000093381194703895],[-1.000000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[1.000000000000000000000000000]},{[Data/particle.bmp],[32],[32],[1]}},{[4],{[0.000000000000002334529952301],[-0.025000000372529029846191406],[0.000000000000000000000000000],[0.500000],[0.000000],{[0.000000000000093381194703895],[-1.000000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000],[0.500000],[0.500000],{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[-0.021650634706020355224609375],[-0.012500000186264514923095703],[0.000000000000000000000000000],[0.066987],[0.250000],{[-0.866025388240814208984375000],[-0.500000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[1.000000000000000000000000000]},{[Data/particle.bmp],[32],[32],[1]}},{[4],{[-0.021650634706020355224609375],[-0.012500000186264514923095703],[0.000000000000000000000000000],[0.066987],[0.250000],{[-0.866025388240814208984375000],[-0.500000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000],[0.500000],[0.500000],{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[-0.021650634706020355224609375],[0.012500000186264514923095703],[0.000000000000000000000000000],[0.066987],[0.750000],{[-0.866025388240814208984375000],[0.500000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[1.000000000000000000000000000]},{[Data/particle.bmp],[32],[32],[1]}},{[4],{[-0.021650634706020355224609375],[0.012500000186264514923095703],[0.000000000000000000000000000],[0.066987],[0.750000],{[-0.866025388240814208984375000],[0.500000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000],[0.500000],[0.500000],{[0.000000000000000000000000000],[0.000000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[-0.000000000000004669059904601],[0.025000000372529029846191406],[0.000000000000000000000000000],[0.500000],[1.000000],{[-0.000000000000186762389407791],[1.000000000000000000000000000],[0.000000000000000000000000000]},{[0.200000],[0.500000],[1.000000],[1.000000]}},{[-0.000000000000000000000000000],[0.000000000000000000000000000],[1.000000000000000000000000000]},{[Data/particle.bmp],[32],[32],[1]}}>}')

sphere0 = sim2.obj("sphere0")

#cam.turnby(90,0,0)


