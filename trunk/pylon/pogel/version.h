#ifndef POGEL_VERSION_H
#define POGEL_VERSION_H

namespace PogelAutoVersion{
	
	//Date Version Types
	static const char DATE[] = "19";
	static const char MONTH[] = "07";
	static const char YEAR[] = "2011";
	static const char UBUNTU_VERSION_STYLE[] = "11.07";
	
	//Software Status
	static const char STATUS[] = "Beta";
	static const char STATUS_SHORT[] = "b";
	
	//Standard Version Type
	static const long MAJOR = 0;
	static const long MINOR = 1;
	static const long BUILD = 16;
	static const long REVISION = 87;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 217;
	#define RC_FILEVERSION 0,1,16,87
	#define RC_FILEVERSION_STRING "0, 1, 16, 87\0"
	static const char FULLVERSION_STRING[] = "0.1.16.87";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 16;
	

}
#endif //POGEL_VERSION_H
