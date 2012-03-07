#ifndef _CLASSLIST_TEMPLATE_H
#define _CLASSLIST_TEMPLATE_H

#include <iostream>
#include <vector>
using namespace std;

template < typename DataType, typename ComparisonType >
class DataWraper
{
    public:
        DataType data;
        ComparisonType value;
        DataWraper();
        DataWraper(DataType d, ComparisonType v);
};

template < typename T, typename C = int (*)(T* a, T* b) >
class ClassList
{
	private:
		T *list;
		unsigned int len;
		unsigned int overhead;
		bool sc;

		//typedef int (C::*FredMemFn)(T* a, T* b);

		//int (*sortFunction)(T* a, T* b);

		C sortFunction;
	protected:
        /// returns the pointer to the actual data array
		T* getList();
	public:
        /// blank constructor
		ClassList();
		/// construct from an array
		ClassList(T *c, unsigned int l);
		/// construct with overhead
		ClassList(unsigned int i);

		/// deconstructor
		~ClassList();

        /// deletes all the data from this list
		void clear();
		/// deletes the list pointer to all the data in the list
		void safeclear();
		void nullify();

        /// returns the number of items in the list
		unsigned int length();

        /// adds an item
		void add(T l);

        /// adds all the items form the pointer c to the index l past c
		void add(T *c, unsigned int l);

        ///
		void replace(unsigned int l, T c);

        /// removes an item from the list
		void remove(unsigned int l);

        /// inserts an item into the list in the desired position
		void insert(T c, unsigned int l);

        /// get an item in the array
		T get(unsigned int i);

        /// get the first item in the array
		T first();
		/// get the last item in the array
		T last();

        /// same as get
		T operator[] (unsigned int i);

        /// sets this list to the other list as quickly as possible, deleting all the list data that is currently stored in the destination list
		ClassList<T,C>& operator = (ClassList<T,C> c);

        /// returns a list that is the same as this one but with item l appedned to the end
		ClassList<T,C>  operator + (T l);
		/// appends item l to the end of this list, same as add
		ClassList<T,C>& operator+= (T l);

        /// retruns a list that is the same as this but with all the items in list l appened to the end
		ClassList<T,C>  operator + (ClassList<T,C> l);
		ClassList<T,C>  operator + (ClassList<T,C> *l);
		/// appends all items in the list l to this one
		ClassList<T,C>& operator+= (ClassList<T,C> l);
		ClassList<T,C>& operator+= (ClassList<T,C> *l);

        /// returnes a list that does not have the item in index l
		ClassList<T,C>  operator - (unsigned int l);
		/// removes the item in index l from this list
		ClassList<T,C>& operator-= (unsigned int l);

		/// sets the sorting function
		void setSortFunc(C sortFunc);
		/// sorts the list
		void sort();
		/// sets the sorting function and then sorts the list
		void sort(C sortFunc);
		/// searches the list for item ind
		T* search(T ind);
		/// sets the sorting function then sorts(for the sorting function might have changed thus cannot search) then searches for item ind
		T* search(T ind, C sortFunc);
};


#include "classlist_template.cpp"

#endif /* _CLASSLIST_TEMPLATE_H */

