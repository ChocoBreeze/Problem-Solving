#include <iostream>
#include <vector>
#include <string>

using namespace std; 
const int INF = 1000000000;

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int N, P;
	cin >> N;
	vector<vector<int>> cost(N, vector<int>(N, 0));
	const int SIZE = 1 << (N + 1);
	// vector<vector<int>> DP(SIZE, vector<int>(N,INF));
	vector<int> DP(SIZE, INF);
	for (auto& i : cost) {
		for (auto& j : i) {
			cin >> j;
		}
	}
	string str;
	cin >> str;
	cin >> P;
	int bit = 0, first_count = 0;
	for (int s = 0; s < str.length();++s) {
		if (str[s] == 'Y') {
			bit += (1 << s);
			++first_count;
		}
	}
	if (first_count >= P) {
		cout << 0;
		return 0;
	}
	// cout << bit;
	// DP[bit].clear();
	// DP[bit].assign(N, 0);
	DP[bit] = 0;
	// bitfield dp
	int answer = INF;
	for (int i = bit; i < SIZE; ++i) { // 가능한 bit
		for (int j = 0; j < N; ++j) {	
			if (!(i & (1 << j))) continue; // 꺼진 발전소
			for (int k = 0; k < N; ++k) {
				if (i & (1 << k)) continue; // 이미 방문
				int n_bit = i | (1 << k);
				int temp_n_bit = n_bit, count_one = 0;
				while (temp_n_bit) {
					if (temp_n_bit & 1) ++count_one;
					temp_n_bit >>= 1;
				}
				DP[n_bit] = min(DP[n_bit], DP[i] + cost[j][k]);
				if (count_one >= P) answer = min(answer, DP[n_bit]);
			}
		}
	}
	if (answer == INF) cout << -1; // 불가능한 경우
	else cout << answer;

	return 0;
}