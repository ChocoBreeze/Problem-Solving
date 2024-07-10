// 정밀도 때문에 애먹음
// N개의 a와 M개의 z
// 알파벳 순
// K번째 문자열 찾기
// 조합
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath> // 반올림

using namespace std;

double count(int N, int M, int K) {
	double cnt = 1;
	int large = max(N, M);
	int small = min(N, M);
	for (int i = large + 1; i <= N + M; ++i) { // a 넣을 경우 개수
		cnt *= i;
		if (small > 1) {
			cnt /= small;
			--small;
		}
		if (cnt > K) break;
	}
	return cnt;
}

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int N, M, K;
	cin >> N >> M >> K;
	// 없으면 -1
	// K는 최대 10억. - 다 구해서 찾으면 늦을 듯.
	// 처음에 되는지 확인
	double cnt;
	cnt = count(N, M, K);
	//cout << cnt;
	if (cnt < K) {
		cout << -1;
	}
	else {
		string answer;
		while (M>0 || N>0) {
			if (K == 1) {
				while (N > 0) {
					answer += "a";
					--N;
				}
				while (M > 0) {
					answer += "z";
					--M;
				}
				break;
			}
			// a를 넣었을 때의 개수
			cnt = count(N - 1, M, K);
			if (cnt >= K) {
				answer += "a";
				--N;
			}
			else {
				answer += "z";
				K -= round(cnt); // 정밀도?
				--M;
			}
		}
		cout << answer;
	}
	return 0;
}