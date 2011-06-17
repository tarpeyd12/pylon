#ifndef RENDERER_VERSION_H
#define RENDERER_VERSION_H

namespace RendererAutoVersion{
	
	//Date Version Types
	static const char DATE[] = "09";
	static const char MONTH[] = "06";
	static const char YEAR[] = "2011";
	static const char UBUNTU_VERSION_STYLE[] = "11.06";
	
	//Software Status
	static const char STATUS[] = "Beta";
	static const char STATUS_SHORT[] = "b";
	
	//Standard Version Type
	static const long MAJOR = 0;
	static const long MINOR = 1;
	static const long BUILD = 1;
	static const long REVISION = 7;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 200;
	#define RC_FILEVERSION 0,1,1,7
	#define RC_FILEVERSION_STRING "0, 1, 1, 7\0"
	static const char FULLVERSION_STRING[] = "0.1.1.7";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 1;
	

}
#endif //RENDERER_VERSION_H
