#ifndef POGEL_VERSION_H
#define POGEL_VERSION_H

namespace PogelAutoVersion{
	
	//Date Version Types
	static const char  _DATE[] = "19";
	static const char  _MONTH[] = "04";
	static const char  _YEAR[] = "2012";
	static const char  _UBUNTU_VERSION_STYLE[] = "12.04";
	
	//Software Status
	static const char  _STATUS[] = "Beta";
	static const char  _STATUS_SHORT[] = "b";
	
	//Standard Version Type
	static const long  _MAJOR = 0;
	static const long  _MINOR = 2;
	static const long  _BUILD = 104;
	static const long  _REVISION = 600;
	
	//Miscellaneous Version Types
	static const long  _BUILDS_COUNT = 325;
	#define  _RC_FILEVERSION 0,2,104,600
	#define  _RC_FILEVERSION_STRING "0, 2, 104, 600\0"
	static const char  _FULLVERSION_STRING[] = "0.2.104.600";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long  _BUILD_HISTORY = 4;
	

}
#endif //POGEL_VERSION_H
