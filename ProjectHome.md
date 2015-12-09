# About #
Pylon is a multithreaded game engine programmed mostly in c++, using the [pogel](http://pogel.googlecode.com/) physics library and python scripting for game logic. OpenGL is used for rendering.

Though Pylon is multithreaded, it uses no inter-thread synchronization or variable locking functions and routines. Pylon is designed not to need them, through the structuring of boolean signal arrays, and access loops. Thus Pylon can operate with superior speed on multicore systems, and is only limited by the processors' I/O wait from transferring data between cores and, obviously, between the processor and RAM. Each thread only changes its behavior when signaled to do so, through the modification of a global or localized boolean value, thus no variables are locked, and no blocking or halts in thread execution occurs.

### A few notes: ###
  * the [zlib v1.2.5](http://zlib.net/) library is included in the source.
  * the [simpleini](http://code.jellycan.com/simpleini/) parser can be found in the source.
  * the [minizip](http://www.winimage.com/zLibDll/minizip.html) zlib examples are included in the source but slightly modified for my purposes.
  * I use the [Code::Blocks IDE](http://www.codeblocks.org/) for development.

Thanks [Python](http://www.python.org/) for being so easily learned ...
Thank you [NeHe](http://nehe.gamedev.net/) for introducing me to OpenGL those many moons ago...

![http://pylon.googlecode.com/svn/wiki/images/pylon_logo_512_x_512.png](http://pylon.googlecode.com/svn/wiki/images/pylon_logo_512_x_512.png)

## A Note on Licenses: ##
Pylon includes many opensource sources and thus has many different licenses, and after a length of time some of these licenses may have been forgotten, relegated to some unknown piece of code, or lost entirely. I cannot completely confirm the origins of some functions, although such functions are rare. Since Pylon contains code from the previously mentioned libraries and examples above, Pylon must also use the licenses of said components.