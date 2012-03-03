#ifndef SCRIPTENGINE_VERSION_H
#define SCRIPTENGINE_VERSION_H

namespace ScriptEngineAutoVersion{
	
	//Date Version Types
	static const char  _DATE[] = "26";
	static const char  _MONTH[] = "02";
	static const char  _YEAR[] = "2012";
	static const char  _UBUNTU_VERSION_STYLE[] = "12.02";
	
	//Software Status
	static const char  _STATUS[] = "Beta";
	static const char  _STATUS_SHORT[] = "b";
	
	//Standard Version Type
	static const long  _MAJOR = 0;
	static const long  _MINOR = 1;
	static const long  _BUILD = 1;
	static const long  _REVISION = 1;
	
	//Miscellaneous Version Types
	static const long  _BUILDS_COUNT = 200;
	#define  _RC_FILEVERSION 0,1,1,1
	#define  _RC_FILEVERSION_STRING "0, 1, 1, 1\0"
	static const char  _FULLVERSION_STRING[] = "0.1.1.1";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long  _BUILD_HISTORY = 1;
	

}
#endif //SCRIPTENGINE_VERSION_H
