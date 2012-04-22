#ifndef POGELINTERFACE_VERSION_H
#define POGELINTERFACE_VERSION_H

namespace pogelInterfaceAutoVersion{
	
	//Date Version Types
	static const char  _DATE[] = "21";
	static const char  _MONTH[] = "04";
	static const char  _YEAR[] = "2012";
	static const char  _UBUNTU_VERSION_STYLE[] = "12.04";
	
	//Software Status
	static const char  _STATUS[] = "Beta";
	static const char  _STATUS_SHORT[] = "b";
	
	//Standard Version Type
	static const long  _MAJOR = 0;
	static const long  _MINOR = 1;
	static const long  _BUILD = 25;
	static const long  _REVISION = 158;
	
	//Miscellaneous Version Types
	static const long  _BUILDS_COUNT = 230;
	#define  _RC_FILEVERSION 0,1,25,158
	#define  _RC_FILEVERSION_STRING "0, 1, 25, 158\0"
	static const char  _FULLVERSION_STRING[] = "0.1.25.158";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long  _BUILD_HISTORY = 25;
	

}
#endif //POGELINTERFACE_VERSION_H
