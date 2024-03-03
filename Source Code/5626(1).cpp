// https://mapocodingpark.blogspot.com/2020/03/BOJ-5626.html
// 파멸적인 메모리 사용을 줄이자..
// 2180KB, 120ms
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
	// vector DP(SIZE, vector<int>(MAXH, 0)); // [column][h]
	vector<int> DPLast(MAXH, 0);
	DPLast[0] = 1; // 0번째 열의 0번 높이는 1개 가능.
	if (!impos) {
		for (int n{1}; n < N; ++n) {
			vector<int> DPCurr(MAXH, 0);
			if (altars[n] == -1) {
				int maxH = min(n, N - 1 - n); // 가능 높이 : 0 ~ min(n, N - 1 - n)
				for (int h{}; h <= maxH; ++h) {
					if (h) {
						DPCurr[h] += DPLast[h - 1];
						DPCurr[h] %= MOD;
					}
					DPCurr[h] += DPLast[h];
					DPCurr[h] %= MOD;
					DPCurr[h] += DPLast[h + 1];
					DPCurr[h] %= MOD;
				}
			}
			else { // altars[n]의 경우에만 갱신
				int h = altars[n]; // 그러고 보니 이게 0인 경우는 없었나 보네?.. 뭐지..
				if (h) {
					DPCurr[h] += DPLast[h - 1];
					DPCurr[h] %= MOD;
				}
				DPCurr[h] += DPLast[h];
				DPCurr[h] %= MOD;
				DPCurr[h] += DPLast[h + 1];
				DPCurr[h] %= MOD;
			}
			DPLast.swap(DPCurr);
		}
		answer = DPLast[0]; // 마지막 열에 위치한 제단 높이도 0만 가능.
	}
	cout << answer << '\n';
	return 0;
}