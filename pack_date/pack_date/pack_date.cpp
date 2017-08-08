#include <iostream>
#include <Windows.h>
#include <datetimeapi.h>
using namespace std;
void DisplayBits(unsigned int value);
void PackData(unsigned int a, unsigned int b, unsigned int c,unsigned int d);
void main()
{
	unsigned int day, month, year,date=0;
	cout << "Enter the day:\n";
	cin >> day;
	cout << "Enter the month:\n";
	cin >> month;
	cout << "Enter the year:\n";
	cin >> year;
	PackData(day, month, year, date);
	system("pause");
}
void PackData(unsigned int a, unsigned int b, unsigned int c,unsigned int d)
{
	d = c;
	d = d | (b<<11);
	d = d | (a<<15);
	cout << d<<"\n";
	DisplayBits(d);
}
void DisplayBits(unsigned int value)
{
	unsigned int c = 0;
	unsigned int displayMask = 1 << 31;
	//cout << setw(12) << value << " = ";
	for (c = 1; c <= 32; c++)
	{
		cout << (value & displayMask ? '1' : '0');
		displayMask >>= 1;
		if (c % 8 == 0)
		{
			cout << ' ';
		}
	}
	cout << endl;
}