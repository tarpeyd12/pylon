#ifndef RENDERER_VERSION_H
#define RENDERER_VERSION_H

namespace RendererAutoVersion{
	
	//Date Version Types
	static const char DATE[] = "27";
	static const char MONTH[] = "09";
	static const char YEAR[] = "2011";
	static const char UBUNTU_VERSION_STYLE[] = "11.09";
	
	//Software Status
	static const char STATUS[] = "Beta";
	static const char STATUS_SHORT[] = "b";
	
	//Standard Version Type
	static const long MAJOR = 0;
	static const long MINOR = 1;
	static const long BUILD = 30;
	static const long REVISION = 187;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 229;
	#define RC_FILEVERSION 0,1,30,187
	#define RC_FILEVERSION_STRING "0, 1, 30, 187\0"
	static const char FULLVERSION_STRING[] = "0.1.30.187";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 30;
	

}
#endif //RENDERER_VERSION_H
