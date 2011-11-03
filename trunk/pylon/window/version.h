#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char  _DATE[] = "03";
	static const char  _MONTH[] = "11";
	static const char  _YEAR[] = "2011";
	static const char  _UBUNTU_VERSION_STYLE[] = "11.11";
	
	//Software Status
	static const char  _STATUS[] = "Alpha";
	static const char  _STATUS_SHORT[] = "a";
	
	//Standard Version Type
	static const long  _MAJOR = 0;
	static const long  _MINOR = 3;
	static const long  _BUILD = 337;
	static const long  _REVISION = 1785;
	
	//Miscellaneous Version Types
	static const long  _BUILDS_COUNT = 3384;
	#define  _RC_FILEVERSION 0,3,337,1785
	#define  _RC_FILEVERSION_STRING "0, 3, 337, 1785\0"
	static const char  _FULLVERSION_STRING[] = "0.3.337.1785";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long  _BUILD_HISTORY = 37;
	

}
#endif //VERSION_H
