#include<iostream>
using namespace std;
#define DEBUG
#define tab "\t"
#define delimiter "\n------------------------------------------\n"
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
	~Tree()
	{
		Clear(Root);
		Root = nullptr;
		cout << "TDestructor:\t" << this << endl;
		cout << delimiter;
	}
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
		if (Root->pLeft == nullptr)return Root->Data;
		return minValue(Root->pLeft);
	}
	int maxValue(Element* Root)const
	{
		if (Root->pRight == nullptr)return Root->Data;
		return maxValue(Root->pRight);
	}
	int Count(Element* Root)const
	{
		if (Root == nullptr)return 0;
		else {
			return 1 + Count(Root->pLeft) + Count(Root->pRight);
		}
	}
	int Sum(Element* Root)const
	{
		if (Root == 0) return 0;
		return Root->Data + Sum(Root->pLeft) + Sum(Root->pRight);

	}
	void Clear(Element* Root)
	{
		if (Root == nullptr)return;
		Clear(Root->pLeft);Clear (Root->pRight);
		delete Root;
	}
	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
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
		/*int number = rand() % 100;
		cout << number << tab;*/
		tree.insert(/*number*/rand() % 100, tree.getRoot());
	}
	tree.print(tree.getRoot());
	cout << delimiter;
	cout << "Количество элементов дерева:" << tree.Count(tree.getRoot()) << endl;
	cout << "Минимальное значение: " << tree.minValue(tree.getRoot()) << endl;
	cout << "Максимальное значение: " << tree.maxValue(tree.getRoot()) << endl;
	cout << "Сумма элементов: " << tree.Sum(tree.getRoot()) << endl;
	/*tree.Clear(tree.getRoot());*/
	tree.print(tree.getRoot());
	
	
}