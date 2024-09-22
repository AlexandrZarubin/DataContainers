#include<iostream>
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
	}*Head,*Tail;//��������� ��� ��������� �� ������ ������ 'Element' ��������������� ����� �������� ������
	size_t size;//���-�� ��������� ������
public:
	List()
	{
		//����������� �� ���������� ������� ������ ������
		Head = Tail = nullptr;
		size = 0;
		cout << "Lconstructor:\t" << this << endl;
	}
	~List()
	{
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
		//1. ������� ����� �������
		Element* New = new Element(Data);
		//2. ������������ ������� � ������:
		New->pNext = Head;
		//3. ������������ ������ � ��������
		Head->pPrev = New;
		//4.������� ������ �� ����� �������
		Head = New;
		}

		size++;
	}
	//
	void print()const
	{
		cout << "Head:\t" << Head << endl;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Tail:\t" << Tail;
		cout << "���-�� �������� ������: " << size << endl;
	}
	void revers_print()const
	{
		cout << "Tail:\t" << Tail;
		cout << "���-�� �������� ������: " << size << endl;
		for(Element*Temp=Tail;Temp;Temp=Temp->pPrev)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Head:\t" << Head << endl;
	}
};

int main()
{
	setlocale(LC_ALL, "rus");
	int n;
	cout << "������� ������ ������: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();
	list.revers_print();
	return 0;
}