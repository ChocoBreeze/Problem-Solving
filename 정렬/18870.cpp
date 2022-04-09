#include<iostream>
#include<vector>
#include<map>
#include<utility>

int main() {
	int N, a;
	std::vector<int> coord;
	std::map<int, int> coord_sort;

	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	std::cin >> N;
	
	for (int i = 0; i < N; ++i) {
		std::cin >> a;
		coord.push_back(a);
		coord_sort.emplace(std::make_pair(a, i));
	}
	a = 0;
	for (auto i = coord_sort.begin(); i != coord_sort.end(); ++i, ++a) { // indexing
		i->second = a;
	}

	for (auto i = coord.begin(); i != coord.end(); ++i) {
		std::cout << coord_sort[*i] << " ";
	}
	return 0;
}