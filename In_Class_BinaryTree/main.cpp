#include<ctime>
#include<chrono>
#include<iomanip>
#include<thread>
//#include<vector>
#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n------------------------------------------------\n"

class Tree
{
protected:
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
		int height;						// Высота узла (для балансировки)
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr)
			:Data(Data), pLeft(pLeft), pRight(pRight)
		{
#ifdef DEBUG
			cout << "EConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~Element()
		{
#ifdef DEBUG
			cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
		}
		bool isLeaf()const
		{
			return pLeft == pRight;
		}
		friend class Tree;
		friend class UniqueTree;
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
	Tree(const std::initializer_list<int>& il) :Tree()
	{
		for (int const* it = il.begin(); it != il.end(); ++it)
			insert(*it, Root);
	}
	~Tree()
	{
		clear();
		cout << "TDestructor:\t" << this << endl;
	}
	void clear()
	{
		clear(Root);
		Root = nullptr;
	}
	void insert(int Data)
	{
		insert(Data, Root);
	}
	void erase(int Data)
	{
		erase(Data, Root);
	}
	int minValue()const
	{
		return minValue(Root);
	}
	int maxValue()const
	{
		return maxValue(Root);
	}
	int count()const
	{
		return count(Root);
	}
	int sum()const
	{
		return sum(Root);
	}
	double avg()const
	{
		return (double)sum(Root) / count(Root);
	}
	void print()const
	{
		print(Root);
		cout << endl;
	}
	int depth() const
	{
		return depth(Root);
	}
	void balance()
	{
		Root = balance(Root);
	}
private:
	int height(Element* Root)			// Функция для получения высоты узла
	{
		return Root == nullptr ? 0 : Root->height;
	}

	int getBalance(Element* Root)		// Функция для вычисления баланс-фактора узла
	{
		return Root == nullptr ? 0 : height(Root->pLeft) - height(Root->pRight);
	}
	Element* rightRotate(Element* y)	// Правый поворот для балансировки дерева
	{
		Element* x = y->pLeft;			// Новым корнем поддерева станет левый узел
		Element* T2 = x->pRight;		// Сохраняем правое поддерево левого узла
		//Поворот
		x->pRight = y;					// Левый узел теперь становится родителем
		y->pLeft = T2;					// Правое поддерево бывшего левого узла перемещается налево

		y->height = (height(y->pLeft) > height(y->pRight) ? height(y->pLeft) : height(y->pRight)) + 1;
		x->height = (height(x->pLeft) > height(x->pRight) ? height(x->pLeft) : height(x->pRight)) + 1;

		return x;
	} 
	Element* leftRotate(Element* x) // Левый поворот для балансировки дерева
	{
		Element* y = x->pRight;    // Новым корнем поддерева станет правый узел
		Element* T2 = y->pLeft;    // Сохраняем левое поддерево правого узла
		//поворот
		y->pLeft = x;              // Правый узел теперь становится родителем
		x->pRight = T2;            // Левое поддерево бывшего правого узла перемещается направо

		x->height = (height(x->pLeft) > height(x->pRight) ? height(x->pLeft) : height(x->pRight)) + 1;
		y->height = (height(y->pLeft) > height(y->pRight) ? height(y->pLeft) : height(y->pRight)) + 1;

		return y;
	}

	Element* balance(Element* Root)
	{
		if (Root == nullptr)  return nullptr; 
		Root->height = (height(Root->pLeft) > height(Root->pRight) ? height(Root->pLeft) : height(Root->pRight)) + 1;

		int balanceFactor = getBalance(Root);
		
		if (balanceFactor > 1)		  // Левый перевес:
		{
			if (getBalance(Root->pLeft) < 0) Root->pLeft = leftRotate(Root->pLeft); // Выполняем левый поворот
			return rightRotate(Root); // Выполняем правый поворот
		}

		if (balanceFactor < -1)		 // Правый перевес
		{
			if (getBalance(Root->pRight) > 0)Root->pRight = rightRotate(Root->pRight); // Выполняем правый поворот
			return leftRotate(Root); // Выполняем левый поворот
		}
		return Root;				// Возвращаем узел, если он уже сбалансирован
	}
	void clear(Element* Root)
	{
		if (Root == nullptr)return;
		clear(Root->pLeft);
		clear(Root->pRight);
		delete Root;
	}
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
	void erase(int Data, Element*& Root)
	{
		if (Root == nullptr)return;
		erase(Data, Root->pLeft);
		erase(Data, Root->pRight);
		if (Data == Root->Data)
		{
			if (Root->isLeaf())
			{
				delete Root;
				Root = nullptr;
			}
			else
			{
				if (count(Root->pLeft) > count(Root->pRight))
				{
					Root->Data = maxValue(Root->pLeft);
					erase(maxValue(Root->pLeft), Root->pLeft);
				}
				else
				{
					Root->Data = minValue(Root->pRight);
					erase(minValue(Root->pRight), Root->pRight);
				}
			}
		}
	}
	int minValue(Element* Root)const
	{
		if (Root == nullptr)throw exception("Error in minValue: Tree is empty");
		return Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
		/*if (Root->pLeft == nullptr)return Root->Data;
		else return minValue(Root->pLeft);*/
	}
	int maxValue(Element* Root)const
	{
		if (Root == nullptr)throw std::exception("Error in maxValue: Tree is empty");
		return Root->pRight ? maxValue(Root->pRight) : Root->Data;
	}
	int count(Element* Root)const
	{
		return !Root ? 0 : count(Root->pLeft) + count(Root->pRight) + 1;
		/*if (Root == nullptr)return 0;
		else return count(Root->pLeft) + count(Root->pRight) + 1;*/
	}
	int sum(Element* Root)const
	{
		return !Root ? 0 : sum(Root->pLeft) + sum(Root->pRight) + Root->Data;
	}
	int depth(Element* Root) const
	{
		if (Root == nullptr) return 0;
		int left_depth = depth(Root->pLeft);	// Глубина левого поддерева
		int right_depth = depth(Root->pRight);	// Глубина правого поддерева
		return (left_depth > right_depth ? left_depth : right_depth) + 1;
	}
	//					Methods:
	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}
};

