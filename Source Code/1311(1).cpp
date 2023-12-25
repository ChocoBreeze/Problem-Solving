// N명의 사람과 N개의 일
// 각 일을 담당하는 사람은 한 명이어야 함..

// MCMF로도 가능하려나 생각??
// https://www.acmicpc.net/problem/14216
// Hungarian algorithm..

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
constinit const int INF = 1'000'000;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}; cin >> N;

	vector<vector<int>> W(N, vector<int>(N, 0));
	for (auto& row : W) {
		for (auto& v : row) {
			cin >> v;
		}
	}

	const int SIZE = 1 << N;
	vector<vector<int>> DP(N, vector<int>(SIZE, INF));
	
	for (int w{}; w < N; ++w) {
		DP[0][(1LL << w)] = W[0][w];
	}

	for (int n = 1; n < N; ++n) { // 사람
		for (int bit{}; bit < SIZE; ++bit) {
			if (DP[n - 1][bit] == INF) continue;
			for (int w{}; w < N; ++w) { // 일
				if (bit & (1 << w)) continue; // 이미 한 일
				DP[n][bit | (1 << w)] = min(DP[n][bit | (1 << w)], DP[n - 1][bit] + W[n][w]);
			}
		}
	}

	cout << DP.back().back() << '\n'; // DP[N-1][SIZE-1]

	return 0;
}