#ifndef FILELOADER_VERSION_H
#define FILELOADER_VERSION_H

namespace FileLoaderAutoVersion{
	
	//Date Version Types
	static const char DATE[] = "18";
	static const char MONTH[] = "05";
	static const char YEAR[] = "2011";
	static const char UBUNTU_VERSION_STYLE[] = "11.05";
	
	//Software Status
	static const char STATUS[] = "Beta";
	static const char STATUS_SHORT[] = "b";
	
	//Standard Version Type
	static const long MAJOR = 0;
	static const long MINOR = 1;
	static const long BUILD = 0;
	static const long REVISION = 0;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 201;
	#define RC_FILEVERSION 0,1,0,0
	#define RC_FILEVERSION_STRING "0, 1, 0, 0\0"
	static const char FULLVERSION_STRING[] = "0.1.0.0";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 0;
	

}
#endif //FILELOADER_VERSION_H
