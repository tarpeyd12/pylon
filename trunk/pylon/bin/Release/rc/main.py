if counter == 0.0:
	print 'Pylon Engine started:',ctime(time())

	
count = counter
count = count % 20
goin = False
if count > 10:
	goin = True
	count = count + 01 #
else:
	count = count - 01 #
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

if pylon.mouse_ispressed() and pylon.mouse_getbutton() == 1:
	x = pylon.mouse_pos_x()/640.0
	y = pylon.mouse_pos_y()/-480.0
	pylon.object_move_3f("sim",'sphere7',x-0.5,y+0.5,0)
	pylon.object_set_dir_s("sim",'sphere7',orig)

if pylon.key_ispressed('a') or pylon.key_ispressed('A'):
	movestatetype = 0
elif pylon.key_ispressed('s') or pylon.key_ispressed('S'):
	movestatetype = 1

if pylon.key_ispressed('p') or pylon.key_ispressed('P'):
	print 'FPS: ', pylon.fps()

if pylon.key_ispressed('\r'):
	if going:
		print "Stopping Physics Calculation Thread"
		going = False
		calc.lock()
		# gives time to the calculation thread to catch up
		waitcalc(1000000)
	else:
		print "Starting Physics Calculation Thread"
		going = True
		# gives time to the calculation thread to catch up
		waitcalc(1000000)
		calc.unlock()

counter = counter + 0.5

#st = getstrthing(st)

#print st

if pylon.key_ispressed(';'):
	sphere8.move(rnd()*3,rnd()*3,rnd()*3)
	sphere0.move(rnd()*3,rnd()*3,rnd()*3)

if pylon.key_ispressed('q') or pylon.key_ispressed('Q'):
	quit()

if pylon.key_ispressed('g'):
	sim2.stop()
	waitcalc(1000000)

if pylon.key_ispressed('G'):
	sim2.restart()
	waitcalc(1000000)

cam.mouserot()
cam.mousepos()

