import pylon
from pylonsupport.classes.position import Position

def hitfilter1( sim, obj1, obj2 ):
	if pylon.key_ispressed( '=' ) or obj2.find("sim2Outset") != -1:
		return True
	return False

def stepfunction1( sim, obj, steps ):
	return

def collisionfunction1( sim, obj1, obj2 ):
	return
