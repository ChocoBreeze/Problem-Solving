#include<iostream>
int main() {
	int T, H, W, N;
	std::cin >> T;
	for (int i = 0; i < T; i++) {
		std::cin >> H >> W >> N;
		if (N%H == 0) std::cout << H*100+(N / H) << std::endl;
		else std::cout << (N % H)*100+(N / H) + 1 << std::endl;
	}
	return 0;
}