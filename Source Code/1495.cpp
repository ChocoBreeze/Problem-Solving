#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	int N, S, M;
	cin >> N >> S >> M;
	vector<int> V(N, 0);
	for (auto& v : V) {
		cin >> v;
	}
	vector<int> DP(M + 1, 0);
	DP[S] = 1;
	int answer = -1;
	for (int i = 0; i < N; ++i) {
		int count = 0;
		vector<int> DP_tmp(M + 1, 0);
		for (int j = 0; j <= M; ++j) {
			if (DP[j] == 0) continue;
			if (0<=j + V[i] && j+ V[i] <=M) {
				DP_tmp[j + V[i]] = 1;
				if (i == N - 1) answer = max(answer, j + V[i]);
				++count;
			}
			if (0 <= j - V[i] && j - V[i] <= M) {
				DP_tmp[j - V[i]] = 1;
				if (i == N - 1) answer = max(answer, j - V[i]);
				++count;
			}
		}
		DP = move(DP_tmp);
		if (count == 0) break; // 끝까지 도달 불가능
	}
	cout << answer;
}