#include<iostream>
#include<string>
#include<vector>

int main()
{
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int a,b;
	while (1) {
		std::cin >> a >> b;
		if (a == 0 && b == 0) break;
		if (a < b && b % a == 0) std::cout << "factor\n";
		else if (b < a && a % b == 0) std::cout << "multiple\n";
		else std::cout << "neither\n";
	}
	return 0;
}