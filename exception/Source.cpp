#include<iostream>
using namespace std;
//#define TRY_SYNTAX
void main()
{
	setlocale(LC_ALL, "");
#ifdef TRY_SYNTAX
	/*throw 1;*/ //���������� �����������, ����� ������

	//��� ��������� ����������, ������ catch()
	try
	{
		throw 1;
	}
	//��������� �� ��������������, ����� ������
	catch (short e)
	{
		cerr << "Error #" << e << "(short)\n";
	}
	//��� ��� 1 int
	catch (int e)
	{
		cerr << "Error #" << e << " (int)\n";
	}
#endif


	/*cout << 2 / 0 << endl;*/
	//������: ������������� ������� �� 0
	int a, b;
	cout << "������� ��� �����: "; cin >> a >> b;
	//����� ������������
	try
	{
	cout << a / b << endl;
	}
	catch (...)
	{
		cerr << "Something happened :(\n" << endl;
	}
}