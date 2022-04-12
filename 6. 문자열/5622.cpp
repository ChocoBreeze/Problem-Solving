#include<iostream>
#include<string>
int main()
{
	std::string input;
	std::cin >> input;
	int sum = 0;
	for (auto i : input) {
		if (i >= 'A' && i <= 'C') sum += 3;
		else if (i >= 'D' && i <= 'F') sum += 4;
		else if (i >= 'G' && i <= 'I') sum += 5;
		else if (i >= 'J' && i <= 'L') sum += 6;
		else if (i >= 'M' && i <= 'O') sum += 7;
		else if (i >= 'P' && i <= 'S') sum += 8;
		else if (i >= 'T' && i <= 'V') sum += 9;
		else sum += 10;
	}
	std::cout << sum;
	return 0;
}