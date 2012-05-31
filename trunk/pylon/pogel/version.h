#ifndef POGEL_VERSION_H
#define POGEL_VERSION_H

namespace PogelAutoVersion{
	
	//Date Version Types
	static const char  _DATE[] = "30";
	static const char  _MONTH[] = "05";
	static const char  _YEAR[] = "2012";
	static const char  _UBUNTU_VERSION_STYLE[] = "12.05";
	
	//Software Status
	static const char  _STATUS[] = "Beta";
	static const char  _STATUS_SHORT[] = "b";
	
	//Standard Version Type
	static const long  _MAJOR = 0;
	static const long  _MINOR = 2;
	static const long  _BUILD = 108;
	static const long  _REVISION = 620;
	
	//Miscellaneous Version Types
	static const long  _BUILDS_COUNT = 328;
	#define  _RC_FILEVERSION 0,2,108,620
	#define  _RC_FILEVERSION_STRING "0, 2, 108, 620\0"
	static const char  _FULLVERSION_STRING[] = "0.2.108.620";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long  _BUILD_HISTORY = 8;
	

}
#endif //POGEL_VERSION_H
