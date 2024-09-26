#include<iostream>
#include <initializer_list>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimetr "\n-----------------------"
class List
{
	class Element
	{
		int Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr)
			:Data(Data),pNext(pNext),pPrev(pPrev)
		{
			cout << "Econstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDetructor:\t" << this << endl;
		}
		friend class List;
	}*Head,*Tail;//Объявляем два указателя на объкты класса 'Element' непосресдтвенно после описания класса
	size_t size;//кол-во элементов списка
public:
	List()
	{
		//коснтруктор по умаолчанию создает пустой список
		Head = Tail = nullptr;
		size = 0;
		cout << "Lconstructor:\t" << this << endl;
	}
	List(std::initializer_list<int> list) : List()
	{
		for (int value : list)
			push_back(value);
		cout << "List initializer constructor:\t" << this << endl;
	}
	List(const List& other) : List()
	{
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		cout << "Copy constructor:\t" << this << endl;
	}
	~List()
	{
		while (Head) pop_front();
		cout << "LDestructor:\t" << this << endl;
	}
	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
		}
		else
		{
		//1. создаем новый элемент
		Element* New = new Element(Data);
		//2. Пписоединяем элемент к списку:
		New->pNext = Head;
		//3. присоединяем список к элементу
		Head->pPrev = New;
		//4.Смещаем голову на новый элемент
		Head = New;
		}

		size++;
	}
	void push_back(int Data)
	{
		if (Tail == nullptr)  Head = Tail = new Element(Data);
		else 
		{
			Element* New = new Element(Data);
			New->pPrev = Tail;
			Tail->pNext = New;
			Tail = New;
		}
		size++;
	}
	void pop_front()
	{
		if (Head == nullptr) return;
		Element* Temp = Head;
		Head = Head->pNext;
		if (Head) Head->pPrev = nullptr;
		else Tail = nullptr;
		delete Temp;
		size--;
	}
	void pop_back()
	{
		if (Tail == nullptr) return;
		Element* Temp = Tail;
		Tail = Tail->pPrev;
		if (Tail) Tail->pNext = nullptr;
		else Head = nullptr;
		delete Temp;
		size--;
	}
	void insert(int index, int Data)
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
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)
			Temp = Temp->pNext;
		Element* New = new Element(Data, Temp->pNext, Temp);
		Temp->pNext->pPrev = New;
		Temp->pNext = New;
		size++;
	}
	void erase(int index)
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
		Element* Temp = Head;
		for (int i = 0; i < index; i++)
			Temp = Temp->pNext;
		Temp->pPrev->pNext = Temp->pNext;
		Temp->pNext->pPrev = Temp->pPrev;
		delete Temp;
		size--;
	}

	//
	void print()const
	{
		cout << "Head:\t" << Head << endl;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Tail:\t" << Tail;
		cout << "Кол-во элеентов списка: " << size << endl;
	}
	void revers_print()const
	{
		cout << "Tail:\t" << Tail;
		cout << "Кол-во элеентов списка: " << size << endl;
		for(Element*Temp=Tail;Temp;Temp=Temp->pPrev)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Head:\t" << Head << endl;
	}
	List operator+(const List& other) const
	{
		List result = *this;
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			result.push_back(Temp->Data);
		return result;
	}
};

int main()
{
	setlocale(LC_ALL, "rus");
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();
	list.revers_print();
	cout << delimetr;
	list.push_back(42);
	list.print();
	cout << delimetr;

	list.pop_front();
	list.print();
	cout << delimetr;

	list.pop_back();
	list.print();
	cout << delimetr;

	list.insert(2, 99);
	list.print();
	cout << delimetr;

	list.erase(3);
	list.print();
	cout << delimetr;
	cout << delimetr;
	List list11 = { 3, 5, 8, 13, 21 };
	list11.print();
	cout << delimetr;
	cout << delimetr;
	cout << delimetr;
	List list1 = { 3, 5, 8, 13, 21 };
	List list2 = { 34, 55, 89 };
	List list3 = list1 + list2;
	list1.print();
	list2.print();
	list3.print();
	return 0;
}