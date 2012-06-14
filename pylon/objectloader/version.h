#ifndef OBJECTLOADER_VERSION_H
#define OBJECTLOADER_VERSION_H

namespace ObjectLoaderAutoVersion{
	
	//Date Version Types
	static const char  _DATE[] = "10";
	static const char  _MONTH[] = "06";
	static const char  _YEAR[] = "2012";
	static const char  _UBUNTU_VERSION_STYLE[] = "12.06";
	
	//Software Status
	static const char  _STATUS[] = "Alpha";
	static const char  _STATUS_SHORT[] = "a";
	
	//Standard Version Type
	static const long  _MAJOR = 0;
	static const long  _MINOR = 0;
	static const long  _BUILD = 79;
	static const long  _REVISION = 435;
	
	//Miscellaneous Version Types
	static const long  _BUILDS_COUNT = 286;
	#define  _RC_FILEVERSION 0,0,79,435
	#define  _RC_FILEVERSION_STRING "0, 0, 79, 435\0"
	static const char  _FULLVERSION_STRING[] = "0.0.79.435";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long  _BUILD_HISTORY = 79;
	

}
#endif //OBJECTLOADER_VERSION_H
