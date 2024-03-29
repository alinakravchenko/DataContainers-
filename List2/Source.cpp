﻿#include<iostream>
//#include<exception>
using namespace std;
using std::cin;
using std::cout;
using std::endl;
#define tab "\t"
class List
{
	class Element
	{
		int Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr)
			:Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class List;
	}*Head, *Tail;
	//Element* Head;
	//Element* Tail;
	unsigned int size;
public:
	class Iterator 
	{
		Element* Temp;
	public:
		Iterator(Element* Temp) :Temp(Temp)
		{
			cout << "IConstructor:\t" << this << endl;
		}
		~Iterator()
		{
			cout << "IDestructor:\t" << this << endl;
		}
		Iterator& operator++()
		{
			Temp = Temp->pNext;
			return *this;
		}
		Iterator operator++(int)
		{
			Iterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		Iterator& operator--()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		Iterator operator--(int)
		{
			Iterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		bool operator==(const Iterator& other)const
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
	class ReverseIterator
	{
		Element* Temp;
	public:
		ReverseIterator(Element* Temp) :Temp(Temp)
		{
			cout << "RItConstructor:\t" << this << endl;
		}
		~ReverseIterator()
		{
			cout << "RItDestructor:\t" << this << endl;
		}
		ReverseIterator& operator++()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ReverseIterator operator++(int)
		{
			ReverseIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		ReverseIterator& operator--()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ReverseIterator operator--(int)
		{
			ReverseIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		bool operator==(const ReverseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const ReverseIterator& other)const
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
	ReverseIterator rbegin()
	{
		return Tail;
	}
	ReverseIterator rend()
	{
		return nullptr;
	}
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;

	}

	List()
	{
		//когда список пуст, его Head и Tail указывают на 0
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	//передаём по ссылке, чтобы не создавать копию
	List(const std:: initializer_list<int>&il) :List()
	{
		//int* - указатель
		//const int* - констанстный указатель
		//int const* - указатель на константу
		//const int const* - конст указатель на константу
		/*for (int const* it = il.begin(); it != il.end(); ++it)
			push_back(*it);*/
		for (int i : il)push_back(i);
	}

	~List()
	{
		//while (Head)pop_front();
		while (Tail)pop_back();
		cout << "LDestrcutor:\t" << this << endl;
	}

	//					                                              Adding Elements:
	void push_front(int Data)
	{
		/*Element* New = new Element(Data);
		if (Head == nullptr && Tail == nullptr)
		{
		Head = Tail = New;
		}
		else
		{
		New->pNext = Head;
		Head->pPrev = New;
		Head = New;
		}*/

		if (Head == nullptr&&Tail == nullptr)
			Head = Tail = new Element(Data);
		else
			Head = Head->pPrev = new Element(Data, Head);
		size++;
	}
	void push_back(int Data)
	{
		/*Element* New = new Element(Data);
		if (Head == nullptr && Tail == nullptr)
		{
		Head = Tail = New;
		}
		else
		{
		New->pPrev = Tail;
		Tail->pNext = New;
		Tail = New;
		}*/

		if (Head == nullptr && Tail == nullptr)
			Head = Tail = new Element(Data);
		else
			Tail = Tail->pNext = new Element(Data, nullptr, Tail);
		size++;
	}
	void insert(int Data, int Index)
	{
		if (Index > size)throw std::out_of_range("Error: Out of range exception");
		//out of range - выход за пределы 
			/*throw exception("Error: Out of range");*/
		if (Index == 0)return push_front(Data);
		if (Index == size)return push_back(Data);

		Element* Temp;
		if (Index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < Index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - Index- 1; i++)Temp = Temp->pPrev;
			/*Element* New = new Element(Data);
			New->pNext = Temp;
			New->pPrev = Temp->pPrev;
			Temp->pPrev->pNext = New;
			Temp->pPrev = New;*/
			Temp->pPrev=Temp->pPrev->pNext= new Element(Data, Temp, Temp->pPrev);
			size++;
		}
	}

	//					                                            Removing Elements:
	void pop_front()
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
		}
		else
		{
			Head = Head->pNext;
			delete Head->pPrev;
			Head->pPrev = nullptr;
		}
		size--;
	}
	void pop_back()
	{
		if (Head == Tail)return pop_front();
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		size--;
	}
	void erase(int Index)
	{
		if (Index > size)throw out_of_range("Error: Out of range exception in erace() function");
		if (Index == 0)return pop_front();
		/*if (Index == size - 1) return pop_back();*/
        //1)доходим до удаляемого элемента
		Element* Temp;
		if (Index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < Index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size-Index - 1; i++)Temp = Temp->pPrev;
		}
		//2)исключаем элемент из списка
		Temp->pPrev->pNext = Temp->pNext;
		Temp->pNext->pPrev = Temp->pPrev;
		//3) удаляем элемент из памяти
		delete Temp;
		size--;
    }
	//					                                                  Methods:
	void print()const
	{
		cout << "Head: " << Head << endl;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов " << size << endl;
	}
	void reverse_print()const
	{
		cout << "Tail: " << Tail << endl;
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов " << size << endl;
	}
};
//#define BASE_CHECK
void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	list.reverse_print();
	int value;
	int Index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	cout << "Введите индекс добавляемого элемента: "; cin >> Index;
	try
	{

		list.insert(value, Index);
		list.print();
		list.reverse_print();
	}
	catch (const exception& e)
	{
		//вывод на экран
		cerr << e.what() << endl;
	}
	cout << "Введите индекс удаляемого элемента: "; cin >> Index;
	try
	{
	list.erase(Index);
	list.print();
	list.reverse_print();
	}
	catch (const std::exception& e)
	{
		cerr << e.what() << endl;
	}
#endif //BASE_CHECK
	List list = { 3,5,8,13,21 };
	list.print();
	for (int i : list)cout << i << tab; cout << endl;

	List::ReverseIterator rend = list.rend();
	for (List::ReverseIterator rit = list.rbegin(); rit != rend; ++rit)
	{
		cout << *rit << tab;
	}
	cout << endl;
}
/*
исключение (exception)
throw exception бросить исключение 
try
{
   
}
catch(type name) - ловит и обр. исключ.
{

}

универсальный catch(...)
{}
*/