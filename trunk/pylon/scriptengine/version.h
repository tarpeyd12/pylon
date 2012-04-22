#ifndef SCRIPTENGINE_VERSION_H
#define SCRIPTENGINE_VERSION_H

namespace ScriptEngineAutoVersion{
	
	//Date Version Types
	static const char  _DATE[] = "19";
	static const char  _MONTH[] = "04";
	static const char  _YEAR[] = "2012";
	static const char  _UBUNTU_VERSION_STYLE[] = "12.04";
	
	//Software Status
	static const char  _STATUS[] = "Beta";
	static const char  _STATUS_SHORT[] = "b";
	
	//Standard Version Type
	static const long  _MAJOR = 0;
	static const long  _MINOR = 1;
	static const long  _BUILD = 34;
	static const long  _REVISION = 171;
	
	//Miscellaneous Version Types
	static const long  _BUILDS_COUNT = 236;
	#define  _RC_FILEVERSION 0,1,34,171
	#define  _RC_FILEVERSION_STRING "0, 1, 34, 171\0"
	static const char  _FULLVERSION_STRING[] = "0.1.34.171";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long  _BUILD_HISTORY = 34;
	

}
#endif //SCRIPTENGINE_VERSION_H
