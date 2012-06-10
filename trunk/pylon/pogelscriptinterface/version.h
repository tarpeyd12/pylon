#ifndef POGELINTERFACE_VERSION_H
#define POGELINTERFACE_VERSION_H

namespace pogelInterfaceAutoVersion{
	
	//Date Version Types
	static const char  _DATE[] = "10";
	static const char  _MONTH[] = "06";
	static const char  _YEAR[] = "2012";
	static const char  _UBUNTU_VERSION_STYLE[] = "12.06";
	
	//Software Status
	static const char  _STATUS[] = "Beta";
	static const char  _STATUS_SHORT[] = "b";
	
	//Standard Version Type
	static const long  _MAJOR = 0;
	static const long  _MINOR = 1;
	static const long  _BUILD = 31;
	static const long  _REVISION = 200;
	
	//Miscellaneous Version Types
	static const long  _BUILDS_COUNT = 235;
	#define  _RC_FILEVERSION 0,1,31,200
	#define  _RC_FILEVERSION_STRING "0, 1, 31, 200\0"
	static const char  _FULLVERSION_STRING[] = "0.1.31.200";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long  _BUILD_HISTORY = 31;
	

}
#endif //POGELINTERFACE_VERSION_H
