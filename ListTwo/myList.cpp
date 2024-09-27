#include "myList.h"
#include <iostream>
using std::cout;
using std::endl;

#define tab "\t"

template<typename T>
myList<T>::myList():Head(nullptr), Tail(nullptr), size(0)
{
	//коснтруктор по умаолчанию создает пустой список
	//Head = Tail = nullptr;
	//size = 0;
	cout << "Lconstructor:\t" << this << endl;
}

template<typename T>
myList<T>::myList(std::initializer_list<T> list) : myList()
{
	for (T value : list)
		push_back(value);
	cout << "List initializer constructor:\t" << this << endl;
}

template<typename T>
myList<T>::myList(const myList& other) : myList()
{
	for (Element<T>* Temp = other.Head; Temp; Temp = Temp->pNext)
		push_back(Temp->Data);
	cout << "Copy constructor:\t" << this << endl;
}
template<typename T>
myList<T>::~myList()
{
	while (Head) pop_front();
	cout << "LDestructor:\t" << this << endl;
}

template<typename T>
void myList<T>::push_front(T Data)
{
	if (Head == nullptr && Tail == nullptr)
	{
		Head = Tail = new Element<T>(Data);
	}
	else
	{
		//1. создаем новый элемент
		Element<T>* New = new Element<T>(Data);
		//2. Пписоединяем элемент к списку:
		New->pNext = Head;
		//3. присоединяем список к элементу
		Head->pPrev = New;
		//4.Смещаем голову на новый элемент
		Head = New;
	}
	size++;
}
template<typename T>
void myList<T>::push_back(T Data)
{
	if (Tail == nullptr)  Head = Tail = new Element<T>(Data);
	else
	{
		Element<T>* New = new Element<T>(Data);
		New->pPrev = Tail;
		Tail->pNext = New;
		Tail = New;
	}
	size++;
}
template<typename T>
void myList<T>::pop_front()
{
	if (Head == nullptr) return;
	Element<T>* Temp = Head;
	Head = Head->pNext;
	if (Head) Head->pPrev = nullptr;
	else Tail = nullptr;
	delete Temp;
	size--;
}
template<typename T>
void myList<T>::pop_back()
{
	if (Tail == nullptr) return;
	Element<T>* Temp = Tail;
	Tail = Tail->pPrev;
	if (Tail) Tail->pNext = nullptr;
	else Head = nullptr;
	delete Temp;
	size--;
}
template<typename T>
void myList<T>::insert(int index, T Data)
{
	if (index == 0)
	{
		push_front(Data);
		return;
	}
	if (index >= size)
	{
		push_back(Data);
		return;
	}
	Element<T>* Temp = Head;
	for (int i = 0; i < index - 1; i++)
		Temp = Temp->pNext;
	Element<T>* New = new Element<T>(Data, Temp->pNext, Temp);
	Temp->pNext->pPrev = New;
	Temp->pNext = New;
	size++;
}
template<typename T>
void myList<T>::erase(int index)
{
	if (index == 0)
	{
		pop_front();
		return;
	}
	if (index >= size - 1)
	{
		pop_back();
		return;
	}
	Element<T>* Temp = Head;
	for (int i = 0; i < index; i++)
		Temp = Temp->pNext;
	Temp->pPrev->pNext = Temp->pNext;
	Temp->pNext->pPrev = Temp->pPrev;
	delete Temp;
	size--;
}
template<typename T>
void myList<T>::print() const
{
	cout << "Head:\t" << Head << endl;
	for (Element<T>* Temp = Head; Temp; Temp = Temp->pNext)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Tail:\t" << Tail;
	cout << "Кол-во элеентов списка: " << size << endl;
}
template<typename T>
void myList<T>::reverse_print() const
{
	cout << "Tail:\t" << Tail;
	cout << "Кол-во элеентов списка: " << size << endl;
	for (Element<T>* Temp = Tail; Temp; Temp = Temp->pPrev)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Head:\t" << Head << endl;
}
template<typename T>
myList<T> myList<T>::operator+(const myList& other) const
{
	myList result = *this;
	for (Element<T>* Temp = other.Head; Temp; Temp = Temp->pNext)
		result.push_back(Temp->Data);
	return result;
}
template class myList<int>;