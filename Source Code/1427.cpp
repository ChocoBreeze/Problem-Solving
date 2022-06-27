#include<string>
#include<iostream>
#include<algorithm>
int main() {
	std::string N;
	std::cin >> N;
	std::sort(N.begin(), N.end(), [](int a, int b) {return a > b; });
	std::cout << N;
	return 0;
}