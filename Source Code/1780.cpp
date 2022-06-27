#include<iostream>
#include<vector>

int cnt_minus_one, cnt_zero, cnt_one;

void devide_conquer(std::vector<std::vector<int>>& paper, int start_i, int start_j, int length) {
	int one = 0, zero = 0, minus_one = 0;
	for (int i = start_i; i < start_i +length; ++i) { // 정해진 크기에 대해 확인
		for (int j = start_j; j < start_j+length; ++j) {
			if (paper[i][j] == 1) one++;
			else if (paper[i][j] == 0) zero++;
			else if (paper[i][j] == -1) minus_one++;
			if ((minus_one > 0 && zero > 0) || (minus_one > 0 && one > 0) || (zero > 0 && one > 0)) break;
		}
	}
	if ((minus_one > 0 && zero > 0) || (minus_one > 0 && one > 0) || (zero > 0 && one > 0)) { // 9개로 나눠야 함
		int one_third = length / 3;
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				devide_conquer(paper, start_i + one_third * i, start_j + one_third * j, one_third);
			}
		}
	}
	else {
		if (zero > 0) ++cnt_zero;
		else if (one > 0) ++cnt_one;
		else ++cnt_minus_one;
	}
}

int main() {
	int N;
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	std::cin >> N; // N은 3^k, k = 7까지
	std::vector<std::vector<int>> paper(N, std::vector<int>(N, 0)); // N x N
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			std::cin >> paper[i][j];
		}
	}
	devide_conquer(paper, 0, 0, N);
	std::cout << cnt_minus_one << "\n" << cnt_zero << "\n" << cnt_one;
	return 0;
}