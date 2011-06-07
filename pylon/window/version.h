#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char  _DATE[] = "06";
	static const char  _MONTH[] = "06";
	static const char  _YEAR[] = "2011";
	static const char  _UBUNTU_VERSION_STYLE[] = "11.06";
	
	//Software Status
	static const char  _STATUS[] = "Alpha";
	static const char  _STATUS_SHORT[] = "a";
	
	//Standard Version Type
	static const long  _MAJOR = 0;
	static const long  _MINOR = 0;
	static const long  _BUILD = 91;
	static const long  _REVISION = 493;
	
	//Miscellaneous Version Types
	static const long  _BUILDS_COUNT = 651;
	#define  _RC_FILEVERSION 0,0,91,493
	#define  _RC_FILEVERSION_STRING "0, 0, 91, 493\0"
	static const char  _FULLVERSION_STRING[] = "0.0.91.493";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long  _BUILD_HISTORY = 91;
	

}
#endif //VERSION_H
