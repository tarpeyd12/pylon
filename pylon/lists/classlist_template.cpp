#include "classlist_template.h"

#include <stdlib.h>

using namespace std;

template < typename DataType, typename ComparisonType >
DataWraper<DataType,ComparisonType>::DataWraper()
{

}

template < typename DataType, typename ComparisonType >
DataWraper<DataType,ComparisonType>::DataWraper(DataType d, ComparisonType v)
{
    this->data = d;
    this->value = v;
}

template < typename T, typename C >
T*
ClassList<T,C>::getList()
{
    return list;
}

template < typename T, typename C >
ClassList<T,C>::ClassList()
{
    list=NULL;
    overhead=0;
    len=0;
    sc=false;
    sortFunction=NULL;
}

template < typename T, typename C >
ClassList<T,C>::ClassList(T *c, unsigned int l)
{
    list=c;
    overhead=0;
    len=l;
    sortFunction=NULL;
}

template < typename T, typename C >
ClassList<T,C>::ClassList(unsigned int i)
{
     list=new T[i];
     overhead=i;
     len=0;
     sc=false;
     sortFunction=NULL;
}

template < typename T, typename C >
ClassList<T,C>::~ClassList()
{
    if(list!=NULL)
        delete[]list;
    list=NULL;
    overhead=len=0;
    sortFunction=NULL;
}

template < typename T, typename C >
void
ClassList<T,C>::clear()
{
    if(list!=NULL)
        delete[]list;
    list=NULL;
    len=0;
    overhead=0;
}

template < typename T, typename C >
void
ClassList<T,C>::safeclear()
{

    if(list!=NULL)
    {
        while(length())
            remove(length()-1);
        //delete[]list;
    }
    list=NULL;
    len=0;
    overhead=0;
}

template < typename T, typename C >
void
ClassList<T,C>::nullify()
{
    list=NULL;
    len=0;
    overhead=0;
}

template < typename T, typename C >
unsigned int
ClassList<T,C>::length()
{
    return len;
}

template < typename T, typename C >
void
ClassList<T,C>::add(T l)
{
    if(len<overhead)
        list[len++]=l;
    else {
        T *tmp = new T[length()+1];
        for(unsigned int i=0;i<length();i++)
            tmp[i]=list[i];
        tmp[len++]=l;
        if(list!=NULL)
            delete[]list;
        list=tmp;
    }
}

template < typename T, typename C >
void
ClassList<T,C>::add(T *c, unsigned int l)
{
    if(c==NULL||l==0)
        return;
    T *tmp = new T[length()+l];
    for(unsigned int i=0;i<(length()>l?length():l);i++)
    {
        if(i<length())
            tmp[i]=list[i];
        if(i<l)
            tmp[i+length()]=c[i];
    }
    len+=l;
    if(list!=NULL)
        delete[]list;
    list=tmp;
}

template < typename T, typename C >
void
ClassList<T,C>::replace(unsigned int l, T c)
{
    if(l>=length())
        return;
    list[l] = c;
}

template < typename T, typename C >
void
ClassList<T,C>::remove(unsigned int l)
{
    if(l>=length())
        return;
    T *tmp = new T[--len];
    for(unsigned int i=0;i<length();i++)
        if(i<l)
            tmp[i]=list[i];
        else
            tmp[i]=list[i+1];
    if(list!=NULL)
        delete[]list;
    list=tmp;
}

template < typename T, typename C >
void
ClassList<T,C>::insert(T c, unsigned int l)
{
    if(l>=length())
        return;
    T *tmp = new T[++len];
    for(unsigned int i=0;i<length()-1;i++)
        if(i<l)
            tmp[i]=list[i];
        else
            tmp[i+1]=list[i];
    tmp[l]=c;
    if(list!=NULL)
        delete[]list;
    list=tmp;
}

template < typename T, typename C >
T
ClassList<T,C>::get(unsigned int i)
{
    //if(i < length())
    return list[i];
}

template < typename T, typename C >
T
ClassList<T,C>::first()
{
    return get(0);
}

template < typename T, typename C >
T
ClassList<T,C>::last()
{
    return get(length()-1);
}

template < typename T, typename C >
T
ClassList<T,C>::operator[] (unsigned int i)
{
    return get(i);
}

template < typename T, typename C >
ClassList<T,C>&
ClassList<T,C>::operator = (ClassList<T,C> c)
{
    if(list!=NULL)
        delete[]list;
    list=c.getList();
    len=c.length();
    return *this;
}

template < typename T, typename C >
ClassList<T,C>
ClassList<T,C>::operator + (T l)
{
    ClassList<T,C> v;
    v.add(getList(),length());
    v.add(l);
    return v;
}

template < typename T, typename C >
ClassList<T,C>&
ClassList<T,C>::operator+= (T l)
{
    add(l);
    return*this;
}

template < typename T, typename C >
ClassList<T,C>
ClassList<T,C>::operator + (ClassList<T,C> l)
{
    ClassList<T,C> v;
    v.add(getList(),length());
    v.add(l.getList(),l.length());
    return v;
}

template < typename T, typename C >
ClassList<T,C>
ClassList<T,C>::operator + (ClassList<T,C> *l)
{
    ClassList<T,C> v;
    v.add(getList(),length());
    v.add(l->getList(),l->length());
    return v;
}

template < typename T, typename C >
ClassList<T,C>&
ClassList<T,C>::operator+= (ClassList<T,C> l)
{
    add(l.getList(),l.length());
    return*this;
}

template < typename T, typename C >
ClassList<T,C>&
ClassList<T,C>::operator+= (ClassList<T,C> *l)
{
    add(l->getList(),l->length());
    return*this;
}

template < typename T, typename C >
ClassList<T,C>
ClassList<T,C>::operator - (unsigned int l)
{
    ClassList<T,C> v;
    v.add(getList(),length());
    v.remove(l);
    return v;
}

template < typename T, typename C >
ClassList<T,C>&
ClassList<T,C>::operator-= (unsigned int l)
{
    remove(l);
    return*this;
}

template < typename T, typename C >
void
ClassList<T,C>::setSortFunc(C sortFunc)
{
    sortFunction = sortFunc;
}

template < typename T, typename C >
void
ClassList<T,C>::sort()
{
    if(sortFunction)
        qsort((void*)list, len, sizeof(T), (int(*)(const void*,const void*))sortFunction);
}

template < typename T, typename C >
void
ClassList<T,C>::sort(C sortFunc)
{
    setSortFunc(sortFunc);
    sort();
}

template < typename T, typename C >
T*
ClassList<T,C>::search(T ind)
{
    if(sortFunction)
        return (T*)bsearch((void*)&ind, (void*)list, len, sizeof(T), (int(*)(const void*,const void*))sortFunction);
    return NULL;
}

template < typename T, typename C >
T*
ClassList<T,C>::search(T ind, C sortFunc)
{
    setSortFunc(sortFunc);
    sort();
    return search(ind);
}
