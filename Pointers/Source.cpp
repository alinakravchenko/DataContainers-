#include<iostream>
//#include<exception>
using namespace std;
using std::cin;
using std::cout;
using std::endl;
#define tab "\t"
void main()
{
	setlocale(LC_ALL, "");
	const int n = 5;
	int arr[n] = { 3,5,8,13,21 };
	/*const int* p_arr = arr;*/ //указатель на конст
	/*int const* p_arr = arr;*/ //указатель на конст
	//int* cont p_arr=arr; //константный указатель
	const int* const p_arr = arr; //конст указатель на конст
	for (int i = 0; i < n; i++)
	{
		*(p_arr + i) *= 10;
		//(p_arr+i)*=10;
		/**p_arr *= 10;*/
		cout << *(p_arr+i) << tab;
		/*p_arr++;*/
	}
	cout << endl;
}