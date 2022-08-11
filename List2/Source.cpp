#include<iostream>
/*
------------------------------------------------
Class object; - �������� ������� �������� ������ 
Class<type> object; - �������� ������� ���������� ������
��� type - ��� �����  ������������ �������
------------------------------------------------
*/
//#include<exception>
using namespace std;
using std::cin;
using std::cout;
using std::endl;
#define tab "\t"
template<typename T>
class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr) :
			Data(Data), pNext(pNext), pPrev(pPrev)
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
	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp = nullptr) :Temp(Temp)
		{
			cout << "CBItConstructor:\t" << this << endl;
		}
		~ConstBaseIterator()
		{
			cout << "CBItDestructor:\t" << this << endl;
		}

		bool operator==(const ConstBaseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const ConstBaseIterator& other)const
		{
			return this->Temp != other.Temp;
		}

		const T& operator*()const
		{
			return Temp->Data;
		}
	};
public:
	class ConstIterator :public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp) :ConstBaseIterator(Temp)
		{
#ifdef DEBUG
			cout << "CItConstructor:\t" << this << endl;
#endif
		}
		~ConstIterator()
		{
#ifdef DEBUG
			cout << "CItDestructor:\t" << this << endl;
#endif 
		}

		ConstIterator& operator++()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ConstIterator operator++(int)
		{
			ConstIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		ConstIterator& operator--()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ConstIterator operator--(int)
		{
			ConstIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
	};
	class ConstReverseIterator :public ConstBaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp) :ConstBaseIterator(Temp)
		{
#ifdef DEBUG
			cout << "CRItConstructor:\t" << this << endl;
#endif 
		}
		~ConstReverseIterator()
		{
#ifdef DEBUG
			cout << "CRItDestructor:\t" << this << endl;
#endif 
		}

		ConstReverseIterator& operator++()
		{
			ConstBaseIterator::Temp = Temp->pPrev;
			return *this;
		}
		ConstReverseIterator operator++(int)
		{
			ConstReverseIterator old = *this;
			ConstBaseIterator::Temp = Temp->pPrev;
			return old;
		}
		ConstReverseIterator& operator--()
		{
			ConstBaseIterator::Temp = Temp->pNext;
			return *this;
		}
		ConstReverseIterator operator--(int)
		{
			ConstReverseIterator old = *this;
			ConstBaseIterator::Temp = Temp->pNext;
			return old;
		}
	};
	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp = nullptr) :ConstIterator(Temp) {}
		T& operator*()
		{
			return ConstBaseIterator::Temp->Data;
		}
	};
	class ReverseIterator :public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp = nullptr) :ConstReverseIterator(Temp) {}
		T& operator*()
		{
			return ConstBaseIterator::Temp->Data;
		}
	};

	ConstIterator cbegin()const
	{
		return Head;
	}
	ConstIterator cend()const
	{
		return nullptr;
	}
	ConstReverseIterator crbegin()
	{
		return Tail;
	}
	ConstReverseIterator crend()
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
		//����� ������ ����, ��� Head � Tail ��������� �� 0
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	//������� �� ������, ����� �� ��������� �����
	List(const std:: initializer_list<T>&il) :List()
	{
		//int* - ���������
		//const int* - ������������ ���������
		//int const* - ��������� �� ���������
		//const int const* - ����� ��������� �� ���������
		for (T const* it = il.begin(); it != il.end(); ++it)
			push_back(*it);
		/*for (T  i : il)push_back(i);*/
	}
	//��� ������� ��� ������ type name 
	List(const List<T>& other) :List()
	{
		for (ConstIterator it = other.cbegin(); it != other.cend(); ++it)push_back(*it);
	}
	~List()
	{
		//while (Head)pop_front();
		while (Tail)pop_back();
		cout << "LDestrcutor:\t" << this << endl;
	}

	//					                                              Adding Elements:
	void push_front(T Data)
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
	void push_back(T Data)
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
	void insert(T Data, int Index)
	{
		if (Index > size)throw std::out_of_range("Error: Out of range exception");
		//out of range - ����� �� ������� 
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
        //1)������� �� ���������� ��������
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
		//2)��������� ������� �� ������
		Temp->pPrev->pNext = Temp->pNext;
		Temp->pNext->pPrev = Temp->pPrev;
		//3) ������� ������� �� ������
		delete Temp;
		size--;
    }
	//					                                                  Methods:
	void print()const
	{
		cout << "Head: " << Head << endl;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "���������� ��������� " << size << endl;
	}
	void reverse_print()const
	{
		cout << "Tail: " << Tail << endl;
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "���������� ��������� " << size << endl;
	}
};
template<typename T>
//type   //name    //(parameters)
List<T> operator+(const List<T>& left, const List<T>& right)
{
	List<T> cat = left;
	for (typename List<T>::ConstIterator it = right.cbegin(); it != right.cend(); ++it)
	{
		cat.push_back(*it);
		//(*it) *= 100;
	}
	return cat;
}
//#define BASE_CHECK
//#define ITERATORS_CHECK1
void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "������� ������ ������: "; cin >> n;
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
	cout << "������� �������� ������������ ��������: "; cin >> value;
	cout << "������� ������ ������������ ��������: "; cin >> Index;
	try
	{

		list.insert(value, Index);
		list.print();
		list.reverse_print();
	}
	catch (const exception& e)
	{
		//����� �� �����
		cerr << e.what() << endl;
	}
	cout << "������� ������ ���������� ��������: "; cin >> Index;
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
#ifdef ITERATORS_CHECK1
	List list = { 3,5,8,13,21 };
	list.print();
	for (int i : list)cout << i << tab; cout << endl;

	List::ReverseIterator rend = list.rend();
	for (List::ReverseIterator rit = list.rbegin(); rit != rend; ++rit)
	{
		cout << *rit << tab;
	}
	cout << endl;
#endif
	List<int> list1 = { 3,5,8,13,21 };
	List<int> list2 = { 34,55,89 };
	List<int> list3 = list1 + list2;
	for (int i : list1)cout << i << tab; cout << endl;
	for (int i : list2)cout << i << tab; cout << endl;
	for (int i : list3)cout << i << tab; cout << endl;
}
/*
���������� (exception)
throw exception ������� ���������� 
try
{
   
}
catch(type name) - ����� � ���. ������.
{

}

������������� catch(...)
{}
*/