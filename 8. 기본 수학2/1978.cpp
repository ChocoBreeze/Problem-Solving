#include<iostream>
int main() {
	int N,count=0,K;
	std::cin >> N;
	for (int i = 0; i < N; i++) {
		std::cin >> K;
		if (K==1 || (K % 2 == 0 && K != 2)) continue;
		else {
			int chk = 0;
			for (int j = 3; j < K - 1; j++) {
				if (K % j == 0) {
					chk = 1;
					break;
				}
			}
			if (chk == 0) count++;
		}
	}
	std::cout << count;
}