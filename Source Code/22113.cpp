#include<iostream>
#include<vector>

int main() {
	int N, M, temp;
	using std::vector;
	std::cin >> N >> M;
	vector<int> Bus;
	for (int i = 0; i < M; ++i) {
		std::cin >> temp;
		Bus.push_back(temp);
	}
	vector<vector<int>> cost;
	for (int i = 0; i < N; ++i) {
		vector<int> cost_temp;
		for (int j = 0; j < N; ++j) {
			std::cin >> temp;
			cost_temp.push_back(temp);
		}
		cost.push_back(cost_temp);
	}
	int sum = 0;
	for (int i = 0; i < M - 1; ++i) {
		sum += cost[Bus[i]-1][Bus[i + 1]-1];
	}
	std::cout << sum;
	return 0;
}