#include "Element.h"
#include <iostream>
using std::cout;
using std::endl;

template<typename T>
Element<T>::Element(T Data, Element* pNext, Element* pPrev)
	: Data(Data), pNext(pNext), pPrev(pPrev)
{
	cout << "Econstructor:\t" << this << endl;
}

template<typename T>
Element<T>::~Element()
{
	cout << "EDestructor:\t" << this << endl;
}
template class Element<int>;