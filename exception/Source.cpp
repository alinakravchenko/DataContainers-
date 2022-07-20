#include<iostream>
using namespace std;
//#define TRY_SYNTAX
void main()
{
	setlocale(LC_ALL, "");
#ifdef TRY_SYNTAX
	/*throw 1;*/ //сбрасываем исключерние, выдаёт ошибку

	//для обработки исключения, создаём catch()
	try
	{
		throw 1;
	}
	//исключние не обрабатывается, выдаёт ошибку
	catch (short e)
	{
		cerr << "Error #" << e << "(short)\n";
	}
	//так как 1 int
	catch (int e)
	{
		cerr << "Error #" << e << " (int)\n";
	}
#endif


	/*cout << 2 / 0 << endl;*/
	//ошибка: целочисленное деление на 0
	int a, b;
	cout << "введите два числа: "; cin >> a >> b;
	//чтобы обработалось
	try
	{
	cout << a / b << endl;
	}
	catch (...)
	{
		cerr << "Something happened :(\n" << endl;
	}
}