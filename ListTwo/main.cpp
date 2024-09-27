#include<iostream>
#include"myList.h"
#define tab "\t"
#define delimetr "\n-----------------------"
using std::cout;
using std::endl;
using std::cin;
int main()
{
	setlocale(LC_ALL, "rus");
	int n;
	cout << "¬ведите размер списка: "; cin >> n;
	myList<int> list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();
	list.reverse_print();
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
	myList<int> list11 = { 3, 5, 8, 13, 21 };
	list11.print();
	cout << delimetr;
	cout << delimetr;
	cout << delimetr;
	myList<int> list1 = { 3, 5, 8, 13, 21 };
	myList<int> list2 = { 34, 55, 89 };
	myList<int> list3 = list1 + list2;
	list1.print();
	list2.print();
	list3.print();
	return 0;
}