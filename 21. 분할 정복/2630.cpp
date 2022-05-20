#include<iostream>
#include<vector>

int W = 0, B = 0; // White, Blue

void devide_conquer(std::vector<std::vector<int>>& paper, int start_i, int start_j, int length) {
	int W_ = 0, B_ = 0;
	for (int i = start_i; i < start_i +length; ++i) { // 정해진 크기에 대해 확인
		for (int j = start_j; j < start_j+length; ++j) {
			if (paper[i][j] == 1) B_++;
			else if(paper[i][j]==0) W_++;
			if (B_ > 1 && W_ > 1) break;
		}
	}
	if (B_ > 0 && W_ > 0) { // 반으로 나눠야 함
		int half = length / 2;
		devide_conquer(paper, start_i, start_j, half);
		devide_conquer(paper, start_i, start_j + half, half);
		devide_conquer(paper, start_i + half, start_j, half);
		devide_conquer(paper, start_i + half, start_j + half, half);
	}
	else { // 하나의 종이
		if (B_ > 0) ++B;
		else ++W;
	}
}

int main() {
	int N;
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	std::cin >> N; // 2, 4, 8, 16, 32, 64, 128
	std::vector<std::vector<int>> paper(N, std::vector<int>(N, 0)); // N x N
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			std::cin >> paper[i][j];
		}
	}
	devide_conquer(paper, 0, 0, N);
	std::cout << W << "\n" << B;
	return 0;
}