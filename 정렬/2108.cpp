#include<vector>
#include<iostream>
#include<algorithm>

int main() {
	int N, temp, sum = 0, max = -1, max_frequency = -1;
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	std::cin >> N;
	std::vector<int> list;
	std::vector<int> list_count(8001, 0);
	for (int i = 0; i < N; ++i) {
		std::cin >> temp;
		sum += temp;
		list.push_back(temp);
		++list_count[temp+4000];
		if (max < list_count[temp+4000]) {
			max = list_count[temp+4000]; max_frequency = temp;
		}
	}
	std::sort(list.begin(), list.end());
	temp = 0;
	for (int i = 0; i < 8001; ++i) {
		if (list_count[i] == max && temp == 0) temp = 1;
		else if (list_count[i] == max && temp == 1) {
			max_frequency = i - 4000;
			break;
		}
	}

	std::cout << std::fixed;
	std::cout.precision(0);
	if (static_cast<double>(sum) / N < 0 && static_cast<double>(sum) / N > -0.5) std::cout << "0" << "\n";
	else std::cout << static_cast<double>(sum) / N << "\n";
	std::cout << list[N / 2] << "\n";
	std::cout << max_frequency << "\n";
	std::cout << list[N - 1] - list[0] << "\n";

	return 0;
}