#include<iostream>
#include<string>
int main() {
	std::string N;
	while (1) {
		std::cin >> N;
		if (N == "0") break;
		int sum = 2; // 양 끝 
		for (int i = 0; i < N.size(); i++) {
			if (N[i] == '1') sum += 2;
			else if (N[i] == '0') sum += 4;
			else sum += 3;
		}
		sum += (N.size() - 1);
		std::cout << sum << std::endl;
	}
	return 0;
}