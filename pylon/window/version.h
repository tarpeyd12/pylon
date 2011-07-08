#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char  _DATE[] = "08";
	static const char  _MONTH[] = "07";
	static const char  _YEAR[] = "2011";
	static const char  _UBUNTU_VERSION_STYLE[] = "11.07";
	
	//Software Status
	static const char  _STATUS[] = "Alpha";
	static const char  _STATUS_SHORT[] = "a";
	
	//Standard Version Type
	static const long  _MAJOR = 0;
	static const long  _MINOR = 1;
	static const long  _BUILD = 152;
	static const long  _REVISION = 784;
	
	//Miscellaneous Version Types
	static const long  _BUILDS_COUNT = 861;
	#define  _RC_FILEVERSION 0,1,152,784
	#define  _RC_FILEVERSION_STRING "0, 1, 152, 784\0"
	static const char  _FULLVERSION_STRING[] = "0.1.152.784";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long  _BUILD_HISTORY = 52;
	

}
#endif //VERSION_H
