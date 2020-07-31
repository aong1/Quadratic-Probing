#ifndef ORDEREDLINKEDLIST_H
#define ORDEREDLINKEDLIST_H
#include <iostream>

class Hashtable
{
   private:
      int hash(int v) const;
public:
	Hashtable();
	Hashtable(int);
	Hashtable(int, double);
	Hashtable(const Hashtable& other);
	Hashtable& operator=(const Hashtable& other);
	~Hashtable();

        int size() const;
        int capacity() const;
        double getLoadFactorThreshold() const;
        bool empty() const;
		void insert(const int);
        void remove(int);
        bool contains(int) const;
        int indexOf(int) const;
        void clear();
		void resizeInsert(int* newtable, int value, int newcap);
        static bool isPrime(int n);
        static int nextPrime(int n);

protected:
	int cap;
	int sz;
	int c1;
	int c2;
	double lft;
	int* htable;
};

#endif
