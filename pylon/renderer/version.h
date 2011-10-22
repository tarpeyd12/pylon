#ifndef RENDERER_VERSION_H
#define RENDERER_VERSION_H

namespace RendererAutoVersion{
	
	//Date Version Types
	static const char  _DATE[] = "18";
	static const char  _MONTH[] = "10";
	static const char  _YEAR[] = "2011";
	static const char  _UBUNTU_VERSION_STYLE[] = "11.10";
	
	//Software Status
	static const char  _STATUS[] = "Beta";
	static const char  _STATUS_SHORT[] = "b";
	
	//Standard Version Type
	static const long  _MAJOR = 0;
	static const long  _MINOR = 1;
	static const long  _BUILD = 35;
	static const long  _REVISION = 214;
	
	//Miscellaneous Version Types
	static const long  _BUILDS_COUNT = 234;
	#define  _RC_FILEVERSION 0,1,35,214
	#define  _RC_FILEVERSION_STRING "0, 1, 35, 214\0"
	static const char  _FULLVERSION_STRING[] = "0.1.35.214";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long  _BUILD_HISTORY = 35;
	

}
#endif //RENDERER_VERSION_H
