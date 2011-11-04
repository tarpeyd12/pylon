if counter == 0.0:
	print ''
	print 'Pylon Engine started:',ctime(time())

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

if pylon.key_ispressed('p') or pylon.key_ispressed('P'):
	print 'FPS: ', pylon.fps()

if pylon.key_ispressed('q') or pylon.key_ispressed('Q'):
	print _pylon.exit(0)
	quit()

if pylon.key_ispressed('\r') or pylon.key_ispressed('\n'):
	if going:
		print "Stopping Physics Calculation Thread"
		going = False
		_pylon_calc.lock()
		# gives time to the calculation thread to catch up
		waitcalc(1000000)
	else:
		print "Starting Physics Calculation Thread"
		going = True
		# gives time to the calculation thread to catch up
		waitcalc(1000000)
		_pylon_calc.unlock()

counter = counter + 0.1

#st = getstrthing(st)
#print st

if pylon.key_ispressed(';'):
	sphere8.move(rnd()*3,rnd()*3,rnd()*3)
	sphere0.move(rnd()*3,rnd()*3,rnd()*3)

if pylon.key_ispressed('g'):
	sim2.stop()
	waitcalc(100000)

if pylon.key_ispressed('G'):
	sim2.restart()
	waitcalc(100000)

if ( pylon.mouse_ispressed() and pylon.mouse_getbutton() == 1 ) or ( pylon.key_ispressed('z') or pylon.key_ispressed('Z') ):
	x = pylon.mouse_pos_x()/640.0
	y = pylon.mouse_pos_y()/-480.0
	pylon.object_move_3f("sim",'sphere7',x-0.5,y+0.5,0)
	pylon.object_set_dir_s("sim",'sphere7',orig)


if pylon.mouse_ispressed():
	ClickLine.x2 = pylon.mouse_pos_x()
	ClickLine.y2 = pylon.mouse_pos_y()
	if not ClickLine.visable:
		ClickLine.x1 = pylon.mouse_pos_x()
		ClickLine.y1 = pylon.mouse_pos_y()
		ClickLine.makeVisable()
	else:
		ClickLine.update()
else:
	if ClickLine.visable:
		ClickLine.makeInvisable()

mouseScale = 1
if pylon.mouse_ispressed():
	mouseScale = 1.5
if pylon.mouse_pos_x() != Mouse.x1+int(4*mouseScale) or pylon.mouse_pos_y() != Mouse.y1+int(6*mouseScale):
#if(True):
	Mouse.x1 = pylon.mouse_pos_x() - int(3*mouseScale)
	Mouse.y1 = pylon.mouse_pos_y() - int(5*mouseScale)
	Mouse.x2 = Mouse.x1 + int(32*mouseScale)
	Mouse.y2 = Mouse.y1 + int(32*mouseScale)
	Mouse.update()

if(pylon.key_ispressed('/') or int(counter*10) % 100 == 0):
	pylon.clearquads()

if pylon.key_ispressed(' ') or pylon.key_ispressed('j'):
#	print pylon.requestfile('Data/images/particle.bmp')
	bob = 0
	while bob < 1:
		sc1 = 0.1
		sc2 = 0.0
		sc3 = 0.0
		sc4 = 0.0
		vect1 = makepos(rnd_n1p1()*sc1, rnd_n1p1()*sc1, rnd_n1p1()*sc1)
		vect2 = makepos(rnd_n1p1()*sc2, rnd_n1p1()*sc2, rnd_n1p1()*sc2)
		vect3 = makepos(rnd_n1p1()*sc3, rnd_n1p1()*sc3, rnd_n1p1()*sc3)
		vect4 = makepos(rnd_n1p1()*sc4, rnd_n1p1()*sc4, rnd_n1p1()*sc4)
		newobjdat = '{[obj'+str(int(counter*10))+'.'+str(bob)+'],[22],[136],[0],[0],'+vect1+','+vect2+','+vect3+','+vect4+',{[1.000000],[0.000000],[2000.000000],[1.000000],[1.000000],[1.000000],[0],[-1.000000]},<'+objtridat+'>}'
		print sim2.addobject(newobjdat)
		pylon.object_build(sim2.name,'objobj'+str(int(counter*10))+'.'+str(bob))
		bob = bob + 1

if pylon.key_ispressed('m'):
#	print pylon.requestfile('Data/images/particle.tga')
	sim.addfilehere('Data/objectdata/log125_tga.txt')

if pylon.key_ispressed('4'):
	if pylon.hasproperty(16):
		pylon.removeproperty(16)
	else:
		pylon.addproperty(16)

if pylon.key_ispressed(','):
	sim2.stop()
	waitcalc(1000000)
	pylon.clearsimulation(sim2.name)
	waitcalc(1000000)
	sim2.restart()
	waitcalc(100000)
#sim.restart()

if False:
	if pylon.key_ispressed('r'):
		cam.mradus(-0.01)
	if pylon.key_ispressed('f'):
		cam.mradus(0.01)
	if pylon.key_ispressed('a'):
		cam.angley = cam.angley + 1
	if pylon.key_ispressed('d'):
		cam.angley = cam.angley - 1
	if pylon.key_ispressed('w'):
		cam.anglex = cam.anglex - 1
	if pylon.key_ispressed('s'):
		cam.anglex = cam.anglex + 1

	cam.getcamstrs()
	print cam.radus

cam.mouserot()
#cam.angley = cam.angley + .1
cam.mousepos()
cam.centerset()
cam.getcamstrs()

doOBJECTrelocate()

