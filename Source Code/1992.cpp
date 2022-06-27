#include<iostream>
#include<vector>
#include<string>

std::string answer;

void devide_conquer(std::vector<std::vector<int>>& paper, int start_i, int start_j, int length) {
	int one = 0, zero = 0;
	for (int i = start_i; i < start_i +length; ++i) { // 정해진 크기에 대해 확인
		for (int j = start_j; j < start_j+length; ++j) {
			if (paper[i][j] == 1) one++;
			else if(paper[i][j]==0) zero++;
			if (one > 1 && zero > 1) break;
		}
	}
	if (zero > 0 && one > 0) { // 반으로 나눠야 함
		int half = length / 2;
		answer.push_back(('('));
		devide_conquer(paper, start_i, start_j, half);					//left-top
		devide_conquer(paper, start_i, start_j + half, half);			//right-top
		devide_conquer(paper, start_i + half, start_j, half);			//left-bottom
		devide_conquer(paper, start_i + half, start_j + half, half);	//right-bottom
		answer.push_back((')'));
	}
	else {
		if (zero > 0) answer.push_back('0');
		else answer.push_back('1');
	}
}

int main() {
	int N;
	std::string temp;
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	std::cin >> N; // 2, 4, 8, 16, 32, 64, 128
	std::vector<std::vector<int>> paper(N, std::vector<int>(N, 0)); // N x N
	for (int i = 0; i < N; ++i) {
		std::cin >> temp; // 한 줄 입력
		for (int j = 0; j < N; ++j) {
			paper[i][j] = temp[j] - '0';
		}
	}
	devide_conquer(paper, 0, 0, N);
	std::cout << answer;
	return 0;
}