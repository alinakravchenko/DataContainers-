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
	static int count;
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};
int Element::count = 0;
class ForwardList
{
	Element* Head; //указывает на начало элемента списка (голова списка)
	unsigned int size;
public:
	ForwardList()
	{
		Head = nullptr; //когда head списка указ. на ноль - список пуст
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(const ForwardList& other) :ForwardList()
	{
		Element* Temp = other.Head;
		while (Temp)
		{
			push_back(Temp->Data);
			Temp = Temp->pNext;
		}
		cout << "LCopyConstructor: " << this << endl;
	}
	~ForwardList()
	{
		cout << "\n-------------------------------------\n";
		while (Head) pop_front();//очищает список перед удалением
		cout << "LDestructor:\t" << this << endl;
	}
	//                      Operators:
	ForwardList& operator=(const ForwardList& other)
	{
		while (Head)pop_front();
		Element* Temp = other.Head;
		while (Temp)
		{
			push_back(Temp->Data);
			Temp = Temp->pNext;
		}
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
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
		size++;
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
		size++;
	}
	void insert(int Data, int Index)
	{
		if (Index == 0)return push_front(Data);
		if (Index == size)return push_back(Data);
		if (Index > size)return;
		Element* New = new Element(Data);
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;
		New->pNext = Temp->pNext;
		Temp->pNext = New;
		size++;
	}
	void erase(int Index)
	{
		if (Index > Head->count)return;
		if (Index == 0) return pop_front();
		if (Index == Head->count - 1) return pop_back();
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++) Temp = Temp->pNext;
		Element* Erased = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete Erased;
		size++;

	}
	//                      Removing elements
	void pop_front()
	{
		Element* fr = Head;
		Head = Head->pNext;
		//удаление элемента из списка
		delete fr;
		size--;
	}
	void pop_back()
	{
		if (Head->pNext == nullptr)return pop_front();
		Element* Temp = Head;
		while (Temp->pNext->pNext != nullptr)
		{
			Temp = Temp->pNext;
		}
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
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
		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количество элементов: " << Element::count << endl;
	}
};

#define BASE_CHECK
//#define COUNT_CHECK
void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n; //размер списка
	cout << "Введите размер списка: "; cin >> n;

	ForwardList list; //односвязный список 
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
		/*list.push_back(rand() % 100);*/
	}
	list.print();
	list.push_back(19);
	list.print();
	list.pop_front();
	list.print();
	list.pop_back();
	list.print();
	int value;
	int index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	list.insert(value, index);
	list.print();
	/*ForwardList list2 = list;*/ //CopyConstr
	ForwardList list2;
	list2 = list;
	list2.print();

#endif
#ifdef COUNT_CHECK
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);
	list1.print();

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print();
#endif

}