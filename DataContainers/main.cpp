#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;
class ForwardList;
#define tab "\t"
class Element
{
	int Data;		//значение элемента
	Element* pNext;	//адрес следующего элемента
	static int count;
public:
	/*int getData()const
	{
		return Data;
	}
	Element* getpNext()const
	{
		return pNext;
	}*/
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
	friend class Iterator;
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};
int Element::count = 0;
class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp = nullptr) :Temp(Temp)
	{
		cout << "ItConstructor:\t" << this << endl;
	}
	~Iterator()
	{
		cout << "ItDestructor:\t" << this << endl;
	}

	Iterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}
	Iterator operator++(int)//suffix incr
	{
		Iterator old = *this;
		Temp = Temp->pNext;
		return old;
	}
	bool operator==(const Iterator& other)const   //const значит, что не меняем this
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const Iterator& other)const
	{
		return this->Temp != other.Temp;
	}
	const int& operator*()const
	{
		return Temp->Data;
	}
	 int& operator*()
	{
		return Temp->Data;
	}
};
class ForwardList
{
protected:
	Element* Head; //указывает на начало элемента списка (голова списка)
	unsigned int size;
public:
	/*Element* getHead()const
	{
		return Head;
	}*/
	// 1) begin()- возвращает итератор на началo контейнера
	 Iterator begin()
	{
		return Head;
	}
	 //end()- возвращает итератор на конец контейнера
    Iterator end() 
	{
		return nullptr;
	}
	ForwardList()
	{
		Head = nullptr; //когда head списка указ. на ноль - список пуст
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(initializer_list<int>il) :ForwardList()
	{
		//у люб. контейнера есть методы:
		//begin()- возвращает итератор на началo контейнера
		//end()- возвращает итератор на конец контейнера
		cout << typeid(il.begin()).name() << endl;
		for (const int* it = il.begin(); it != il.end(); it++)
		{
			//it - итератор для проходжения по initializer_list
			push_back(*it); //разыменовываем it
		}
		
	}
	ForwardList(const ForwardList& other):ForwardList()
	{
		/*Element* Temp = other.Head;
		while (Temp)
		{
			push_back(Temp->Data);
			Temp = Temp->pNext;
		}*/
		*this = other;  //CopyAssignment
		cout << "LCopyConstructor: " << this << endl;
	}
	ForwardList(ForwardList&& other):ForwardList()
	{
		/*this->Head= other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;*/
		*this = std::move(other);  //глобальная функция move принудительно вызывает
		cout << "LMoveConstructor\t" << this << endl;

	}
	~ForwardList()
	{
		while (Head) pop_front();//очищает список перед удалением
		cout << "LDestructor:\t" << this << endl;
	}
	//                      Operators:
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;
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
	ForwardList& operator=(ForwardList&& other)
	{
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;
		cout << "MoveAssignment:\t" << this << endl;
		return *this;
	}
	
	//						Adding elements:
	void push_front(int Data)
	{
		////1) создаем элемент:
		//Element* New = new Element(Data);
		////2) присоединяем новый элемент к началу списка:
		//New->pNext = Head;
		////3) новый элемент является head списка:
		//Head = New;
		Head = new Element(Data, Head);
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		/*Element* New = new Element(Data);*/
		/*Element* Temp = Head;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}
		Temp->pNext = New;*/
		Element* Temp = Head;
		for (; Temp->pNext != nullptr; Temp = Temp->pNext);
		Temp->pNext = new Element(Data);
		size++;
	}
	void insert(int Data, int Index)
	{
		if (Index == 0)return push_front(Data);
		if (Index == size)return push_back(Data);
		if (Index > size)return;
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;
		Temp->pNext = new Element(Data, Temp->pNext);
		size++;
		/*Element* New = new Element(Data);
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;
		New->pNext = Temp->pNext;
		Temp->pNext = New;*/
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
		//Element* Temp = Head;	//Temp - итератор.
		////итератор - это указатель, при помощи которого можно получить доступ к элементам структуры данных.
		//while (Temp)
		//{
		//	cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		//	Temp = Temp->pNext;	//переход на следующий элемент.
		//}
		for(Element* Temp = Head; Temp; Temp=Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количество элементов: " << Element::count << endl;
	}
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};
ForwardList operator+(const ForwardList& left, const ForwardList& right) 
{
	ForwardList cat = left; //левый список скопирован с результат
	/*Element* Temp = right.Head;
	while (Temp)
	{
		cat.push_back(Temp->Data);
		Temp = Temp->pNext;
	}*/
	for (Element* Temp = right.Head; Temp; Temp = Temp->pNext)cat.push_back(Temp->Data);
	cout << "Operator + "<<endl;
	return cat;

}


//#define BASE_CHECK
//#define OPERATOR_PLUS_CHECK
//#define RANGE_BASED_ARRAY
//#define RANGE_BASED_FOR_LIST
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
	list = list;
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
	cout << tab;
	ForwardList list2 = list; //CopyConstr
	/*ForwardList list2;
	list2 = list;*/
	list2.print();
	cout << tab;

#endif
#ifdef OPERATOR_PLUS_CHECK
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
	cout << tab;
	/*ForwardList list3=list1 + list2;*/ //MoveConstr
	ForwardList list3;
	list3 = list1 + list2;
	cout << tab;
	list3.print();
#endif
#ifdef RANGE_BASED_ARRAY
	int arr[] = { 3, 5, 8, 13, 21 };

	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
		cout << arr[i] << tab;
	cout << endl;

	for (int i : arr)  //range-based for (цикл for на основе диапазона, цикл for для контейнеров)
		cout << i << tab;
	cout << endl;
	//итератор 'i' последовательно принимает значение каждого элемента массива 
#endif
#ifdef RANGE_BASED_FOR_LIST
	ForwardList list = { 3, 5, 8, 13, 21 };
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;
	/*list.print();*/
	/*for (Iterator it = list.begin(); it != list.end(); it++)
	{
		cout << *it << tab;
	}*/

#endif
	
}