#include<iostream>
int main() {
	int A, B, C;
	std::cin >> A >> B >> C;
	std::cout << (A + B) % C << std::endl;
	std::cout << ((A % C) + (B % C)) % C << std::endl;
	std::cout << (A * B) % C << std::endl;
	std::cout << ((A % C) * (B % C)) % C;
	return 0;
}