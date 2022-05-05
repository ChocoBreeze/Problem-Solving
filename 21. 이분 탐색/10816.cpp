// 여러번 틀림
// upper_bound, lower_bound에 대해 배움
#include<vector>
#include<algorithm> // sort, upper_bound, lower_bound
#include<iostream>

int main() {
	int N, temp, M;
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	std::cin >> N;
	std::vector<int> elements;
	for (int i = 0; i < N; ++i) {
		std::cin >> temp;
		elements.push_back(temp);
	}
	std::sort(elements.begin(), elements.end());
	std::cin >> M;
	for (int j = 0; j < M; ++j) {
		std::cin >> temp;
		auto ub = std::upper_bound(elements.begin(), elements.end(), temp);
		auto lb = std::lower_bound(elements.begin(), elements.end(), temp);
		std::cout << std::distance(lb,ub) << " ";
	}
	return 0;
}