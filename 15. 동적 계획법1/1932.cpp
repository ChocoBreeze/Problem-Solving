#include<iostream>
#include<vector>
#include<algorithm>
int main() {
	int N;
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	std::cin >> N;
	std::vector<int> hab(N, 0);
	for (int i = 0; i < N; ++i) {
		std::vector<int> sum(i + 1, 0);
		std::vector<int> line(i + 1, 0);
		for (int j = 0; j <= i; ++j) {
			std::cin >> line[j];
		}
		sum[0] = line[0] + hab[0];
		if(i>=1) sum[i] = line[i] + hab[i - 1];
		for (int j = 1; j < i ; ++j) {
			sum[j] = hab[j - 1] + line[j] > hab[j] + line[j] ? hab[j - 1] + line[j] : hab[j] + line[j];
		}
		for (int j = 0; j <= i; ++j) {
			hab[j] = sum[j];
		}
	}

	std::cout << *std::max_element(hab.begin(), hab.end());
	return 0;
}