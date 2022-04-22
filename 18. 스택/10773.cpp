#include<iostream>
#include<vector>
int main() {
	int N, a;
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	std::cin >> N;
	std::vector<int> record;
	for (int i = 0; i < N; ++i) {
		std::cin >> a;
		if (a == 0) record.pop_back();
		else record.push_back(a);
	}
	int sum = 0;
	for (auto i = record.begin(); i != record.end(); ++i) {
		sum += *i;
	}
	std::cout << sum;
	return 0;
}