#include<vector>
#include<iostream>
#include<algorithm>
#include<string>
#include<utility>

int main() {
	int N, a;
	std::string b;

	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	std::cin >> N;
	std::vector<std::tuple<int, std::string, int>> member_list;
	for (int i = 0; i < N; ++i) {
		std::cin >> a >> b;
		member_list.push_back(std::make_tuple(a, b, i));
	}

	auto comparable = [](std::tuple<int, std::string, int> a, std::tuple<int, std::string, int> b) {
		if (std::get<0>(a) < std::get<0>(b)) return true;
		else if (std::get<0>(a) == std::get<0>(b) && std::get<2>(a) < std::get<2>(b)) return true;
		else return false;
	};

	std::sort(member_list.begin(), member_list.end(), comparable);
	for (auto i = member_list.begin(); i != member_list.end(); ++i) {
		std::cout << std::get<0>(*i) << " " << std::get<1>(*i) << "\n";
	}
	return 0;
}