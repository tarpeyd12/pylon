# Setting up Code::Blocks to develop Pylon #

  1. Install Code::Blocks in the usual way.
  1. when that is finished, do no open pylon. open the C::B IDE then go to "Settings" -> "Global Variables ..."
  1. under the "Current Set" press "New" and type in '`pylon`', without quotes, then press "Ok"
> > http://pylon.googlecode.com/svn/wiki/images/pylon_setup_1.JPG
  1. under the "Current Variable" press "New" and type in '`python`' without quotes, then press "Ok"
  1. in the variable '`python`' the sections should be as follows:
    * **base** to "`C:\Python27`"
    * **include** to "`C:\Python27\include`"
    * **lib** to "`C:\Python27\libs`"
    * **lflags** to "`python27`"
> > it should look like this:
> > > http://pylon.googlecode.com/svn/wiki/images/pylon_setup_2_python.JPG
  1. under the "Current Variable" press "New" and type in '`base`' without quotes, then press "Ok"
  1. in the variable '`base`' the sections should be as follows:
    * **base** to "`C:\Program Files\CodeBlocks\MinGW`"
    * **include** to "`C:\Program Files\CodeBlocks\MinGW\include`"
    * **lib** to "`C:\Program Files\CodeBlocks\MinGW\lib`"

> > it should look like this:
> > > http://pylon.googlecode.com/svn/wiki/images/pylon_setup_3_base.JPG
  1. under the "Current Variable" select "base" then press "Clone" and type in '`opengl`' without quotes, then press "Ok"
  1. in the variable '`opengl`' the sections should be as follows:
    * **base** to "`C:\Program Files\CodeBlocks\MinGW`"
    * **include** to "`C:\Program Files\CodeBlocks\MinGW\include`"
    * **lib** to "`C:\Program Files\CodeBlocks\MinGW\lib`"
    * **lflags** to "`opengl32`"
  1. under the "Current Variable" select "base" then press "Clone" and type in '`glu`' without quotes, then press "Ok"
  1. in the variable '`glu`' the sections should be as follows:
    * **base** to "`C:\Program Files\CodeBlocks\MinGW`"
    * **include** to "`C:\Program Files\CodeBlocks\MinGW\include`"
    * **lib** to "`C:\Program Files\CodeBlocks\MinGW\lib`"
    * **lflags** to "`glu32`"
  1. under the "Current Variable" select "base" then press "Clone" and type in '`glut`' without quotes, then press "Ok"
  1. in the variable '`glut`' the sections should be as follows:
    * **base** to "`C:\Program Files\CodeBlocks\MinGW`"
    * **include** to "`C:\Program Files\CodeBlocks\MinGW\include`"
    * **lib** to "`C:\Program Files\CodeBlocks\MinGW\lib`"
    * **lflags** to "`glut32`"

## Troubleshooting ##
  * Step 3 may be an issue, and is not really needed, so it is fine to ignore it.