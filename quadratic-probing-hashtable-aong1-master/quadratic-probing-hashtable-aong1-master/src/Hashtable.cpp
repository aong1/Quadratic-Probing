#include "Hashtable.h"
#include <cmath>

int Hashtable::hash(int v) const{
   return v % capacity();
}
 
Hashtable::Hashtable()
{
	cap = 17;
	c1 = 0;
	c2 = 1;
	sz = 0;
	lft = .65;
	htable = new int[cap];
	for (int i = 0; i < cap; i++) {
		htable[i] = -101;
	}
}

Hashtable::Hashtable(int capacity)
{
	cap = capacity;
	c1 = 0;
	c2 = 1;
	sz = 0;
	lft = .65;
	htable = new int[cap];
	for (int i = 0; i < cap; i++) {
		htable[i] = -101;
	}
}

Hashtable::Hashtable(int capacity, double threshold)
{
	cap = capacity;
	c1 = 0;
	c2 = 1;
	sz = 0;
	lft = threshold;
	htable = new int[cap];
	for (int i = 0; i < cap; i++) {
		htable[i] = -101;
	}
}

Hashtable::Hashtable(const Hashtable& other)
{
	//make it like how you copy the other array
	
	if (this != &other) {
		sz = other.sz;
		cap = other.cap;
		lft = other.lft;
		c1 = 0;
		c2 = 1;
		htable = new int[cap];

		int i = 0;
		while (i < cap) {
			htable[i] = other.htable[i];
			i++;
		}
	}
}

Hashtable& Hashtable::operator=(const Hashtable& other)
{
	clear();

	if (htable != nullptr) {
		delete[] htable;
	}

	htable = nullptr;

	sz = other.sz;
	cap = other.cap;
	lft = other.lft;
	c1 = 0;
	c2 = 1;
	htable = new int[cap];
	int i = 0;

	while (i < cap) {
		htable[i] = other.htable[i];
		i++;
	}

return *this;
}

Hashtable::~Hashtable()
{

	if (htable != nullptr) {
		delete[] htable;
	}

	htable = nullptr;
}

int Hashtable::size() const
{
return sz;
}

int Hashtable::capacity() const
{
return cap;
}
double Hashtable::getLoadFactorThreshold() const
{
   return lft;
}

bool Hashtable::empty() const
{
	if (sz == 0) {
		return true;
	}
return false;
}

void Hashtable::resizeInsert(int* newtable, int value, int newcap)	//when you are forced to resize, insert the new values in
{
	int origKey = value % newcap;
	int bucket = origKey;
	int i = 0;
	int bucketsProbed = 0;

	while (bucketsProbed < newcap) {
		if (newtable[bucket] == -101) {		//-101 used to signify an empty array object
			newtable[bucket] = value;
			return;
		}
		i++;
		bucket = (origKey + c1 * i + c2 * i * i) % newcap;

		bucketsProbed++;

	}
}

void Hashtable::insert(int value)
{
	int bucket = hash(value);
	int i = 0;
	int bucketsProbed = 0;
	double check = ((sz + 1) / (double)cap);
	
	if (check >= lft) {		//make sure it doesn't go over the load capacity set earlier
		int oldcap = cap;
		cap = nextPrime(cap * 2);
		int* newtable; 
		newtable = new int[cap];	

		for (int j = 0; j < cap; j++) {
			newtable[j] = -101;
		}

		for (int j = 0; j < oldcap; j++) {
			if (htable[j] != -101) {
				resizeInsert(newtable, htable[j], cap);		//call the method made to sort the resized array
			}
		}

		resizeInsert(newtable, value, cap);			//finally place the value that was passed earlier

		delete[] htable;

		htable = newtable;		//point htable at new array
	}
	while(bucketsProbed < cap) {	//otherwise find an empty spot and place the value
		if (htable[bucket] == -101) {
			htable[bucket] = value;
			sz++;
			return;
		}
		i++;
		bucket = (hash(value) + c1 * i + c2 * i * i) % cap;

		bucketsProbed++;
	}
}

void Hashtable::remove(int value)
{
	int i = 0;
	int bucketsProbed = 0;
	int bucket = hash(value);

	while (bucketsProbed < cap) {	
		if (htable[bucket] == value) {	//find the value
			htable[bucket] = -101;		//set that spot to empty
			sz--;
			return;
		}
		i++;
		bucket = (hash(value) + c1 * i + c2 * i * i) % cap;

		bucketsProbed++;
	}
}

bool Hashtable::contains(int value) const{
	int i = 0;
	int bucketsProbed = 0;
	int bucket = hash(value);

	while (bucketsProbed < cap) {
		if (htable[bucket] == value) {
			return true;
		}
		i++;
		bucket = (hash(value) + c1 * i + c2 * i * i) % cap;

		bucketsProbed++;
	}
return false;
}

int Hashtable::indexOf(int value) const
{
	for (int i = 0; i < cap; i++) {
		if (htable[i] == value) {
			return i;
		}
   }

   return -1;
}

void Hashtable::clear()
{
	for (int i = 0; i < cap; i++) {
			htable[i] = -101;
	}
	sz = 0;
}

bool Hashtable::isPrime(int n){
	int checker = 2;

	for(checker; checker < (sqrt(n)); checker++) {		//start with 2 and check each number to see if the number is able to be divided 
		if (n % checker == 0) {
			return false;
		}
   }
   return true;
}

int Hashtable::nextPrime(int n){
  
	   n++;		//increment the number once
	   while(!isPrime(n)) {		//if it's not prime keep incrementing the number
	      n++;
	   }
	   return n;
 
}
