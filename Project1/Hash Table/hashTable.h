#pragma once
#include <iostream>
#include <algorithm>
#include "item.h"
using namespace std;

// hash table in the open addressing method

template <class T, class K>
struct Table
{
	Item<T, K>* itemTable;
	int theSize;
	Table(int size = 0);
	~Table();
	virtual int h1(K key) = 0;
	virtual int h2() = 0;
	int hash(K key, int i);
	void addItem(Item<T, K>);
	void deleteItem(K);
	void print();
	int search(K key);
	friend class MainHashTable;
	bool isPrime(int);
	int nextPrime(int);
};

// A optimized school method based C++ program to check
// if a number is prime
// in this func constructor use to check if size of table is prime
template<class T, class K>
inline bool Table<T, K>::isPrime(int n)
{
	// Corner cases
	if (n <= 1)
		return false;
	if (n <= 3)
		return true;

	// This is checked so that we can skip
   // middle five numbers in below loop
	if (n % 2 == 0 || n % 3 == 0)
		return false;

	for (int i = 5; i * i <= n; i = i + 6)
		if (n % i == 0 || n % (i + 2) == 0)
			return false;

	return true;
}

// Function to return the smallest
// prime number greater than N
template<class T, class K>
inline int Table<T, K>::nextPrime(int N)
{
	// Base case
	if (N <= 1)
		return 2;

	int prime = N;
	bool found = false;

	// Loop continuously until isPrime returns
	// true for a number greater than n
	while (!found) {
		prime++;

		if (isPrime(prime))
			found = true;
	}
	return prime;
}

// constructor and destructor
template<class T, class K>
inline Table<T, K>::Table(int size)
{
	if (isPrime(size))
		itemTable = new Item<T, K>[size];
	else
	{
		size = nextPrime(size);
		itemTable = new Item<T, K>[size];
	}
	theSize = size;
}

template<class T, class K>
inline Table<T, K>::~Table()
{
	if (itemTable)
	{
		delete itemTable;
	}
}

//Returns the position in the table for key k in attempt i.
template<class T, class K>
inline int Table<T, K>::hash(K key, int i)
{
	return (h1(key) + i * h2()) % theSize;
}

template<class T, class K>
inline int Table<T, K>::search(K key)
{
	int i = 0
	int index = -1;
	for (size_t i = 0; i < theSize; i++)
	{
		if (itemTable[i].key == key && itemTable[i].flag != DELETED)
		{
			index = i;
			break;
		}
	}
	return index;
}

// method to add an item to hash table
template<class T, class K>
inline void Table<T, K>::addItem(Item<T, K> item)
{
	// we ned to search for a free space in the hash table
	//	using our hash functions.
	// if index i full, we use h2 (skip)
		//to find next index thats empty.
	for (int i = 0; i < theSize ;i++)
	{
		int place = hash(item.key, i);
		if (itemTable[place].flag != FULL)
		{
			item.flag = FULL;
			itemTable[place] = item;
			break;
		}
	}
}

// delete an item from the hash table
template<class T, class K>
inline void Table<T, K>::deleteItem(K key)
{
	int index = -1;
	index = search(key);
	if (index == -1)
	{
		cout << "item not found\n";
		return;
	}
	itemTable[index].flag = DELETED;
	delete itemTable[index];
}

template<class T, class K>
inline void Table<T, K>::print()
{
	for (size_t i = 0; i < theSize; i++)
	{
		cout << itemTable[i].key ;
		cout << itemTable[i].data << endl;
	}
}