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

testQuad = Quad(0,0,500,500,'{[Data/default_2.bmp],[32],[32],[0]}',False)

cam = Camera(0,0,-10,0,0,0)

#cam.turnby(90,0,0)


