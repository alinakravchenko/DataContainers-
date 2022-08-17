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
		clear(Root);
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
			//���������, ���� ��� ������ ������� � ��������
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			// ���� ����, �� ���� ���� ��� �������� 
			else insert(Data, Root->pLeft);
		}
		//���� Data �� ������, ��� Root Data
		else 
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
	int minValue(Element* Root)const
	{
		//����� ��������� �������� �������� � ����� ������� 
		if (Root->pLeft == nullptr)return Root->Data;
		return minValue(Root->pLeft);
	}
	int maxValue(Element* Root)const
	{
		if (Root->pRight == nullptr)return Root->Data;
		return maxValue(Root->pRight);
	}
	void clear(Element* Root)
	{
		if (Root == nullptr)return;
		//�������� �� ������ �� ��������� ��������
		clear(Root->pLeft); clear(Root->pRight);
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
	cout << "������� ������ ������: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		/*int number = rand() % 100;
		cout << number << tab;*/
		tree.insert(/*number*/rand() % 100, tree.getRoot());
	}
	tree.print(tree.getRoot());
	cout << delimiter;
	cout << "����������� ��������: " << tree.minValue(tree.getRoot()) << endl;
	cout << "������������ ��������: " << tree.maxValue(tree.getRoot()) << endl;
	tree.clear(tree.getRoot());
	/*tree.print(tree.getRoot());*/
	
}