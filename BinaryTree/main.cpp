#include<iostream>
#include<iomanip>
using namespace std;

#define tab "\t"

class Tree
{
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr)
			:Data(Data), pLeft(pLeft), pRight(pRight)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class Tree;
	}*Root;
public:
	Element* getRoot()const
	{
		return Root;
	}
	Tree()
	{
		Root = nullptr;
		cout << "TConstructor:\t" << this << endl;
	}
	~Tree()
	{
		clear(this->Root);
		cout << "TDestructor:\t" << this << endl;
	}

	void insert(int Data)
	{
		insert(Data, this->Root);
	}

	//					Methods:
	void print()const
	{
		print(this->Root);
	}
	void clear()
	{
		clear(this->Root);
		this->Root = nullptr;
	}
	int minValue()const
	{
		if (Root == nullptr)return 999999999999;
		return minValue(this->Root);
	}
	int maxValue()const
	{
		if (Root == nullptr)return -999999999999;
		return maxValue(this->Root);
	}
	int count()const
	{
		return count(this->Root);
	}
	int sum()const
	{
		return sum(this->Root);
	}
	double avg()const
	{
		int Temp = count();
		if (!Temp)return 0;
		return static_cast<double>(sum()) / Temp;
	}
	int depth()const
	{
		return depth(this->Root);
	}
	void PrintTree()
	{
		PrintTree(this->Root, 0);
	}
private:
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
	///
	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}
	void clear(Element* Root)
	{
		if (Root == nullptr)return;
		clear(Root->pLeft);
		clear(Root->pRight);
		delete Root;
	}
	int minValue(Element*Root)const
	{
		if (Root->pLeft == nullptr) return Root-> Data;
		return minValue(Root->pLeft);
	}
	int maxValue(Element*Root)const
	{
		if (Root->pRight == nullptr)return Root->Data;
		return maxValue(Root->pRight);
	}
	int count(Element*Root)const
	{
		if (Root == nullptr)return 0;
		return 1 + count(Root->pLeft) + count(Root->pRight);
	}
	int sum(Element*Root)const
	{
		if (Root == nullptr)return 0;
		return Root->Data + sum(Root->pLeft) + sum(Root->pRight);
	}
	int depth(Element* Root)const
	{
		if (Root == nullptr)return 0;
		int leftDepth = depth(Root->pLeft);
		int rightDepth = depth(Root->pRight);
		if (leftDepth > rightDepth)
			return 1 + leftDepth;
		else
			return 1 + rightDepth;
	}
	void PrintTree(Element* Root, int level)const
	{
		if (Root == nullptr)return;
		PrintTree(Root->pRight, level + 1);
		for (int i = 0; i < level; i++)
		{
			cout << "   ";  // Отступ для каждого уровня
		}
		cout << Root->Data << endl;
		PrintTree(Root->pLeft, level + 1);
	}
	
};

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Введите кол-во элементов: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		//tree.insert(rand() % 100, tree.getRoot());
		tree.insert(rand() % 100);
	}
	cout << "Количество узлов в дереве: " << tree.count() << endl;
	cout << "Сумма всех элементов в дереве: " << tree.sum() << endl;
	cout << "Глубина дерева: " << tree.depth() << endl;
	cout << "Минимальное значение в дереве: " << tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << tree.maxValue() << endl;
	//tree.print(tree.getRoot());
	tree.print();
	cout << endl;
	cout << endl;
	cout << "Дерево в виде структуры:" << endl;
	tree.PrintTree();

}