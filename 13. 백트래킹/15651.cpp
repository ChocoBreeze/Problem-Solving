#include<iostream>
#include<vector>

void backtracking(int& N, int count, std::vector<bool>& list,  std::vector<int>& answer) {
	if (count == 0) {
		for (auto i = answer.begin(); i != answer.end(); ++i) {
			std::cout << *i << " ";
		}
		std::cout << "\n";
		return;
	}
	else {
		for (int i = 0; i < N; ++i) {
			list[i] = true;
			answer.push_back(i + 1);
			backtracking(N, count - 1, list, answer);
			list[i] = false;
			answer.pop_back();
		}
	}
}
int main() {
	int N, M;
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	std::cin >> N >> M;
	std::vector<bool> list(N, false);
	std::vector<int> answer;
	backtracking(N, M, list, answer);
	return 0;
}