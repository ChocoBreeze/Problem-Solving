// 시간 초과
#include<iostream>
#include<vector>

int min = 2001;

void backtracking(std::vector<std::vector<int>>& number, std::vector<int>& chk_list, std::vector<int>& team_start, std::vector<int>& team_link,int index) {
	if (team_start.size() == number.size() / 2) {
		for (int i = 0; i < chk_list.size(); ++i) {
			if (chk_list[i] == 0) team_link.push_back(i);
		}
		int sum_start = 0, sum_link = 0;
		for (int i = 0; i < team_start.size(); ++i) {
			for (int j = 0; j < team_start.size(); ++j) {
				if (i == j) continue;
				sum_start += number[team_start[i]][team_start[j]];
				sum_link += number[team_link[i]][team_link[j]];
			}
		}
		if (min > abs(sum_start - sum_link)) min = abs(sum_start - sum_link);
		team_link.clear();
		return;
	}
	for (int i = index; i < chk_list.size(); ++i) {
		if (chk_list[i] == 0) {
			chk_list[i] = 1;
			team_start.push_back(i);
			backtracking(number, chk_list, team_start, team_link, i + 1);
			chk_list[i] = 0;
			team_start.pop_back();
		}
	}
}

int main() {
	int N;
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	std::cin >> N;
	std::vector<std::vector<int>> number(N,std::vector<int>(N,0));
	std::vector<int> chk_list(N, 0);
	std::vector<int> team_start;
	std::vector<int> team_link;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			std::cin >> number[i][j];
		}
	}
	backtracking(number, chk_list, team_start, team_link, 0);
	std::cout << min;
	return 0;
}