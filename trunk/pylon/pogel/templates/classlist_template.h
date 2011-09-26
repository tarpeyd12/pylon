#ifndef _CLASSLIST_TEMPLATE_H
#define _CLASSLIST_TEMPLATE_H

//#include <iostream>
//#include <vector>
using namespace std;

template<typename T>
class CLASSLIST {
	private:
		T *list;
		unsigned int len;
		bool sc;
		int (*sortFunction)(T* a, T* b);
	protected:
        /// returns the pointer to the actual data array
		T* getList() { return list; }
	public:
        /// blank constructor
		CLASSLIST() { list=NULL; len=0; sc=false; sortFunction=NULL;}
		/// construct from an array
		CLASSLIST(T *c, unsigned int l) { list=c; len=l; sortFunction=NULL;}

		/// deconstructor
		~CLASSLIST() { if(list!=NULL)delete[]list; list=NULL; len=0; sortFunction=NULL;}

        /// deletes all the data from this list
		void clear() { if(list!=NULL)delete[]list; list=NULL; len=0; }
		/// deletes the list pointer to all the data in the list
		void safeclear() { if(list!=NULL)delete list; list=NULL; len=0; }
		void nullify() { list=NULL; len=0; }

        /// returns the number of items in the list
		unsigned int length() { return len; }

        /// adds an item
		void add(T l) {
			T *tmp = new T[length()+1];
			for(unsigned int i=0;i<length();i++) tmp[i]=list[i];
			tmp[len++]=l; if(list!=NULL)delete[]list; list=tmp;
		}

        /// adds all the items form the pointer c to the index l past c
		void add(T *c, unsigned int l) {
			if(c==NULL||l==0) return;
			T *tmp = new T[length()+l];
			for(unsigned int i=0;i<(length()>l?length():l);i++) { if(i<length())tmp[i]=list[i]; if(i<l)tmp[i+length()]=c[i]; }
			len+=l; if(list!=NULL)delete[]list; list=tmp;
		}

        /// removes an item from the list
		void remove(unsigned int l) {
			if(l>=length()) return;
			T *tmp = new T[--len];
			for(unsigned int i=0;i<length();i++) if(i<l)tmp[i]=list[i]; else tmp[i]=list[i+1];
			if(list!=NULL)delete[]list; list=tmp;
		}

        /// inserts an item into the list in the desired position
		void insert(T c, unsigned int l) {
			if(l>=length()) return;
			T *tmp = new T[++len];
			for(unsigned int i=0;i<length()-1;i++) if(i<l)tmp[i]=list[i]; else tmp[i+1]=list[i];
			tmp[l]=c; if(list!=NULL)delete[]list; list=tmp;
		}

        /// get an item in the array
		T get(unsigned int i) { return list[i]; }

        /// get the first item in the array
		T first() { return get(0); }
		/// get the last item in the array
		T last() { return get(length()-1); }

        /// same as get
		T operator[] (unsigned int i) { return get(i); }

        /// sets this list to the other list as quickly as possible, deleting all the list data that is currently stored in the destination list
		CLASSLIST<T>& operator = (CLASSLIST<T> c)	{ if(list!=NULL)delete[]list; list=c.getList(); len=c.length(); return *this;}

        /// returns a list that is the same as this one but with item l appedned to the end
		CLASSLIST<T>  operator + (T l)				{ CLASSLIST<T> v; v.add(getList(),length()); v.add(l); return v; }
		/// appends item l to the end of this list, same as add
		CLASSLIST<T>& operator+= (T l)				{ add(l); return*this; }

        /// retruns a list that is the same as this but with all the items in list l appened to the end
		CLASSLIST<T>  operator + (CLASSLIST<T> l)	{ CLASSLIST<T> v; v.add(getList(),length()); v.add(l.getList(),l.length()); return v; }
		/// appends all items in the list l to this one
		CLASSLIST<T>& operator+= (CLASSLIST<T> l)	{ add(l.getList(),l.length()); return*this; }

        /// returnes a list that does not have the item in index l
		CLASSLIST<T>  operator - (unsigned int l)	{ CLASSLIST<T> v; v.add(getList(),length()); v.remove(l); return v; }
		/// removes the item in index l from this list
		CLASSLIST<T>& operator-= (unsigned int l)	{ remove(l); return*this; }

		/// sets the sorting function
		void setSortFunc(int (*sortFunc)(T*,T*)) { sortFunction = sortFunc; }
		/// sorts the list
		void sort() { if(sortFunction!=NULL)qsort((void*)list, len, sizeof(T), (int(*)(const void*,const void*))sortFunction); }
		/// sets the sorting function and then sorts the list
		void sort(int (*sortFunc)(T*,T*)) { setSortFunc(sortFunc); sort(); }
		/// searches the list for item ind
		T* search(T ind) {
			if(sortFunction!=NULL)
				return (T*)bsearch((void*)&ind, (void*)list, len, sizeof(T), (int(*)(const void*,const void*))sortFunction);
			else return NULL;
		}
		/// sets the sorting function then sorts(for the sorting function might have changed thus cannot search) then searches for item ind
		T* search(T ind, int (*sortFunc)(T*,T*)) { setSortFunc(sortFunc); sort(); return search(ind); }
};

#endif /* _CLASSLIST_TEMPLATE_H */

