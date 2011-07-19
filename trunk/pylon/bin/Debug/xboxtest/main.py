
pygame.event.get()

rotcomx = controller.getRightY()
rotcomy = controller.getRightX()
if(abs(rotcomx) + abs(rotcomy) > 0.25):
	cam.turnby(rotcomx*5,rotcomy*5,0)

movcomx = controller.getLeftX()
movcomy = controller.getLeftY()
if(abs(movcomx) + abs(movcomy) > 0.25):
	cam.moveby(movcomx*-1,movcomy,0)

movcomzp = controller.getRightTrigger()
movcomzn = controller.getLeftTrigger()

if(movcomzp > -0.75):
	cam.moveby(0,0,(movcomzp+1)/2)
if(movcomzn > -0.75):
	cam.moveby(0,0,((movcomzn+1)/2)*-1)

if(controller.getButton(10)):
	cam.turnto(0,0,0)

