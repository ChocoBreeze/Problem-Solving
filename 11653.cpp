#include<iostream>
int main() {
	int N, start = 2;
	std::cin >> N;
	while (N != 1) {
		if (N % start == 0) {
			std::cout << start << std::endl;
			N /= start;
		}
		else {
			if (start == 2) start++;
			else start += 2;
		}
	}
	return 0;
}