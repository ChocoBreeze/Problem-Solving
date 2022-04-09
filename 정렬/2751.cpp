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
	std::sort(list.begin(), list.end());
	std::for_each(list.begin(), list.end(), [](const int& n) {std::cout << n << "\n"; });
	return 0;
}