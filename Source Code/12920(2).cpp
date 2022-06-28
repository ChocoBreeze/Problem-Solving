// https://www.acmicpc.net/board/view/32373
// 개수 없애는 과정 - 이진수로 개수 분해 - 허허..
// 13 = 1 + 2 + 4 + 6
// 무작정 나누면 일반적인 DP에서 중복될 수 있음.
#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::min;
using std::max;

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int N, M, V, C, K;
	cin >> N >> M; // N = 물건 수, M = 최대 무게
	vector<int> w, s; // 물건, 만족도
	for (int i = 0; i < N; ++i) {
		cin >> V >> C >> K; // 무게, 만족도, 물건 수
		for (int c = 1; K > 0; c <<= 1) { // 핵심
			int m = min(c, K);
			w.push_back(m * V);
			s.push_back(m * C);
			K -= m;
		}
	}
	vector<int> DP(M + 1, 0);
	for (int i = 1; i <= size(w); ++i) {
		vector<int> DP_(M + 1, 0);
		for (int j = 0; j <= M; ++j) {
			DP_[j] = DP[j];
			if (j >= w[i-1]) {
				DP_[j] = max(DP_[j], DP[j - w[i - 1]] + s[i - 1]); // 선택
			}
		}
		DP = std::move(DP_);
	}
	cout << DP[M];
	return 0;
}