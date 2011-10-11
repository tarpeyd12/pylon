#ifndef _HASHLIST_TEMPLATE_H
#define _HASHLIST_TEMPLATE_H

#include "classlist_template.h"
#include "arraylist.h"

template <typename T>
class HashList {
	private:
		ClassList<arraylist<T>*> list;
		/*  if insize is one, then this is just as effient as using ClassList<T>.
		 *  if insize is greater than the maximum desired length of the list, then
		 *    it is just as effient as using arraylist<T>.
		 */
		unsigned int insize;
		unsigned int pos;

		int (*sortFunction)(T* a, T* b);
	public:
		HashList();
		HashList(unsigned int s);
		HashList(ClassList<T> *l);

		~HashList();

		unsigned int length();

		void clear();

		void safeclear();

		void add(T l);

		//void add(HashList<T> l);
		void add(HashList<T> *l);

		void steal(HashList<T> *l);
		void faststeal(HashList<T> *l);
		void pillage(HashList<T> *l);

		void add(HashList<T> &l);

		void steal(HashList<T> &l);
		void faststeal(HashList<T> &l);
		void pillage(HashList<T> &l);

		T get(unsigned int l);

		void insert(T l, unsigned int c);

		void remove(unsigned int l);

		void replace(unsigned int i, T l);

		void FORCEresizeInternalList(unsigned int s);

		T operator[] (unsigned int l);

        HashList<T>& operator = (HashList<T> l);

		HashList<T>& operator+= (T l);
		HashList<T>& operator-= (unsigned int l);

		HashList<T> operator - (unsigned int l);
		HashList<T> operator + (T l);

		HashList<T>& operator+= (HashList<T>  l);
		HashList<T>  operator+  (HashList<T>  l);

		void quickSort(int left, int right);

        void setSortFunc(int (*sortFunc)(T*,T*));
        void sort();
        void sort(int (*sortFunc)(T*,T*));
};

#include "hashlist_template.cpp"

#endif /* _HASHLIST_TEMPLATE_H */
