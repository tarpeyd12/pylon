
# the exiting condition
#if pylon.key_ispressed('q') or pylon.key_ispressed('Q'):
if pylon.key_ispressed(chr(27)):
	print _pylon.exit(0)
	#quit()

# greeting
if counter == 0.0:
	print ''
	print 'Pylon Engine started:',time.ctime(time.time())

# simple object controll
count = counter
count = count % 20
goin = False
if count > 10:
	goin = True
	count = count + 01
else:
	count = count - 01
count = 10 - count

orig = "{[0],[0],[0]}"

if movestatetype == 0:
	pylon.object_move_3f("sim",'sphere0',  0,     0,     0)
	pylon.object_move_3f("sim",'sphere1', .1*count,  0,  0)
	pylon.object_move_3f("sim",'sphere2',  0, .1*count,  0)
	pylon.object_move_3f("sim",'sphere3',  0,  0, .1*count)
	pylon.object_move_3f("sim",'sphere4',-.1*count,  0,  0)
	pylon.object_move_3f("sim",'sphere5',  0,-.1*count,  0)
	pylon.object_move_3f("sim",'sphere6',  0,  0,-.1*count)
	
elif movestatetype == 1:
	pylon.object_move_3f("sim",'sphere0',rnd(),rnd(),rnd())
	pylon.object_move_3f("sim",'sphere1',rnd(),rnd(),rnd())
	pylon.object_move_3f("sim",'sphere2',rnd(),rnd(),rnd())
	pylon.object_move_3f("sim",'sphere3',rnd(),rnd(),rnd())
	pylon.object_move_3f("sim",'sphere4',rnd(),rnd(),rnd())
	pylon.object_move_3f("sim",'sphere5',rnd(),rnd(),rnd())
	pylon.object_move_3f("sim",'sphere6',rnd(),rnd(),rnd())	
	
pylon.object_set_dir_s("sim",'sphere0',orig)
pylon.object_set_dir_s("sim",'sphere1',orig)
pylon.object_set_dir_s("sim",'sphere2',orig)
pylon.object_set_dir_s("sim",'sphere3',orig)
pylon.object_set_dir_s("sim",'sphere4',orig)
pylon.object_set_dir_s("sim",'sphere5',orig)
pylon.object_set_dir_s("sim",'sphere6',orig)

if pylon.key_ispressed('a') or pylon.key_ispressed('A'):
	movestatetype = 0
elif pylon.key_ispressed('s') or pylon.key_ispressed('S'):
	movestatetype = 1


# getting the fps
if pylon.key_ispressed('p') or pylon.key_ispressed('P'):
	print 'FPS: ', pylon.fps()

# controlling the pylon internal calculation thread
if pylon.key_ispressed('\r') or pylon.key_ispressed('\n'):
	if going:
		print "Stopping Physics Calculation Thread"
		going = False
		_pylon_calc.lock()
		# gives time to the calculation thread to catch up
		waitcalc(1000)
	else:
		print "Starting Physics Calculation Thread"
		going = True
		# gives time to the calculation thread to catch up
		waitcalc(1000)
		_pylon_calc.unlock()

# increment the counter
counter = counter + 0.1

# more object controll
if pylon.key_ispressed(';'):
	sphere8.move(rnd()*3,rnd()*3,rnd()*3)
	sphere0.move(rnd()*3,rnd()*3,rnd()*3)

# specific simulation execution controll
if pylon.key_ispressed('g'):
	sim2.stop()
	waitcalc(100)
if pylon.key_ispressed('G'):
	sim2.restart()
	waitcalc(100)

# moving an object with the mouse
if ( pylon.mouse_ispressed() and pylon.mouse_getbutton() == 1 ) or ( pylon.key_ispressed('z') or pylon.key_ispressed('Z') ):
	x = pylon.mouse_pos_x()/640.0
	y = pylon.mouse_pos_y()/-480.0
	pylon.object_move_3f("sim",'sphere7',x-0.5,y+0.5,0)
	pylon.object_set_dir_s("sim",'sphere7',orig)


# mouse cursor and 'drag box'
	# DragBox:
if pylon.mouse_ispressed():
	ClickLine.x2 = pylon.mouse_pos_x()
	ClickLine.y2 = pylon.mouse_pos_y()
	if not ClickLine.visable():
		ClickLine.x1 = pylon.mouse_pos_x()
		ClickLine.y1 = pylon.mouse_pos_y()
		ClickLine.makeVisable()
	ClickLine.update()
