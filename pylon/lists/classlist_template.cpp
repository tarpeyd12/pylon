#include "classlist_template.h"

#include <stdlib.h>

using namespace std;

template <typename T>
T* ClassList<T>::getList()
{
    return list;
}

template <typename T>
ClassList<T>::ClassList()
{
    list=NULL;
    overhead=0;
    len=0;
    sc=false;
    sortFunction=NULL;
}

template <typename T>
ClassList<T>::ClassList(T *c, unsigned int l)
{
    list=c;
    overhead=0;
    len=l;
    sortFunction=NULL;
}

template <typename T>
ClassList<T>::ClassList(unsigned int i)
{
     list=new T[i];
     overhead=i;
     len=0;
     sc=false;
     sortFunction=NULL;
}

template <typename T>
ClassList<T>::~ClassList()
{
    if(list!=NULL)
        delete[]list;
    list=NULL;
    overhead=len=0;
    sortFunction=NULL;
}

template <typename T>
void ClassList<T>::clear()
{
    if(list!=NULL)
        delete[]list;
    list=NULL;
    len=0;
    overhead=0;
}

template <typename T>
void ClassList<T>::safeclear()
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

template <typename T>
void ClassList<T>::nullify()
{
    list=NULL;
    len=0;
    overhead=0;
}

template <typename T>
unsigned int ClassList<T>::length()
{
    return len;
}

template <typename T>
void ClassList<T>::add(T l)
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

template <typename T>
void ClassList<T>::add(T *c, unsigned int l)
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

template <typename T>
void ClassList<T>::remove(unsigned int l)
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

template <typename T>
void ClassList<T>::insert(T c, unsigned int l)
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

template <typename T>
T ClassList<T>::get(unsigned int i)
{
    return list[i];
}

template <typename T>
T ClassList<T>::first()
{
    return get(0);
}

template <typename T>
T ClassList<T>::last()
{
    return get(length()-1);
}

template <typename T>
T ClassList<T>::operator[] (unsigned int i)
{
    return get(i);
}

template <typename T>
ClassList<T>& ClassList<T>::operator = (ClassList<T> c)
{
    if(list!=NULL)
        delete[]list;
    list=c.getList();
    len=c.length();
    return *this;
}

template <typename T>
ClassList<T> ClassList<T>::operator + (T l)
{
    ClassList<T> v;
    v.add(getList(),length());
    v.add(l);
    return v;
}

template <typename T>
ClassList<T>& ClassList<T>::operator+= (T l)
{
    add(l);
    return*this;
}

template <typename T>
ClassList<T>  ClassList<T>::operator + (ClassList<T> l)
{
    ClassList<T> v;
    v.add(getList(),length());
    v.add(l.getList(),l.length());
    return v;
}

template <typename T>
ClassList<T>  ClassList<T>::operator + (ClassList<T> *l)
{
    ClassList<T> v;
    v.add(getList(),length());
    v.add(l->getList(),l->length());
    return v;
}

template <typename T>
ClassList<T>& ClassList<T>::operator+= (ClassList<T> l)
{
    add(l.getList(),l.length());
    return*this;
}

template <typename T>
ClassList<T>& ClassList<T>::operator+= (ClassList<T> *l)
{
    add(l->getList(),l->length());
    return*this;
}

template <typename T>
ClassList<T>  ClassList<T>::operator - (unsigned int l)
{
    ClassList<T> v;
    v.add(getList(),length());
    v.remove(l);
    return v;
}

template <typename T>
ClassList<T>& ClassList<T>::operator-= (unsigned int l)
{
    remove(l);
    return*this;
}

template <typename T>
void ClassList<T>::setSortFunc(int (*sortFunc)(T*,T*))
{
    sortFunction = sortFunc;
}

template <typename T>
void ClassList<T>::sort()
{
    if(sortFunction!=NULL)
        qsort((void*)list, len, sizeof(T), (int(*)(const void*,const void*))sortFunction);
}

template <typename T>
void ClassList<T>::sort(int (*sortFunc)(T*,T*))
{
    setSortFunc(sortFunc);
    sort();
}

template <typename T>
T* ClassList<T>::search(T ind)
{
    if(sortFunction!=NULL)
        return (T*)bsearch((void*)&ind, (void*)list, len, sizeof(T), (int(*)(const void*,const void*))sortFunction);
    else
        return NULL;
}

template <typename T>
T* ClassList<T>::search(T ind, int (*sortFunc)(T*,T*))
{
    setSortFunc(sortFunc);
    sort();
    return search(ind);
}
