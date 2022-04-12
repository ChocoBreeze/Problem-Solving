#include<string>
#include<iostream>

int main() {
	int N, repeat;
	std::string str;
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> repeat >> str;
		for (int j = 0; j < str.length(); ++j) {
			for (int k = 0; k < repeat; k++) {
				std::cout << str[j];
			}
		}
		std::cout << std::endl;
	}
	return 0;
}