#include<iostream>
#include<string>
int main()
{
	int N, count = 0;
	std::string input;
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> input;
		int chk = 0;
		if (input.length() != 1) {
			for (int j = 0; j < input.length(); ++j) {
				if (input.find(input[j], j + 1) != std::string::npos && input[j + 1] != input[j]) {
					chk = 1;
					break;
				}
			}
		}
		if (chk == 0) count++;
	}
	std::cout << count;
	return 0;
}