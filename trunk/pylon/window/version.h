#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char  _DATE[] = "24";
	static const char  _MONTH[] = "05";
	static const char  _YEAR[] = "2012";
	static const char  _UBUNTU_VERSION_STYLE[] = "12.05";
	
	//Software Status
	static const char  _STATUS[] = "Alpha";
	static const char  _STATUS_SHORT[] = "a";
	
	//Standard Version Type
	static const long  _MAJOR = 0;
	static const long  _MINOR = 5;
	static const long  _BUILD = 514;
	static const long  _REVISION = 2751;
	
	//Miscellaneous Version Types
	static const long  _BUILDS_COUNT = 6303;
	#define  _RC_FILEVERSION 0,5,514,2751
	#define  _RC_FILEVERSION_STRING "0, 5, 514, 2751\0"
	static const char  _FULLVERSION_STRING[] = "0.5.514.2751";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long  _BUILD_HISTORY = 11;
	

}
#endif //VERSION_H
