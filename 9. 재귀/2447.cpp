#include<iostream>
#include<vector>
#include<string>

void make_star(std::vector<std::string> &star,int N, int n) {
	if (n == 1) return;
	make_star(star, N, n / 3);
	// 공백 만들기
	int start = n / 3;
	for (int i = start; i < N; i += n) {
		for (int j = start; j < N; j+=n) {
			for (int k = 0; k < start; ++k) {
				for (int l = 0; l < start; ++l) {
					star[i + k][j + l] = ' ';
				}
			}
		}
	}
	return;
}
int main() {
	int N;
	std::cin >> N; // 3^1 ~ 3^8
	std::string oneline(N, '*');
	std::vector<std::string> star;
	for (int i = 0; i < N; ++i) {
		star.push_back(oneline);
	}
	make_star(star, N, N);
	for (auto i : star) {
		std::cout << i << std::endl;
	}
	return 0;
}
/*
(1,1)
(1,4)
(1,7)
(1,10)
3*3
행: 1, 4, 7, 10, 13, 16, 19, 22, 25
열: 1, 4, 7, 10, ...

9*9
행: 3~5, 12~14, 21~23
열: 3~5, 12~14, 21~23

27*27
행: 9~17, 36~44
열: 9~17, 36~44
*/