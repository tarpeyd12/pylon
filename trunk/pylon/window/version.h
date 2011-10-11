#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char  _DATE[] = "01";
	static const char  _MONTH[] = "10";
	static const char  _YEAR[] = "2011";
	static const char  _UBUNTU_VERSION_STYLE[] = "11.10";
	
	//Software Status
	static const char  _STATUS[] = "Alpha";
	static const char  _STATUS_SHORT[] = "a";
	
	//Standard Version Type
	static const long  _MAJOR = 0;
	static const long  _MINOR = 2;
	static const long  _BUILD = 253;
	static const long  _REVISION = 1369;
	
	//Miscellaneous Version Types
	static const long  _BUILDS_COUNT = 2234;
	#define  _RC_FILEVERSION 0,2,253,1369
	#define  _RC_FILEVERSION_STRING "0, 2, 253, 1369\0"
	static const char  _FULLVERSION_STRING[] = "0.2.253.1369";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long  _BUILD_HISTORY = 53;
	

}
#endif //VERSION_H
