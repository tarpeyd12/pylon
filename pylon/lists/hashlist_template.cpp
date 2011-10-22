#include "hashlist_template.h"

template <typename T>
HashList<T>::HashList()
{
    pos = 0;
    insize = 256;
    sortFunction = NULL;
}

template <typename T>
HashList<T>::HashList(unsigned int s)
{
    pos = 0;
    insize = s;
    sortFunction = NULL;
}

template <typename T>
HashList<T>::HashList(ClassList<T> *l)
{
    pos = 0;
    insize = 256;
    unsigned int g = 0;
    while(pos%insize && g < l->length())
        add(l->get(g++));
    if(g >= l->length())
        return;
    g-=1;
    unsigned int lstln = l->length()-(g+1);
    unsigned int numtoplsts = lstln/insize + 1;
    unsigned int toplststrtln = list.length();
    for(unsigned int i = 0; i < numtoplsts; i++)
        list+=new arraylist<T>();
    for(unsigned int p = 0; p < lstln; p++)
    {
        if(toplststrtln + p/insize >= list.length())
            list+=new arraylist<T>();
        list[toplststrtln + p/insize]->add(l->get(p));
    }
    pos+=lstln;
    sortFunction = NULL;
}

template <typename T>
HashList<T>::~HashList()
{
    for(unsigned int i=0;i<list.length();i++)
    {
        delete list[i];
        list -= i;
    }
    list.clear();
    pos = 0;
    insize = 256;
    sortFunction = NULL;
}

template <typename T>
unsigned int HashList<T>::length()
{
    return pos;
}

template <typename T>
void HashList<T>::clear()
{
    while(length())
        remove(length()-1);
    /*for(unsigned int i = 0; i < list.length(); i++) {
        list[i]->empty(); delete list[i];
    }*/
    list.clear();
    pos = 0;
}

template <typename T>
void HashList<T>::safeclear()
{
    //while(length()) remove(length()-1);
    clear();
}

template <typename T>
void HashList<T>::add(T l)
{
    if(pos%insize==0)
        list+=new arraylist<T>();
    list[pos/insize]->add(l);
    pos++;
}

//void add(HashList<T> l) { for(unsigned int i = 0; i < l.length(); i++) add(l[i]); }

template <typename T>
void HashList<T>::add(HashList<T> *l)
{
    unsigned int g = 0;
    while(pos%insize && g < l->length())
        add(l->get(g++));
    if(g >= l->length())
        return;
    g-=1;
    unsigned int lstln = l->length()-(g+1);
    unsigned int numtoplsts = lstln/insize + 1;
    unsigned int toplststrtln = list.length();
    for(unsigned int i = 0; i < numtoplsts; i++)
        list+=new arraylist<T>();
    for(unsigned int p = 0; p < lstln; p++)
    {
        if(toplststrtln + p/insize >= list.length())
            list+=new arraylist<T>();
        list[toplststrtln + p/insize]->add(l->get(p));
    }
    pos+=lstln;
}

template <typename T>
void HashList<T>::steal(HashList<T> *l)
{
    add(l);
    while(l->length())
        l->remove(0);
}

template <typename T>
void HashList<T>::faststeal(HashList<T> *l)
{
    add(l);
    while(l->length())
        l->remove(l->length()-1);
}

template <typename T>
void HashList<T>::pillage(HashList<T> *l)
{
    add(l);
    delete l;
}

template <typename T>
void HashList<T>::add(HashList<T> &l)
{
    unsigned int g = 0;
    while(pos%insize && g < l.length())
        add(l[g++]);
    if(g >= l.length())
        return;
    g-=1;
    unsigned int lstln = l.length()-(g+1);
    unsigned int numtoplsts = lstln/insize + 1;
    unsigned int toplststrtln = list.length();
    for(unsigned int i = 0; i < numtoplsts; i++)
        list+=new arraylist<T>();
    for(unsigned int p = 0; p < lstln; p++)
    {
        if(toplststrtln + p/insize >= list.length())
            list+=new arraylist<T>();
        list[toplststrtln + p/insize]->add(l[p]);
    }
    pos+=lstln;
}

template <typename T>
void HashList<T>::steal(HashList<T> &l)
{
    add(l);
    while(l->length())
        l->remove(0);
}

template <typename T>
void HashList<T>::faststeal(HashList<T> &l)
{
    add(l);
    while(l->length())
        l->remove(l->length()-1);
}

template <typename T>
void HashList<T>::pillage(HashList<T> &l)
{
    add(l);
    //delete l;
}

template <typename T>
T HashList<T>::get(unsigned int l)
{
    return list.get( l/insize )->operator[]( l%insize );
}

