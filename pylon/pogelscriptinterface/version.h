#ifndef POGELINTERFACE_VERSION_H
#define POGELINTERFACE_VERSION_H

namespace pogelInterfaceAutoVersion{
	
	//Date Version Types
	static const char  _DATE[] = "04";
	static const char  _MONTH[] = "03";
	static const char  _YEAR[] = "2012";
	static const char  _UBUNTU_VERSION_STYLE[] = "12.03";
	
	//Software Status
	static const char  _STATUS[] = "Beta";
	static const char  _STATUS_SHORT[] = "b";
	
	//Standard Version Type
	static const long  _MAJOR = 0;
	static const long  _MINOR = 1;
	static const long  _BUILD = 21;
	static const long  _REVISION = 121;
	
	//Miscellaneous Version Types
	static const long  _BUILDS_COUNT = 226;
	#define  _RC_FILEVERSION 0,1,21,121
	#define  _RC_FILEVERSION_STRING "0, 1, 21, 121\0"
	static const char  _FULLVERSION_STRING[] = "0.1.21.121";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long  _BUILD_HISTORY = 21;
	

}
#endif //POGELINTERFACE_VERSION_H
