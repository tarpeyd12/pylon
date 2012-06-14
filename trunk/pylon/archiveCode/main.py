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

if pylon.key_ispressed('a') or pylon.key_ispressed('A'):
	movestatetype = 0
elif pylon.key_ispressed('s') or pylon.key_ispressed('S'):
	movestatetype = 1


# getting the fps
if pylon.key_ispressed('p') or pylon.key_ispressed('P'):
	print 'FPS: ', pylon.fps()

# increment the counter
counter = counter + 0.1

# more object controll
if pylon.key_ispressed(';'):
	sphere8.move(rnd()*3,rnd()*3,rnd()*3)
	sphere0.move(rnd()*3,rnd()*3,rnd()*3)

# specific simulation execution controll
if pylon.key_ispressed('g'):
	sim2.stop()
	#waitcalc(100)
if pylon.key_ispressed('G'):
	sim2.restart()
	#waitcalc(100)

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

if False:
	currentanimation = Beast.getAnimationCurrent()
	timesinceanimationstart = Beast.getAnimationRuntime()
	animationlength = Beast.getAnimationLength( currentanimation )

	if timesinceanimationstart > animationlength:
		if random.random() > 0.1:
			Beast.setAnimation( "Idle" )
		else:
			nextanimation = ""
			if random.random() > 0.5:
				nextanimation = "Look"
			else:
				nextanimation = "Rear"
			Beast.setAnimation( nextanimation )
		Beast.setAnimationStart()
	else:
		if pylon.key_ispressed( ' ' ):
			if currentanimation != "Jump":
				Beast.setAnimationStart()
			Beast.setAnimation( "Jump" )
		elif pylon.key_ispressed( 'w' ) or pylon.key_ispressed( 'W' ):
			if currentanimation != "Jump" and timesinceanimationstart < animationlength:
				if currentanimation != "Walk":
					Beast.setAnimationStart()
				Beast.setAnimation( "Walk" )
		elif pylon.key_ispressed( 's' ) or pylon.key_ispressed( 'S' ):
			if currentanimation != "Jump" and timesinceanimationstart < animationlength:
				if currentanimation != "WalkReverse":
					Beast.setAnimationStart()
				Beast.setAnimation( "WalkReverse" )

	if pylon.key_ispressed( 'd' ) or pylon.key_ispressed( 'D' ):
		Beast.setSpin( Position(0,30,0) )
	elif pylon.key_ispressed( 'a' ) or pylon.key_ispressed( 'A' ):
		Beast.setSpin( Position(0,-30,0) )
	else:
		Beast.setSpin( Position(0,0,0) )

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

subrenderer1.setCamera( cam )
subrenderer1.setRatio( float(pylon.window_width())/float(pylon.window_height()) )
subrenderer1.setLight( 1, Position(math.sin(pylon.get_runtime()/2),0,math.cos(pylon.get_runtime()/2))*10, '{[.1],[0],[0],[1]}', '{[0],[1],[0],[1]}', '{[0],[0],[.1],[1]}', False)

Bloop.y1 = pylon.window_height()
Bloop.x2 = pylon.window_width()
#Bloop.makeInvisable()
Bloop.update()

pylon.object_move_3f(Sky.name,"Sky",-cam.posx,-cam.posy,-cam.posz)

# a function defined in init.py for controlling the 'flow' of objects/particles
if going:
	doOBJECTrelocate()

if pylon.key_ispressed('z') and pylon.select_isgood() and pylon.mouse_ispressed() and pylon.mouse_getbutton() == 0:
	pylon.object_move_3f( pylon.select_get_sim(), pylon.select_get_obj(), 0, 0, 0 )


