#include<iostream>
using namespace std;
#define DEBUG
#define tab "\t"
#define delimiter "\n------------------------------------------\n"
class Tree
{
protected:
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr)
			:Data(Data), pLeft(pLeft), pRight(pRight)
		{
#ifdef DEBUG
			cout << "EConstructor:\t" << this << endl;
#endif //DEBUG
		}
		~Element()
		{
#ifdef DEBUG
			cout << "EDestrcutor:\t" << this << endl;
#endif //DEBUG
		}
		friend class Tree; 
		friend class UniqueTree;
	}*Root;
public:
	Element* getRoot()const
	{
		return Root;
	}
	Tree() :Root(nullptr)
	{
		cout << "TConstructor:\t" << this << endl;
	
	}
	Tree(const std::initializer_list<int>&il) :Tree()
	{
		for (int const* it = il.begin(); it != il.end(); ++it)
		{
			insert(*it, Root);
		}
	}
	~Tree()
	{
		Clear(Root);
		Root = nullptr;
		cout << "TDestructor:\t" << this << endl;
		cout << delimiter;
	}

	void insert(int Data)
	{
		insert(Data, Root);
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
	int Sum()const
	{
		return Sum(Root);
	}
	double Avg()const
	{
		return (double)Sum(Root) / count(Root);
	}
	void Clear()
	{
		Clear(Root);
		Root = nullptr;
	}
	int depth()const
	{
		return depth(Root);
	}
	
	void print()const
	{
		print(Root);
		cout << endl;
	}
private:
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			//проверили, если нет левого потомка у элемента
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			// если есть, то ищем куда его добавить 
			else insert(Data, Root->pLeft);
		}
		//если Data не меньше, чем Root Data
		else 
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
	int minValue(Element* Root)const
	{
		//самое маленькое значение хранится в левой стороне 
		/*if (Root->pLeft == nullptr)return Root->Data;
		return minValue(Root->pLeft);*/
		return Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
	}
	int maxValue(Element* Root)const
	{
		return Root->pRight ? maxValue(Root->pRight) : Root->Data;
		/*return Root->pRight == nullptr ? Root->Data : maxValue(Root->pRight);*/
		/*if (Root->pRight == nullptr)return Root->Data;
		return maxValue(Root->pRight);*/
	}
	int count(Element* Root)const
	{
		if (Root == nullptr)return 0;
		else {
			return 1 + count(Root->pLeft) + count(Root->pRight);
		}
	}
	int Sum(Element* Root)const
	{
		/*if (Root == nullptr) return 0;
		return Root->Data + Sum(Root->pLeft) + Sum(Root->pRight);*/
		return Root == nullptr ? 0 : Sum(Root->pLeft) + Sum(Root->pRight) + Root->Data;

	}
	void Clear(Element* Root)
	{
		if (Root == nullptr)return;
		Clear(Root->pLeft);Clear (Root->pRight);
		delete Root;
	}
	int depth(Element* Root)const
	{
		if (Root == nullptr)return 0;
		else return
			depth(Root->pLeft) + 1 > depth(Root->pRight) + 1 ?
			depth(Root->pLeft) + 1 : depth(Root->pRight) + 1;
	}
	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}
};
class UniqueTree : public Tree
{
private:
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)
				Root->pLeft = new Element(Data);
			else
				insert(Data, Root->pLeft);	
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

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Введите размер дерева: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		int number = rand() % 100;
		/*cout << number << tab;*/
		tree.insert(number);
	}
	tree.print();
	cout << endl;
	cout << "Количество элементов дерева:" << tree.count() << endl;
	cout << "Минимальное значение: " << tree.minValue() << endl;
	cout << "Максимальное значение: " << tree.maxValue() << endl;
	cout << "Сумма элементов: " << tree.Sum() << endl;
	cout << "Среднее арифметическое элементов дерева: " << tree.Avg() << endl;
	cout << "Глубина дерева: " << tree.depth() << endl;
	/*tree.Clear(tree.getRoot());*/
	/*tree.print(tree.getRoot());*/
	UniqueTree unique_tree;
	for (int i = 0; i < n; i++)
	{
		int number = rand() % 100;
		/*cout << number << tab;*/
		unique_tree.insert(number);
	}
	unique_tree.print();
	cout << endl;
	cout << "Количество элементов дерева:" << unique_tree.count() << endl;
	cout << "Минимальное значение: " << unique_tree.minValue() << endl;
	cout << "Максимальное значение: " << unique_tree.maxValue() << endl;
	cout << "Сумма элементов: " << unique_tree.Sum() << endl;
	cout << "Среднее арифметическое элементов дерева: " << unique_tree.Avg() << endl;
	cout << "Глубина дерева: " << unique_tree.depth() << endl;
	
	Tree deep_tree = { 50, 25, 75, 16, 32, 64,  85 };
	deep_tree.print();
	cout << "Глубина дерева: " << deep_tree.depth() << endl;

}