// bubble
#include<iostream>
#include<vector> 
#include<algorithm>
int main() {
	int N, tmp;
	std::vector<int> list;
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> tmp;
		list.push_back(tmp);
	}
	for (int i = 0; i < N - 1; ++i) {
		for (int j = i + 1; j < N; ++j) {
			if (list[i] > list[j]) { tmp = list[j]; list[j] = list[i]; list[i] = tmp; }
		}
	}
	std::for_each(list.begin(), list.end(), [](const int& n) {std::cout << n << "\n"; });
	return 0;
}