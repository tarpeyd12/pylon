#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char  _DATE[] = "09";
	static const char  _MONTH[] = "04";
	static const char  _YEAR[] = "2012";
	static const char  _UBUNTU_VERSION_STYLE[] = "12.04";
	
	//Software Status
	static const char  _STATUS[] = "Alpha";
	static const char  _STATUS_SHORT[] = "a";
	
	//Standard Version Type
	static const long  _MAJOR = 0;
	static const long  _MINOR = 4;
	static const long  _BUILD = 420;
	static const long  _REVISION = 2209;
	
	//Miscellaneous Version Types
	static const long  _BUILDS_COUNT = 5547;
	#define  _RC_FILEVERSION 0,4,420,2209
	#define  _RC_FILEVERSION_STRING "0, 4, 420, 2209\0"
	static const char  _FULLVERSION_STRING[] = "0.4.420.2209";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long  _BUILD_HISTORY = 17;
	

}
#endif //VERSION_H
