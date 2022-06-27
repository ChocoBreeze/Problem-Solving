#include<vector>
#include<iostream>
#include<algorithm>
#include<utility>
int main() {
	int N, a, b;
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	std::cin >> N;
	std::vector<std::pair<int, int>> coord;
	for (int i = 0; i < N; ++i) {
		std::cin >> a >> b;
		coord.push_back(std::make_pair(a, b));
	}

	auto comparable = [](std::pair<int, int> a, std::pair<int, int> b) {
		if (a.second < b.second) return true;
		else if (a.second == b.second && a.first < b.first) return true;
		else return false;
	};

	std::sort(coord.begin(), coord.end(), comparable);
	for (auto i = coord.begin(); i != coord.end(); ++i) {
		std::cout << i->first << " " << i->second << "\n";
	}
	return 0;
}