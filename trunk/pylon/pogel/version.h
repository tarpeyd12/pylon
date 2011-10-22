#ifndef POGEL_VERSION_H
#define POGEL_VERSION_H

namespace PogelAutoVersion{
	
	//Date Version Types
	static const char  _DATE[] = "14";
	static const char  _MONTH[] = "10";
	static const char  _YEAR[] = "2011";
	static const char  _UBUNTU_VERSION_STYLE[] = "11.10";
	
	//Software Status
	static const char  _STATUS[] = "Beta";
	static const char  _STATUS_SHORT[] = "b";
	
	//Standard Version Type
	static const long  _MAJOR = 0;
	static const long  _MINOR = 1;
	static const long  _BUILD = 38;
	static const long  _REVISION = 211;
	
	//Miscellaneous Version Types
	static const long  _BUILDS_COUNT = 246;
	#define  _RC_FILEVERSION 0,1,38,211
	#define  _RC_FILEVERSION_STRING "0, 1, 38, 211\0"
	static const char  _FULLVERSION_STRING[] = "0.1.38.211";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long  _BUILD_HISTORY = 38;
	

}
#endif //POGEL_VERSION_H
