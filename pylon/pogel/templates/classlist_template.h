#ifndef CLASSLIST_TEMPLATE_H_INCLUDED
#define CLASSLIST_TEMPLATE_H_INCLUDED

#include "../../lists/classlist_template.h"

template<class T> class CLASSLIST : public ClassList<T>
{
    public:
        CLASSLIST() : ClassList<T>() {}
        CLASSLIST(T *c, unsigned int l) : ClassList<T>(c,l) {}
		CLASSLIST(unsigned int i) : ClassList<T>(i) {}
};
//#define CLASSLIST ClassList
//typedef ClassList CLASSLIST;

#endif // CLASSLIST_TEMPLATE_H_INCLUDED
