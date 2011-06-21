#ifndef THREADS_VERSION_H
#define THREADS_VERSION_H

namespace ThreadsAutoVersion{
	
	//Date Version Types
	static const char DATE[] = "20";
	static const char MONTH[] = "06";
	static const char YEAR[] = "2011";
	static const char UBUNTU_VERSION_STYLE[] = "11.06";
	
	//Software Status
	static const char STATUS[] = "Beta";
	static const char STATUS_SHORT[] = "b";
	
	//Standard Version Type
	static const long MAJOR = 0;
	static const long MINOR = 2;
	static const long BUILD = 4;
	static const long REVISION = 20;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 204;
	#define RC_FILEVERSION 0,2,4,20
	#define RC_FILEVERSION_STRING "0, 2, 4, 20\0"
	static const char FULLVERSION_STRING[] = "0.2.4.20";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 4;
	

}
#endif //THREADS_VERSION_H
