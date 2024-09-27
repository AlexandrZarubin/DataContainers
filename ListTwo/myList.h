#pragma once
#include "Element.h"
#include <initializer_list>

template<typename T>
class myList
{
	Element<T>* Head;
	Element<T>* Tail;
	size_t size;
public:
	myList();
	myList(std::initializer_list<T> list);
	myList(const myList& other);
	~myList();

	void push_front(T Data);
	void push_back(T Data);
	void pop_front();
	void pop_back();
	void insert(int index, T Data);
	void erase(int index);
	void print() const;
	void reverse_print() const;
	myList operator+(const myList& other) const;
};

