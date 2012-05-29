import pylon
from pylonsupport.classes.position import Position

def hitfilter1(sim,obj1,obj2):
	if pylon.key_ispressed('=') or obj2 == "Outset":
		return True
	return False

def stepfunction1(sim,obj,steps):
	pass
	return
	pos = Position()
	pos.fromstring(pylon.object_get_pos_s(sim,obj))
	dir = Position()
	dir.fromstring(pylon.object_get_dir_s(sim,obj))
	dist = Position().distance(pos)
	if dist < 1 or dist > 1:
		pos /= dist
		#if dist > 1:
			#pos = pos * 1
		#if dist < 1:
			#pos = pos * 1
		pylon.object_set_pos_3f(sim,obj,pos.x,pos.y,pos.z)
		
	#if pos.y < -0.5:
		#pos.y = -0.5
		#pylon.object_set_pos_3f(sim,obj,pos.x,pos.y,pos.z)
		#dir.y = dir.y + 1.0
		#if dir.y < 0.0:
			#dir.y = 0.0
			#pylon.object_set_dir_3f(sim,obj,dir.x,dir.y,dir.z)
	#pylon.object_set_dir_3f(sim,obj,dir.x,dir.y-.2,dir.z)
	return

def collisionfunction1(sim,obj1,obj2):
	#print "Object " + sim + ":" + obj1 + " has collided with Object " + sim + ":" + obj2
	return
