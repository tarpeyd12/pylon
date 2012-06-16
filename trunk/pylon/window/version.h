#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char  _DATE[] = "15";
	static const char  _MONTH[] = "06";
	static const char  _YEAR[] = "2012";
	static const char  _UBUNTU_VERSION_STYLE[] = "12.06";
	
	//Software Status
	static const char  _STATUS[] = "Alpha";
	static const char  _STATUS_SHORT[] = "a";
	
	//Standard Version Type
	static const long  _MAJOR = 0;
	static const long  _MINOR = 5;
	static const long  _BUILD = 540;
	static const long  _REVISION = 2887;
	
	//Miscellaneous Version Types
	static const long  _BUILDS_COUNT = 7173;
	#define  _RC_FILEVERSION 0,5,540,2887
	#define  _RC_FILEVERSION_STRING "0, 5, 540, 2887\0"
	static const char  _FULLVERSION_STRING[] = "0.5.540.2887";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long  _BUILD_HISTORY = 37;
	

}
#endif //VERSION_H
