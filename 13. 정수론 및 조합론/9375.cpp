#include<iostream>
#include<string>
#include<map>

int main() {
	int T, N;
	std::string a, b;
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	std::map<std::string, int> dict;
	std::cin >> T;
	for (int i = 0; i < T; ++i) {
		std::cin >> N;
		dict.clear();
		for (int j = 0; j < N; ++j) {
			std::cin >> a >> b;
			if (dict.find(b) == dict.end()) dict.emplace(std::make_pair(b, 1));
			else dict[b]++;
		}
		int sum = 1;
		for (auto i = dict.begin(); i != dict.end(); ++i) {
			sum *= i->second + 1;
		}
		std::cout << sum - 1 << "\n";
	}
	return 0;
}