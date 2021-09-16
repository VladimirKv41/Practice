#include <iostream>
#include <string>

using namespace std;

int main()
{
	cout << "Enter string: ";
	string string;
	getline(cin,string);
	cout << "You entered: "<< string << "\n";
	return 0; 
}
