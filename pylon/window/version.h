#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char  _DATE[] = "16";
	static const char  _MONTH[] = "05";
	static const char  _YEAR[] = "2011";
	static const char  _UBUNTU_VERSION_STYLE[] = "11.05";
	
	//Software Status
	static const char  _STATUS[] = "Alpha";
	static const char  _STATUS_SHORT[] = "a";
	
	//Standard Version Type
	static const long  _MAJOR = 0;
	static const long  _MINOR = 0;
	static const long  _BUILD = 41;
	static const long  _REVISION = 210;
	
	//Miscellaneous Version Types
	static const long  _BUILDS_COUNT = 179;
	#define  _RC_FILEVERSION 0,0,41,210
	#define  _RC_FILEVERSION_STRING "0, 0, 41, 210\0"
	static const char  _FULLVERSION_STRING[] = "0.0.41.210";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long  _BUILD_HISTORY = 41;
	

}
#endif //VERSION_H
