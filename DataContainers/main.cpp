#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
class Element
{
	int Data;		//значение элемента
	Element* pNext;	//адрес следующего элемента
public:
	Element(int Data, Element* pNext=nullptr) :Data(Data), pNext(pNext)
	{
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};
class ForwardList
{
	Element* Head; //указывает на начало элемента списка (голова списка)
public:
	ForwardList()
	{
		Head = nullptr; //когда head списка указ. на ноль - список пуст
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "\n-------------------------------------\n";
		while (Head) pop_front();//очищает список перед удалением
		cout << "LDestructor:\t" << this << endl;
	}
	//						Adding elements:
	void push_front(int Data)
	{
		//1) создаем элемент:
		Element* New = new Element(Data);
		//2) присоединяем новый элемент к началу списка:
		New->pNext = Head;
		//3) новый элемент является head списка:
		Head = New;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		Element* New = new Element(Data);
		/*Element* Temp = Head;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}
		Temp->pNext = New;*/
		Element* Temp = Head;
		for (; Temp->pNext != nullptr; Temp = Temp->pNext);
		Temp->pNext = New;
	}
	//                      Removing elements
	void pop_front()
	{
		Element* fr = Head;
		Head = Head->pNext;
		//удаление элемента из списка
		delete fr;
	}
	void pop_back()
	{
		/*if (Head->pNext == nullptr)return pop_front();*/
		Element* Temp = Head;
		while (Temp->pNext->pNext!=nullptr)
		{
			Temp = Temp->pNext;
		}
		delete Temp->pNext;
		Temp->pNext = nullptr;

	}
	
	//						Methods:
	void print()const
	{
		Element* Temp = Head;	//Temp - итератор.
		//итератор - это указатель, при помощи которого можно получить доступ к элементам структуры данных.
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;	//переход на следующий элемент.
		}
	}
};

void main()
{
	setlocale(LC_ALL, "");
	int n; //размер списка
	cout << "Введите размер списка: "; cin >> n;

	ForwardList list; //односвязный список 
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();
	list.push_back(19);
	list.print();
	list.pop_front();
	list.print();
	list.pop_back();
	list.print();
}