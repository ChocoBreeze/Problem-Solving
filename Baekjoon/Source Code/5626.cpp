// https://mapocodingpark.blogspot.com/2020/03/BOJ-5626.html
// 197808KB, 272ms - 파멸적인 메모리 사용..
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
constinit const int MAXH = 5001;
constinit const int SIZE = 10001;
constinit const int MOD = 1'000'000'007;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}; cin >> N;
	int answer{}, impos{};

	vector<int> altars(N, 0);
	for (int n{}; n < N; ++n) {
		int& al = altars[n]; cin >> al;
		if (al > min(n, N - 1 - n)) { // 제단 성립 불가능.
			impos = 1;
			break;
		}
	}

	// DP[10000][5000] : 191MB 쯤.
	// DP[10000][10000] : 382MB 쯤.
	vector DP(SIZE, vector<int>(MAXH, 0)); // [column][h]
	DP[0][0] = 1; // 0번째 열의 0번 높이는 1개 가능.
	if (!impos) {
		for (int n{1}; n < N; ++n) {
			if (altars[n] == -1) {
				int maxH = min(n, N - 1 - n); // 가능 높이 : 0 ~ min(n, N - 1 - n)
				for (int h{}; h <= maxH; ++h) {
					if (h) {
						DP[n][h] += DP[n - 1][h - 1];
						DP[n][h] %= MOD;
					}
					DP[n][h] += DP[n - 1][h];
					DP[n][h] %= MOD;
					DP[n][h] += DP[n - 1][h + 1];
					DP[n][h] %= MOD;
				}
			}
			else { // altars[n]의 경우에만 갱신
				int h = altars[n];
				DP[n][h] += DP[n - 1][h - 1];
				DP[n][h] %= MOD;
				DP[n][h] += DP[n - 1][h];
				DP[n][h] %= MOD;
				DP[n][h] += DP[n - 1][h + 1];
				DP[n][h] %= MOD;
			}
		}
		answer = DP[N - 1][0]; // 마지막 열에 위치한 제단 높이도 0만 가능.
	}
	cout << answer << '\n';
	return 0;
}