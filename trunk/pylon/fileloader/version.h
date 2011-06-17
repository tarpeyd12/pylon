#ifndef FILELOADER_VERSION_H
#define FILELOADER_VERSION_H

namespace FileLoaderAutoVersion{
	
	//Date Version Types
	static const char DATE[] = "16";
	static const char MONTH[] = "06";
	static const char YEAR[] = "2011";
	static const char UBUNTU_VERSION_STYLE[] = "11.06";
	
	//Software Status
	static const char STATUS[] = "Beta";
	static const char STATUS_SHORT[] = "b";
	
	//Standard Version Type
	static const long MAJOR = 0;
	static const long MINOR = 1;
	static const long BUILD = 23;
	static const long REVISION = 151;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 226;
	#define RC_FILEVERSION 0,1,23,151
	#define RC_FILEVERSION_STRING "0, 1, 23, 151\0"
	static const char FULLVERSION_STRING[] = "0.1.23.151";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 23;
	

}
#endif //FILELOADER_VERSION_H
