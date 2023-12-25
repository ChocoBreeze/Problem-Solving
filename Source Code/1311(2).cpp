// 메모리 줄여지나?
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
	// vector<vector<int>> DP(N, vector<int>(SIZE, INF));
	vector<int> DP(SIZE, INF);
	
	for (int w{}; w < N; ++w) {
		DP[(1LL << w)] = W[0][w];
	}

	for (int n = 1; n < N; ++n) { // 사람
		vector<int> DPtemp(SIZE, INF);
		for (int bit{}; bit < SIZE; ++bit) {
			if (DP[bit] == INF) continue;
			for (int w{}; w < N; ++w) { // 일
				if (bit & (1 << w)) continue; // 이미 한 일
				DPtemp[bit | (1 << w)] = min(DPtemp[bit | (1 << w)], DP[bit] + W[n][w]);
			}
		}
		DP.swap(DPtemp);
	}

	cout << DP.back() << '\n'; // DP[N-1][SIZE-1]

	return 0;
}