template <typename T>
void HashList<T>::insert(T l, unsigned int c)
{
    if(pos == 0 || c >= pos)
    {
        add(l);
        return;
    }
    unsigned int out = c/insize, in = c%insize;
    if(insize == 1)
    {
        arraylist<T>* p = new arraylist<T>();
        p->add(l);
        list.insert(p,c);
        pos++;
        return;
    }
    list[out]->insert(l,in);
    if((unsigned int)list[out]->length() >= insize)
    {
        if((unsigned int)list[list.length()-1]->length()+1 >= insize)
            list += new arraylist<T>();
        for(unsigned int i = out; i < list.length()-1; i++)
        {
            if((unsigned int)list[list.length()-1]->length()+1 >= insize)
                list += new arraylist<T>();
            while((unsigned int)list[i]->length() > insize)
                if(list[i]->length())
                {
                    T itm = list[i]->operator[]( list[i]->length()-1 );
                    list[i]->remove( list[i]->length()-1 );
                    if(list[i+1]->length() == 0)
                        list[i+1]->add( itm );
                    else
                        list[i+1]->insert( itm, 0 );
                }
                else
                    break;
        }
    }
    pos++;
}

template <typename T>
void HashList<T>::remove(unsigned int l)
{
    unsigned int out=l/insize, in=l%insize;
    list[out]->remove(in);
    if(list[out]->length() == 0)
    {
        delete list[out];
        list-=out;
    }
    if(insize>1)
        for(unsigned int i = out; i < list.length(); i++)
            if(i+1<list.length() && list[i+1]->length())
            {
                list[i]->add(list[i+1]->operator[](0));
                list[i+1]->remove(0);
            }
    if(list.length() && list[list.length()-1]->length()==0)
    {
        delete list[list.length()-1];
        list-=list.length()-1;
    }
    pos--;
}

template <typename T>
void HashList<T>::replace(unsigned int i, T l)
{
    list.get( i/insize )->operator[](i%insize) = l;
    /*list.get( i/insize )->remove( i%insize );
    list.get( i/insize )->insert( l, i%insize );*/
}

template <typename T>
void HashList<T>::FORCEresizeInternalList(unsigned int s)
{
    HashList<T> tmp;
    tmp.faststeal(this);
    insize = s;
    faststeal(&tmp);
}

template <typename T>
T HashList<T>::operator[] (unsigned int l)
{
    return get(l);
}

template <typename T>
HashList<T>& HashList<T>::operator = (HashList<T> l)
{
    clear();
    insize=l.insize;
    add(l);
    return *this;
}

template <typename T>
HashList<T>& HashList<T>::operator+= (T l)
{
    add(l);
    return *this;
}

template <typename T>
HashList<T>& HashList<T>::operator-= (unsigned int l)
{
    remove(l);
    return *this;
}

template <typename T>
HashList<T> HashList<T>::operator - (unsigned int l)
{
    HashList<T> v;
    v.add(this);
    v.remove(l);
    return v;
}

template <typename T>
HashList<T> HashList<T>::operator + (T l)
{
    HashList<T> v;
    v.add(this);
    v.add(l);
    return v;
}

template <typename T>
HashList<T>& HashList<T>::operator+= (HashList<T>  l)
{
    this->add(l);
    return *this;
}

template <typename T>
HashList<T>  HashList<T>::operator+  (HashList<T>  l)
{
    HashList<T> v;
    v.add(this);
    v.add(l);
    return v;
}

template <typename T>
void HashList<T>::quickSort(int left, int right)
{
    int i = left, j = right;
    T tmp;
    T pivot = this->get((left + right) / 2);

    /* partition */
    while (i <= j) {
        //cout << "I: " << i << ", J: " << j << endl;
        T pi = this->get(i);
        T pj = this->get(j);
        while (sortFunction(&pi,&pivot) < 0 && i < right)//(*this[i] < pivot)
        {
            pi = this->get(++i);
        }
        while (sortFunction(&pj,&pivot) > 0 && j > left)//(*this[j] > pivot)
        {
            pj = this->get(--j);
        }
        if (i <= j) {
            tmp = this->get(i);
            this->replace(i,this->get(j));
            this->replace(j,tmp);
            i++;
            j--;
        }
    };

  /* recursion */
  if (left < j)
        this->quickSort(left, j);
  if (i < right)
        this->quickSort(i, right);
}

template <typename T>
void HashList<T>::setSortFunc(int (*sortFunc)(T*,T*))
{
    sortFunction = sortFunc;
}

template <typename T>
void HashList<T>::sort()
{
    if(length() > 1)
        quickSort(0,length()-1);
}

template <typename T>
void HashList<T>::sort(int (*sortFunc)(T*,T*))
{
    setSortFunc(sortFunc);
    sort();
}
