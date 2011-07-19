#ifndef POGELINTERFACE_VERSION_H
#define POGELINTERFACE_VERSION_H

namespace pogelInterfaceAutoVersion{
	
	//Date Version Types
	static const char DATE[] = "18";
	static const char MONTH[] = "07";
	static const char YEAR[] = "2011";
	static const char UBUNTU_VERSION_STYLE[] = "11.07";
	
	//Software Status
	static const char STATUS[] = "Beta";
	static const char STATUS_SHORT[] = "b";
	
	//Standard Version Type
	static const long MAJOR = 0;
	static const long MINOR = 1;
	static const long BUILD = 6;
	static const long REVISION = 25;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 210;
	#define RC_FILEVERSION 0,1,6,25
	#define RC_FILEVERSION_STRING "0, 1, 6, 25\0"
	static const char FULLVERSION_STRING[] = "0.1.6.25";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 6;
	

}
#endif //POGELINTERFACE_VERSION_H
