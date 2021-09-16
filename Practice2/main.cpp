#include <iostream>

using namespace std;

void enter_number(int32_t &number)
{
	cout << "Enter number: ";
	cin >> number;
	if (!cin || cin.peek() != '\n') {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Not 32-bit signed integer\n";
		enter_number(number);
	}
}

int main()
{
	int32_t first, second;
	enter_number(first);
	enter_number(second);
	cout << "Sum: " << first << "+" << second << "=" << first+second << "\n";
	return 0;
}
