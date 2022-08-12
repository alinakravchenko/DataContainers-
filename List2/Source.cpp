﻿//#include"List.h"
#include"List.cpp"

//#define BASE_CHECK
//#define ITERATORS_CHECK1
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
	list1 = list1;
	List<int> list2 = { 34,55,89 };
	List<int> list3 = list1 + list2;
	for (int i : list1)cout << i << tab; cout << endl;
	for (int i : list2)cout << i << tab; cout << endl;
	for (int i : list3)cout << i << tab; cout << endl;

	List<double> d_list = { 1.5, 2.7, 3.14, 8.3 };
	d_list.print();
	for (double i : d_list)cout << i << tab; cout << endl;
	for (List<double>::ReverseIterator rit = d_list.rbegin(); rit != d_list.rend(); ++rit)
		cout << *rit << tab;
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