// N���� ����� N���� ��
// �� ���� ����ϴ� ����� �� ���̾�� ��..

// MCMF�ε� �����Ϸ��� ����??
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

	for (int n = 1; n < N; ++n) { // ���
		for (int bit{}; bit < SIZE; ++bit) {
			if (DP[n - 1][bit] == INF) continue;
			for (int w{}; w < N; ++w) { // ��
				if (bit & (1 << w)) continue; // �̹� �� ��
				DP[n][bit | (1 << w)] = min(DP[n][bit | (1 << w)], DP[n - 1][bit] + W[n][w]);
			}
		}
	}

	cout << DP.back().back() << '\n'; // DP[N-1][SIZE-1]

	return 0;
}