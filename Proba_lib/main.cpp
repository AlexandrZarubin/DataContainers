#include<iostream>
#include<myList.h>
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
	cout << "1-------------------------\n";
	list.push_back(42);
	list.print();
	
	cout << "2-------------------------\n";

	list.pop_front();
	list.print();
	
	cout << "3-------------------------\n";

	list.pop_back();
	list.print();
	cout << "4-------------------------\n";
	

	list.insert(2, 99);
	list.print();
	
	cout << "5-------------------------\n";

	list.erase(3);
	list.print();
	cout << "6-------------------------\n";
	
	
	myList<int> list11 = { 3, 5, 8, 13, 21 };
	list11.print();
	cout << "7-------------------------\n";
	
	myList<int> list1 = { 3, 5, 8, 13, 21 };
	myList<int> list2 = { 34, 55, 89 };
	myList<int> list3 = list1 + list2;
	list1.print();
	list2.print();
	list3.print();
	myList<double> list55 = { 3.3, 5.5, 8.8, 13.7, 21.9 };
	list55.print();
	return 0;
}