class UniqueTree :public Tree
{
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		if (Data > Root->Data)
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
public:
	void insert(int Data)
	{
		insert(Data, Root);
	}
};
class Timer
{
	using clock_t = std::chrono::high_resolution_clock;// это тип часов,
	using time_point_t = std::chrono::time_point<clock_t>;// это шаблонный класс, который используется для хранения точки времени
	time_point_t start_time;
	std::string name;
public:
	Timer(const std::string& name = "Duration") : name(name)
	{
		start_time = clock_t::now();
	}
	~Timer()
	{
		time_point_t end_time = clock_t::now();
		std::chrono::duration<double> duration = end_time - start_time;
		std::cout <<"\t\t"<<name << " выполнено за: " << duration.count() << " секунд.\n";
	}
};
#define BASE_CHECK
//#define PERFECT_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	try
	{

		int n;
		cout << "Введите размер дерева: "; cin >> n;
		Timer timer1("\nОбщее время");
		Tree tree;
		{
			Timer timer2("\nВремя заполнения\t");
			if(n<1000)
			this_thread::sleep_for(chrono::milliseconds(1000));
			for (int i = 0; i < n; i++)
			{
				tree.insert(rand() % 100);
				//tree.insert(rand() % 100, tree.getRoot());
			}
		}
		tree.balance();
			//tree.print();
		{
			// Измерение времени для minValue
			//clock_t start = clock();
			
			//std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
			Timer timer("minValue");
			cout << "Минимальное занчение в дереве: " << tree.minValue();
			//clock_t end = clock();
			//cout << "\nВычесленно за: " << double(end - start) / CLOCKS_PER_SEC << " секунд.\n";
			
			//std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();
			//std::chrono::duration<double> duration = end - start;
			//cout << "\nВычислено за: " << duration.count() << " секунд.\n";
		}

		{
			Timer timer("maxValue");
			cout << "Максимальное значение в дереве: " << tree.maxValue();
		}
		{
			Timer timer("\tcount");
			cout << "Количество элементов дерева:" << tree.count();
		}
		{
			Timer timer("\t\tsum");
			cout << "Сумма элементов дерева:" << tree.sum();
		}
		{
			Timer timer("avg");
			cout << "Среднее-арифметическое элементов дерева: " << tree.avg();
		}
		{
			Timer timer("Время выполнения depth");
			cout << "Глубина дерева: " << tree.depth();
		}
		int value;
		//cout << "Введите значение удаляемого элемента: "; cin >> value;
		//tree.erase(value);
		tree.print();
		cout << "Количество элементов дерева: " << tree.count();
		cout << delimiter << endl;

		UniqueTree u_tree;
		for (int i = 0; i < n; i++)
		{
			u_tree.insert(rand() % 100);
		}
		u_tree.print();
		{
			Timer timer("UniqueTree minValue");;
			cout << "Минимальное занчение в дереве: " << u_tree.minValue();
		}
		{
			Timer timer("UniqueTree maxValue");
			cout << "Максимальное значение в дереве: " << u_tree.maxValue();
		}
		{
			Timer timer("\tUniqueTree count");
			cout << "Количество элементов дерева:" << u_tree.count();
		}
		{
			Timer timer("\t\tUniqueTree sum");
			cout << "Сумма элементов дерева:" << u_tree.sum();
		}
		{
			Timer timer("UniqueTree avg");
			cout << "Среднее-арифметическое элементов дерева: " << u_tree.avg();
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << endl;
	}
#endif // BASE_CHECK

#ifdef PERFECT_CHECK
	Tree tree =
	{
						50,

			25,						75,

		16,		32,				64,		85
	};
	tree.print();

	int value;
	cout << "������� �������� ���������� ��������: "; cin >> value;
	tree.erase(value);
	tree.print();
#endif // PERFECT_CHECK

}