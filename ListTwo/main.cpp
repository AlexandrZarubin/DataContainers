#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimetr "\n-----------------------"
template<typename T>
class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr)
			:Data(Data),pNext(pNext),pPrev(pPrev)
		{
//#if DEBUG
			cout << "Econstructor:\t" << this << endl;
//#endif // DEBUG
		}
		~Element()
		{
//#if DEBUG
			cout << "EDetructor:\t" << this << endl;
//#endif // DEBUG
		}
		friend class List;
	}*Head,*Tail;//Объявляем два указателя на объкты класса 'Element' непосресдтвенно после описания класса
	size_t size;//кол-во элементов списка
	
	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp) :Temp(Temp) {}
		~ConstBaseIterator() {}
		bool operator==(const ConstBaseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const ConstBaseIterator& other)const
		{
			return this->Temp != other.Temp;
		}
		T operator*()const
		{
			return Temp->Data;
		}
	};
public:
	class ConstIterator:public ConstBaseIterator
	{
	public:
		ConstIterator(Element* temp) :ConstBaseIterator(temp)
		{
#if DEBUG
			cout << "ITDestruction:\t" << this << endl;
#endif // DEBUG

		}
		~ConstIterator()
		{
#if DEBUG
			cout << "ITDestruction:\t" << this << endl;
#endif // DEBUG
		}
		ConstIterator& operator++()//Prefix increment
		{
			this->Temp = this->Temp->pNext;
			return *this;
		}
		ConstIterator operator++(int)
		{
			ConstIterator old = *this;
			this->Temp = this->Temp->pNext;
			return old;
		}
		ConstIterator& operator--()//Prefix increment
		{
			this->Temp = this->Temp->pPrev;
			return *this;
		}
		ConstIterator& operator--(int)//Prefix increment
		{
			ConstIterator old = *this;//Temp;
			this->Temp = this->Temp->pPrev;
			return old;
		}
	};
	class ConstReversIterator:public ConstBaseIterator
	{
	public:
		ConstReversIterator(Element* Temp) :ConstBaseIterator(Temp)
		{
#if DEBUG
			cout << "RITconstructor:\t" << this << endl;
#endif // DEBUG
		}
		~ConstReversIterator()
		{
#if DEBUG
			cout << "RITDestructor:\t" << this << endl;
#endif // DEBUG
		}
		ConstReversIterator& operator++()
		{
			this->Temp = this->Temp->pPrev;
			return *this;
		}
		ConstReversIterator& operator++(int)
		{
			ConstReversIterator old = *this;

			this->Temp = this->Temp->pPrev;
			return old;
		}
		ConstReversIterator& operator--()
		{
			this->Temp = this->Temp->pNext;
			return *this;
		}
		ConstReversIterator& operator--(int)
		{
			ConstReversIterator old = *this;
			this->Temp = this->Temp->pNext;
			return old;
		}
	};
	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element*Temp):ConstIterator(Temp){}
		~Iterator(){}
		T& operator*()
		{
			return this->Temp->Data;
		}
	};
	class ReversIterator :public ConstReversIterator
	{
	public:
		ReversIterator(Element* Temp) :ConstReversIterator(Temp) {}
		~ReversIterator() {}
		T& operator*()
		{
			return this->Temp->Data;
		}
	};
	ConstIterator begin()const
	{
		return Head;
	}
	ConstIterator end()const
	{
		return nullptr;
	}
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	ConstReversIterator rbegin()const
	{
		return Tail;
	}
	ConstReversIterator rend()const
	{
		return nullptr;
	}
	ReversIterator rbegin()
	{
		return Tail;
	}
	ReversIterator rend()
	{
		return nullptr;
	}
	List()
	{
		//коснтруктор по умаолчанию создает пустой список
		Head = Tail = nullptr;
		size = 0;
		cout << "Lconstructor:\t" << this << endl;
	}
	List(const std::initializer_list<T>& il) :List()
	{
		//begin() - возвращает итератор на начало контейнераю
		//end() - возвращает итератор на конец контейнер
		//Итератор - это указатель, при помощи которого можно получить доступ к элементам структуры данных.
		cout << "-----\t"<<typeid(il.begin()).name() << endl;
		for (T const* it = il.begin(); it != il.end(); it++)
			push_back(*it);
	}
	List(const List& other) :List()//без делегирования может падать
	{
		*this = other;
		cout << "LCopyConstructor: " << this << endl;
	}
	List(List&& other) :List()
	{
		*this = std::move(other);//явный вызов MoveAssignment
	}
	~List()
	{
		//while(Head)pop_front();
		while(Tail)pop_back();
#if DEBUG
		cout << "LDestructor:\t" << this << endl;
#endif // DEBUG
	}
	void push_front(T Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
		}
		else
		{
		////1. создаем новый элемент
		//Element* New = new Element(Data);
		////2. Пписоединяем элемент к списку:
		//New->pNext = Head;
		////3. присоединяем список к элементу
		//Head->pPrev = New;
		////4.Смещаем голову на новый элемент
		//Head = New;
			Head = Head->pPrev = new Element(Data, Head);
		}
		size++;
	}
	List& operator=(const List& other)
	{
		cout << "LCopyAssignment: " << this << endl;
		if(this == &other)return * this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		return *this;
	}
	List& operator=(List&& other)
	{
		if (this == &other)return*this;
		//Shalow coppy-поверхностное копирование
		this->Head = other.Head;
		this->Tail = other.Tail;
		this->size = other.size;
		//обязательно нужно обнулить other
		other.Head = other.Tail = nullptr;
		other.size = 0;
		cout << "LMoveAssignment:\t" << this << endl;
	}
	void push_back(T Data)
	{
		if (Head == nullptr && Tail == nullptr)return push_front(Data);
		Tail = Tail->pNext = new Element(Data, nullptr, Tail);
		size++;
	}
	void insert(T Data, int index)
	{
		if (index == 0)return push_front(Data);
		if (index == size-1)return push_back(Data);
		if (index >= size)throw std::exception("insert: out of range exception");
		Element* Temp;
		if (index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size-index-1; i++)
			{
				Temp = Temp->pPrev;
			}
			Temp->pNext->pPrev = Temp->pPrev->pNext = new Element(Data, Temp->pNext, Temp->pPrev);
			size++;
		}
	}

	//			Removing elements
	void pop_front()
	{
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
			size=0;
			return;
		}

		Head = Head->pNext;
		delete Head->pPrev;
		Head->pPrev = nullptr;
		size--;
	}
	void pop_back()
	{
		if (Head == Tail)return pop_front();
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		size--;
	}
	//		MEthods:
	void print()const
	{
		cout << "Head:\t" << Head << endl;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Tail:\t" << Tail;
		cout << "\nКол-во элеентов списка: " << size << endl;
	}
	void revers_print()const
	{
		cout << "Tail:\t" << Tail;
		cout << "Кол-во элеентов списка: " << size << endl;
		for(Element*Temp=Tail;Temp;Temp=Temp->pPrev)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Head:\t" << Head << endl;
	}
};
template<typename T>
List<T> operator+(const List<T>& left, const List<T>&right)
{
	List<T> buffer;
	for (typename List<T>::ConstIterator it = left.begin(); it != left.end(); ++it)buffer.push_back(*it);
	for (typename List<T>::ConstIterator it = right.begin(); it != right.end(); ++it)
	{ 
		buffer.push_back(*it); 
	}
	return buffer;
}
//#define BASE_CHAECK
//#define ITERATORS_CHECK
int main()
{
	setlocale(LC_ALL, "rus");
#if BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	list.revers_print();
	/*for (int i = 0; i < n*2; i++)
	{
		list.pop_back();
	}
	list.print();
	list.revers_print();*/
	int index;
	int value;
	cout << "Введите индекс добовляемого элемента: "; cin >> index;
	cout << "Введите значение добовляемого элемента: "; cin >> value;
	try
	{
		list.insert(value, index);
		list.print();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << endl;
	}

#endif // BASE_CHAECK

#if ITERATORS_CHECK
	List list = { 3,5,8,13,21 };
	//list.print();
	/*for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;*/
	for (List::Iterator it = list.begin(); it != list.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << "\n----------------------------\n";
	for (List::ReversIterator it = list.rbegin(); it != list.rend(); ++it)
	{
		cout << *it << tab;
	}
#endif // ITERATORS_CHECK

	List<int> list1 = { 3,5,8,13,21 };
	List<int> list2 = { 34,55,89 };
	List<int> list3 = list1 + list2;
	for (int i : list1)cout << i << tab; cout << endl;
	for (int i : list2)cout << i << tab; cout << endl;
	for (int i : list3)cout << i << tab; cout << endl;
	for (List<int>::Iterator it = list1.begin(); it != list1.end(); ++it)
	{
		*it *= 10;
	}
	for (int i : list1)cout << i << tab; cout << endl;
	return 0;
}