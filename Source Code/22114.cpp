#include<iostream>
#include<vector>

int main() {
	int N, K,temp;
	std::vector<int> L;
	std::cin >> N >> K;
	for (int i = 0; i < N - 1; ++i) {
		std::cin >> temp;
		L.push_back(temp);
	}
	int max_count = -1;
	for (int i = 0; i < N - 1; ++i) {
		int count = 1, jump = 1, j=i; // j = 시작점
		if (max_count > N - i) break;
		while(j < N - 1) {
			if (jump == 0 && L[j] > K) break;
			if (L[j] > K) {
				--jump; 
				++count;
			}
			else ++count;
			++j;
		}
		if (max_count < count) max_count = count;
	}
	std::cout << max_count;
	return 0;
}