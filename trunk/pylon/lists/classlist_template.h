#ifndef _CLASSLIST_TEMPLATE_H
#define _CLASSLIST_TEMPLATE_H

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template < typename DataType, typename ComparisonType >
class DataWraper
{
    public:
        DataType data;
        ComparisonType value;
        DataWraper();
        DataWraper(DataType d, ComparisonType v);
        DataWraper<DataType,ComparisonType>& operator=(const DataWraper<DataType,ComparisonType>&);
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
	//protected:
	public:
        /// returns the pointer to the actual data array
		inline T* getList() const;
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
		inline void clear();
		/// deletes the list pointer to all the data in the list
		inline void safeclear();
		inline void nullify();

        /// returns the number of items in the list
		inline unsigned int length() const;

        /// adds an item
		inline void add(const T& l);

        /// adds all the items form the pointer c to the index l past c
		inline void add(T *c, unsigned int l);

		///
		inline void add(const ClassList<T,C>& l);

		///
		inline void add(ClassList<T,C>* l);

        /// adds l to this, but also deleats the data in l, so the only copy is in this
		inline void pillage(ClassList<T,C>* l);

        ///
		inline void replace(unsigned int l, const T& c);

        /// removes an item from the list
		inline void remove(unsigned int l);

        /// inserts an item into the list in the desired position
		inline void insert(const T& c, unsigned int l);

        /// get an item in the array
		inline T get(unsigned int i) const;

		/// get the internal address of an item in the list
		inline T * getaddress(unsigned int i) const;

        /// get the first item in the array
		inline T first();
		/// get the last item in the array
		inline T last();

        /// same as get
		inline T operator[] (unsigned int i) const;

        /// sets this list to the other list as quickly as possible, deleting all the list data that is currently stored in the destination list
		inline ClassList<T,C>& operator = (const ClassList<T,C>& c);

        /// returns a list that is the same as this one but with item l appedned to the end
		inline ClassList<T,C>  operator + (const T& l) const;
		/// appends item l to the end of this list, same as add
		inline ClassList<T,C>& operator+= (const T& l);

        /// retruns a list that is the same as this but with all the items in list l appened to the end
		inline ClassList<T,C>  operator + (const ClassList<T,C>& l) const;
		inline ClassList<T,C>  operator + (ClassList<T,C>* l) const;
		/// appends all items in the list l to this one
		inline ClassList<T,C>& operator+= (const ClassList<T,C>& l);
		inline ClassList<T,C>& operator+= (ClassList<T,C>* l);

        /// returnes a list that does not have the item in index l
		inline ClassList<T,C>  operator - (unsigned int l);
		/// removes the item in index l from this list
		inline ClassList<T,C>& operator-= (unsigned int l);

		/// sets the sorting function
		inline void setSortFunc(C sortFunc);
		/// sorts the list
		inline void sort();
		/// sets the sorting function and then sorts the list
		inline void sort(C sortFunc);
		/// searches the list for item ind
		inline T* search(const T& ind) const;
		/// sets the sorting function then sorts(for the sorting function might have changed thus cannot search) then searches for item ind
		inline T* search(const T& ind, C sortFunc);
};


#include "classlist_template.cpp"

#endif /* _CLASSLIST_TEMPLATE_H */

