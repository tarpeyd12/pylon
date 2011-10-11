#ifndef HASHLIST_TEMPLATE_H_INCLUDED
#define HASHLIST_TEMPLATE_H_INCLUDED

#include "../../lists/hashlist_template.h"

template<class T> class HASHLIST : public HashList<T>
{
    public:
        HASHLIST() : HashList<T>() {}
        HASHLIST(unsigned int s) : HashList<T>(s) {}
		HASHLIST(CLASSLIST<T> *l) : HashList<T>(l) {}
		HASHLIST(ClassList<T> *l) : HashList<T>(l) {}
};
//#define HASHLIST HashList
//typedef HashList HASHLIST;

#endif // HASHLIST_TEMPLATE_H_INCLUDED
