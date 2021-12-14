#include <iostream>
#include <string>
using namespace std;

string getNumberStr(double num);
int main() {
	cout << getNumberStr(50) << endl;
	return 0;
}
string getNumberStr(double num) {
	string number_str = "";
	if (num >= 0) {
		number_str += " ";//digit of sign
	}
	else if (num < 0) {
		number_str += to_string(num);//digit of sign
	}
	return number_str;
}