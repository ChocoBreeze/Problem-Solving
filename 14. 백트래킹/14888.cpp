#include<iostream>
#include<vector>
#include<limits>

int max = std::numeric_limits<int>::min();
int min = std::numeric_limits<int>::max();

void backtracking(std::vector<int>& number, std::vector<int>& operator_, int result, int index) {
	if (operator_[0] == 0 && operator_[1] == 0 && operator_[2] == 0 && operator_[3] == 0) {
		if (min > result) min = result;
		if (max < result) max = result;
		return;
	}
	for (int i = 0; i < operator_.size(); ++i) {
		if (operator_[i] != 0) {
			--operator_[i];
			if (i == 0) backtracking(number, operator_, result + number[index], index + 1);
			else if (i == 1) backtracking(number, operator_, result - number[index], index + 1);
			else if (i == 2) backtracking(number, operator_, result * number[index], index + 1);
			else backtracking(number, operator_, result / number[index], index + 1);
			++operator_[i];
		}
	}
}

int main() {
	int N, temp;
	std::vector<int> number;
	std::vector<int> operator_(4,0);
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> temp;
		number.push_back(temp);
	}
	std::cin >> operator_[0] >> operator_[1] >> operator_[2] >> operator_[3];
	backtracking(number, operator_, number[0], 1);
	std::cout << max << "\n" << min;
	return 0;
}