#ifndef FILELOADER_VERSION_H
#define FILELOADER_VERSION_H

namespace FileLoaderAutoVersion{
	
	//Date Version Types
	static const char  _DATE[] = "18";
	static const char  _MONTH[] = "11";
	static const char  _YEAR[] = "2011";
	static const char  _UBUNTU_VERSION_STYLE[] = "11.11";
	
	//Software Status
	static const char  _STATUS[] = "Beta";
	static const char  _STATUS_SHORT[] = "b";
	
	//Standard Version Type
	static const long  _MAJOR = 0;
	static const long  _MINOR = 1;
	static const long  _BUILD = 25;
	static const long  _REVISION = 165;
	
	//Miscellaneous Version Types
	static const long  _BUILDS_COUNT = 228;
	#define  _RC_FILEVERSION 0,1,25,165
	#define  _RC_FILEVERSION_STRING "0, 1, 25, 165\0"
	static const char  _FULLVERSION_STRING[] = "0.1.25.165";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long  _BUILD_HISTORY = 25;
	

}
#endif //FILELOADER_VERSION_H
