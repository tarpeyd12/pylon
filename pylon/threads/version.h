#ifndef THREADS_VERSION_H
#define THREADS_VERSION_H

namespace ThreadsAutoVersion{
	
	//Date Version Types
	static const char  _DATE[] = "31";
	static const char  _MONTH[] = "10";
	static const char  _YEAR[] = "2011";
	static const char  _UBUNTU_VERSION_STYLE[] = "11.10";
	
	//Software Status
	static const char  _STATUS[] = "Beta";
	static const char  _STATUS_SHORT[] = "b";
	
	//Standard Version Type
	static const long  _MAJOR = 0;
	static const long  _MINOR = 2;
	static const long  _BUILD = 10;
	static const long  _REVISION = 59;
	
	//Miscellaneous Version Types
	static const long  _BUILDS_COUNT = 210;
	#define  _RC_FILEVERSION 0,2,10,59
	#define  _RC_FILEVERSION_STRING "0, 2, 10, 59\0"
	static const char  _FULLVERSION_STRING[] = "0.2.10.59";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long  _BUILD_HISTORY = 10;
	

}
#endif //THREADS_VERSION_H
