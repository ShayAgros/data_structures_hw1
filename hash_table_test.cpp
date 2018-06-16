#include "hash.h"
#include <iostream>
#include <stdlib.h>
#include <assert.h>

using hw2::Hash;

#define RUN_TEST(b)	if( (b)() ) std::cout << #b << ": [PASS]" << std::endl; \
						else std::cout << #b <<  ": [FAIL]" << std::endl;

class MyInt {
public:	
	int x;
	MyInt() : x(0) {}
	MyInt(int x) : x(x) {}

	bool operator!=(const MyInt& i) const{
		return x != i.x;
	}

	bool operator==(const MyInt& i) const {
		return x == i.x;
	}
};

class MyDouble {
public:
	double x;
	MyDouble() : x(0) {}
	MyDouble(double x) : x(x) {}
};

int moduloHash(MyInt key, int size) {
	return key.x % size;
}

bool hashTableTest() {
	Hash<MyInt, MyDouble> hash(moduloHash);

	for (int i = 0; i < 100; i++) {
		if (hash.doesExist(MyInt(i))) {
			return false;
		}
		hash.insert(MyInt(i), new MyDouble(i));
		if (!hash.doesExist(MyInt(i))) {
			return false;
		}
	}

	for (int i = 0; i < 100; i++) {
		MyDouble* d = hash.find(MyInt(i));
		if ((int)d->x != i) {
			return false;
		}
		try {
			MyDouble* d2 = hash.find(MyInt(i+100));
			return false;
		} catch (const Hash<MyInt, MyDouble>::HashNotAMemberException& ex) {

		}

	}

	for (int i = 0; i < 100; i++) {
		try {
			hash.insert(MyInt(i), new MyDouble(i));
			return false;
		} catch (const Hash<MyInt, MyDouble>::HashAlreadyMemberException& ex) {
			
		}
		
		if (!hash.doesExist(MyInt(i))) {
			return false;
		}
		hash.remove(MyInt(i));
		if (hash.doesExist(MyInt(i))) {
			return false;
		}

		try {
			hash.remove(MyInt(i));
			return false;
		} catch (const Hash<MyInt, MyDouble>::HashNotAMemberException& ex) {

		}
	}

	return true;
}
/**
int main() {

	RUN_TEST(hashTableTest);

}
*/