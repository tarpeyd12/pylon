import pylon

def hitfilter1(sim,obj1,obj2):
	if pylon.key_ispressed('=') or obj2 == "Outset":
		return True
	return False

def stepfunction1(sim,obj):
	#print "Object " + obj + " has moved"
	return

def collisionfunction1(sim,obj1,obj2):
	#print "Object " + obj1 + " has collided with Object " + obj2
	return
