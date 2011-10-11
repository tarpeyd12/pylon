#ifndef POGEL_VERSION_H
#define POGEL_VERSION_H

namespace PogelAutoVersion{
	
	//Date Version Types
	static const char  _DATE[] = "30";
	static const char  _MONTH[] = "09";
	static const char  _YEAR[] = "2011";
	static const char  _UBUNTU_VERSION_STYLE[] = "11.09";
	
	//Software Status
	static const char  _STATUS[] = "Beta";
	static const char  _STATUS_SHORT[] = "b";
	
	//Standard Version Type
	static const long  _MAJOR = 0;
	static const long  _MINOR = 1;
	static const long  _BUILD = 36;
	static const long  _REVISION = 198;
	
	//Miscellaneous Version Types
	static const long  _BUILDS_COUNT = 245;
	#define  _RC_FILEVERSION 0,1,36,198
	#define  _RC_FILEVERSION_STRING "0, 1, 36, 198\0"
	static const char  _FULLVERSION_STRING[] = "0.1.36.198";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long  _BUILD_HISTORY = 36;
	

}
#endif //POGEL_VERSION_H
