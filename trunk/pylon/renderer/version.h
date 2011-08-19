#ifndef RENDERER_VERSION_H
#define RENDERER_VERSION_H

namespace RendererAutoVersion{
	
	//Date Version Types
	static const char DATE[] = "11";
	static const char MONTH[] = "08";
	static const char YEAR[] = "2011";
	static const char UBUNTU_VERSION_STYLE[] = "11.08";
	
	//Software Status
	static const char STATUS[] = "Beta";
	static const char STATUS_SHORT[] = "b";
	
	//Standard Version Type
	static const long MAJOR = 0;
	static const long MINOR = 1;
	static const long BUILD = 21;
	static const long REVISION = 145;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 222;
	#define RC_FILEVERSION 0,1,21,145
	#define RC_FILEVERSION_STRING "0, 1, 21, 145\0"
	static const char FULLVERSION_STRING[] = "0.1.21.145";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 21;
	

}
#endif //RENDERER_VERSION_H
