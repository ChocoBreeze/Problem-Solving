#include<iostream>

int main()
{
	int A, B, C;
	std::cin >> A >> B >> C;
	A = (A + (B + C) / 60) % 24;
	B = (B + C) % 60;
	std::cout << A << " " << B;
	return 0;
}