else:
	ClickLine.makeInvisable()

	# Mouse Cursor:
mouseScale = 1
if pylon.mouse_ispressed():
	mouseScale = 1.5
if True or pylon.mouse_pos_x() != Mouse.x1+int(4*mouseScale) or pylon.mouse_pos_y() != Mouse.y1+int(6*mouseScale):
	Mouse.x1 = pylon.mouse_pos_x() - int(3*mouseScale)
	Mouse.y1 = pylon.mouse_pos_y() - int(5*mouseScale)
	Mouse.x2 = Mouse.x1 + int(32*mouseScale)
	Mouse.y2 = Mouse.y1 + int(32*mouseScale)
	Mouse.update()

# just in case of HUD artifacts clear HUD every 100 script loops
#if(pylon.key_ispressed('/') or int(counter*10) % 100 == 0):
#	pylon.clearquads()

previouslastkey = lastkey
lastkey = pylon.key_last()

currentanimation = pylon.object_get_animation(Animation.name,animationname)
timesinceanimationstart = pylon.object_get_animsince(Animation.name,animationname)
animationlength = pylon.object_get_animlen(Animation.name,animationname, currentanimation)

if timesinceanimationstart > animationlength:
	if random.random() > 0.1:
		pylon.object_set_animation(Animation.name,animationname,"Idle")
	else:
		nextanimation = ""
		if random.random() > 0.5:
			nextanimation = "Look"
		else:
			nextanimation = "Rear"
		pylon.object_set_animation(Animation.name,animationname,nextanimation)
	pylon.object_set_animtime(Animation.name,animationname)
else:
	if pylon.key_ispressed(' '):
		if currentanimation != "Jump":
			pylon.object_set_animtime(Animation.name,animationname)
		pylon.object_set_animation(Animation.name,animationname,"Jump")
	elif pylon.key_ispressed('w') or pylon.key_ispressed('W'):
		if currentanimation != "Jump" and timesinceanimationstart < animationlength:
			if currentanimation != "Walk":
				pylon.object_set_animtime(Animation.name,animationname)
			pylon.object_set_animation(Animation.name,animationname,"Walk")
	elif pylon.key_ispressed('s') or pylon.key_ispressed('S'):
		if currentanimation != "Jump" and timesinceanimationstart < animationlength:
			if currentanimation != "WalkReverse":
				pylon.object_set_animtime(Animation.name,animationname)
			pylon.object_set_animation(Animation.name,animationname,"WalkReverse")

if pylon.key_ispressed( 'd' ) or pylon.key_ispressed( 'D' ):
	pylon.object_set_spin_3f( Animation.name, animationname, 0.0, 30.0, 0.0 )
elif pylon.key_ispressed( 'a' ) or pylon.key_ispressed( 'A' ):
	pylon.object_set_spin_3f( Animation.name, animationname, 0.0,-30.0, 0.0 )
else:
	pylon.object_set_spin_3f( Animation.name, animationname, 0.0, 0.0, 0.0 )

# add a pogel formated multi-object data file to a simulation
if pylon.key_ispressed('m'):
	sim.addfilehere('Data/objectdata/log125_tga.txt')

# simple debug display toggling, for object trails
if pylon.key_ispressed('4'):
	if pylon.hasproperty(16):
		pylon.removeproperty(16)
	else:
		pylon.addproperty(16)

# clearing all objects from a simulation
if pylon.key_ispressed(','):
	sim2.stop()
	pylon.clearsimulation(sim2.name)
	sim2.restart()

# rudimentary camera controll
cam.mouserot()
cam.mousepos()
cam.centerset()
cam.getcamstrs()

pylon.subrender_set_cam(subrenderer1, cam.posx,cam.posy,cam.posz, cam.rotx,cam.roty,cam.rotz)
pylon.subrender_set_ratio(subrenderer1, float(pylon.window_width())/float(pylon.window_height()))
Bloop.y1 = pylon.window_height()
Bloop.x2 = pylon.window_width()
#Bloop.makeInvisable()
Bloop.update()

pylon.object_move_3f(Sky.name,"Sky",-cam.posx,-cam.posy,-cam.posz)

pylon.subrender_set_light(subrenderer1, 1, math.sin(counter)*10,0,math.cos(counter)*10, '{[.1],[0],[0],[1]}', '{[0],[1],[0],[1]}', '{[0],[0],[.1],[1]}', False)

# a function defined in init.py for controlling the 'flow' of objects/particles
if going:
	doOBJECTrelocate()


