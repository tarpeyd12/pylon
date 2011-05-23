#ifndef OBJECTLOADER_VERSION_H
#define OBJECTLOADER_VERSION_H

namespace ObjectLoaderAutoVersion{
	
	//Date Version Types
	static const char DATE[] = "23";
	static const char MONTH[] = "05";
	static const char YEAR[] = "2011";
	static const char UBUNTU_VERSION_STYLE[] = "11.05";
	
	//Software Status
	static const char STATUS[] = "Alpha";
	static const char STATUS_SHORT[] = "a";
	
	//Standard Version Type
	static const long MAJOR = 0;
	static const long MINOR = 0;
	static const long BUILD = 19;
	static const long REVISION = 100;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 225;
	#define RC_FILEVERSION 0,0,19,100
	#define RC_FILEVERSION_STRING "0, 0, 19, 100\0"
	static const char FULLVERSION_STRING[] = "0.0.19.100";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 19;
	

}
#endif //OBJECTLOADER_VERSION_H
