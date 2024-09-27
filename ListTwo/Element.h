#pragma once
//#include <iostream>

template<typename T>
class Element
{
	T Data;
	Element* pNext;
	Element* pPrev;
	template<typename T> friend class myList;
public:
	Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr);
	~Element();
	
};

