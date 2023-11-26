#include <iostream>
#include <iomanip>
#define STAMP_PRISE 47
using namespace std;

int main()
{
	cout << "Please enter number of dollars:";
	double dollar;
	cin >> dollar;
	int dollars = dollar * 100;
	int first_class_stamps = dollars / STAMP_PRISE;
	int penny_stamps = dollars % STAMP_PRISE;
	cout << "The number of first class stamps is:" << first_class_stamps << endl
		 << "The number of second class stamps is:" << penny_stamps << endl;
 } 
