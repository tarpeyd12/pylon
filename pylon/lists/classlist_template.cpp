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

template < typename DataType, typename ComparisonType >
DataWraper< DataType, ComparisonType > &
DataWraper< DataType, ComparisonType >::operator = (const DataWraper< DataType, ComparisonType > & other)
{
    memcpy(this,&other,sizeof(other));
    return *this;
}

template < typename T, typename C >
T*
ClassList<T,C>::getList() const
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
ClassList<T,C>::length() const
{
    return len;
}

template < typename T, typename C >
void
ClassList<T,C>::add(const T& l)
{
    if(len<overhead)
        list[len++]=l;
    else {
        //unsigned int nlen = len;
        T *tmp = new T[len+1];
        /*for(unsigned int i=0;i<nlen;++i)
            tmp[i]=list[i];*/
        std::copy(list,list+len,tmp);
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
    if( len + l < overhead )
    {
        unsigned int i = 0;
        while( i < l && len < overhead )
        {
            list[ len++ ] = c[ i++ ];
        }
        return;
    }
    T * tmp = new T[ len + l ];
    /*unsigned int nlen = (len>l?len:l);
    for(unsigned int i=0;i<nlen;++i)
    {
        if(i<len)
            tmp[i]=list[i];
        if(i<l)
            tmp[i+len]=c[i];
    }*/
    std::copy( list, list+len, tmp);
    std::copy( c, c+l, tmp+len );
    len += l;
    if( list != NULL )
        delete [] list;
    list = tmp;
}

template < typename T, typename C >
void
ClassList<T,C>::add(const ClassList<T,C>& l)
{
    add(l.getList(),l.length());
}

template < typename T, typename C >
void
ClassList<T,C>::add(ClassList<T,C>* l)
{
    add(l->getList(),l->length());
}

template < typename T, typename C >
void
ClassList<T,C>::pillage(ClassList<T,C>* l)
{
    if(l==NULL)
        return;
    add(l);
    delete l;
}

template < typename T, typename C >
void
ClassList<T,C>::replace(unsigned int l, const T& c)
{
    if(l>=length())
    {
        throw int(-1);
        return;
    }
    list[l] = c;
}

template < typename T, typename C >
void
ClassList<T,C>::remove(unsigned int l)
{
    if(l>=length())
    {
        throw int(-1);
        return;
    }
    T *tmp = new T[--len];
    unsigned int nlen = length();
    for(unsigned int i=0;i<nlen;i++)
    {
        if(i<l)
            tmp[i]=list[i];
        else
            tmp[i]=list[i+1];
    }
    /*std::copy(list,list+l,tmp);
    std::copy(list+l+1,list+len,tmp+l);*/
    if(list!=NULL)
        delete[]list;
    list=tmp;
}

template < typename T, typename C >
void
ClassList<T,C>::insert(const T& c, unsigned int l)
{
    if(l>=length())
    {
        throw int(-1);
        return;
    }
    T *tmp = new T[++len];
    unsigned int nlen = length();
    for(unsigned int i=0;i<nlen-1;i++)
    {
        if(i<l)
            tmp[i]=list[i];
        else
            tmp[i+1]=list[i];
    }
    /*std::copy(list,list+l,tmp);
    std::copy(list+l-1,list+len-1,tmp+l);*/
    tmp[l]=c;
    if(list!=NULL)
        delete[]list;
    list=tmp;
}

template < typename T, typename C >
T
ClassList<T,C>::get(unsigned int i) const
{
    //if(i < length())
    if(i>=length())
    {
        throw int(-1);
    }
    return list[i];
}

template < typename T, typename C >
T *
ClassList<T,C>::getaddress(unsigned int i) const
{
    if(i>=length())
    {
        throw int(-1);
    }
    return &list[i];
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
    return get(len-1);
}

template < typename T, typename C >
T
ClassList<T,C>::operator[] (unsigned int i) const
{
    return get(i);
}

template < typename T, typename C >
ClassList<T,C>&
ClassList<T,C>::operator = (const ClassList<T,C>& c)
{
    if(list!=NULL)
        delete[]list;
    list=c.getList();
    len=c.length();
    return *this;
}

template < typename T, typename C >
ClassList<T,C>
ClassList<T,C>::operator + (const T& l) const
{
    ClassList<T,C> v;
    v.add(getList(),length());
    v.add(l);
    return v;
}

template < typename T, typename C >
ClassList<T,C>&
ClassList<T,C>::operator+= (const T& l)
{
    add(l);
    return*this;
}

template < typename T, typename C >
ClassList<T,C>
ClassList<T,C>::operator + (const ClassList<T,C>& l) const
{
    ClassList<T,C> v;
    v.add(getList(),length());
    v.add(l.getList(),l.length());
    return v;
}

template < typename T, typename C >
ClassList<T,C>
ClassList<T,C>::operator + (ClassList<T,C> *l) const
{
    ClassList<T,C> v;
    v.add(getList(),length());
    v.add(l->getList(),l->length());
    return v;
}

template < typename T, typename C >
ClassList<T,C>&
ClassList<T,C>::operator+= (const ClassList<T,C>& l)
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
ClassList<T,C>::search(const T& ind) const
{
    if(sortFunction)
        return (T*)bsearch((void*)&ind, (void*)list, len, sizeof(T), (int(*)(const void*,const void*))sortFunction);
    return NULL;
}

template < typename T, typename C >
T*
ClassList<T,C>::search(const T& ind, C sortFunc)
{
    sort(sortFunc);
    return search(ind);
}
