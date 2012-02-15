#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char  _DATE[] = "14";
	static const char  _MONTH[] = "02";
	static const char  _YEAR[] = "2012";
	static const char  _UBUNTU_VERSION_STYLE[] = "12.02";
	
	//Software Status
	static const char  _STATUS[] = "Alpha";
	static const char  _STATUS_SHORT[] = "a";
	
	//Standard Version Type
	static const long  _MAJOR = 0;
	static const long  _MINOR = 3;
	static const long  _BUILD = 386;
	static const long  _REVISION = 2023;
	
	//Miscellaneous Version Types
	static const long  _BUILDS_COUNT = 4220;
	#define  _RC_FILEVERSION 0,3,386,2023
	#define  _RC_FILEVERSION_STRING "0, 3, 386, 2023\0"
	static const char  _FULLVERSION_STRING[] = "0.3.386.2023";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long  _BUILD_HISTORY = 86;
	

}
#endif //VERSION_H
