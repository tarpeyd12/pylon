
refresh = False
if(pylon.mouse_ispressed()):
	pylon.clearquads()
	refresh = True

if(refresh or pylon.window_width() != bg.x2 or pylon.window_height() != bg.y2):
	if(refresh):
		bg = Quad(0,0,0,0,'{[Data/default_2.bmp],[1]}',False)
	else:
		bg.makeInvisable()
	bg.x2 = pylon.window_width()
	bg.y2 = pylon.window_height()
	bg.makeVisable()

mouseScale = .1
if(refresh or pylon.mouse_pos_x() != Mouse.x1+int(4/mouseScale) or pylon.mouse_pos_y() != Mouse.y1+int(6/mouseScale)):
	if(refresh):
		Mouse = Quad(0,0,0,0,'{[Data/mouse_pointer.png],[1]}',False)
	else:
		Mouse.makeInvisable()
	Mouse.x1 = pylon.mouse_pos_x() - int(4/mouseScale)
	Mouse.y1 = pylon.mouse_pos_y() - int(6/mouseScale)
	Mouse.x2 = Mouse.x1 + int(32/mouseScale)
	Mouse.y2 = Mouse.y1 + int(32/mouseScale)
	Mouse.makeVisable()
