// Rabin-Karp
// https://m.blog.naver.com/kks227/220927272165

/*
해싱을 하기 위해 대상 문자열의 길이를 정하기..?
- 만약 길이가 K+1인 문자열이 두 번 등장한다면, 당연히 길이 K인 문자열도 두 번 등장함.
- 따라사 답이 K라면, K 이하의 모든 길이에 대해 두 번 등장하는 부분 문자열이 존재하며, K보다 큰 길이에 대해서는 없음.
=> 이분 탐색을 통해 K를 찾을 수 있음! (대박..)
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 이번 문제를 풀려면 MOD가 어느 정도로 작아야 합니다.
// 이거는 왜지.. (너무 크면 저장할 수 없어서 그런 듯함).
constinit const int MOD = 100'003;

inline int Mod(long long n) {
	if (n >= 0) return n % MOD;
	return ((-n / MOD + 1) * MOD + n) % MOD;
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int len{};
	string str;
	cin >> len >> str;

	// 답 길이인 K를 찾기 위한 이분 탐색
	int lo{}, hi{ len }; // 두 번 이상 등장하는 문자열을 찾기 때문에 len은 답이 될 수 없음.
	while (lo + 1 < hi) {
		int mid = lo + (hi - lo) / 2;

		int H{}, power = 1;
		vector<vector<int>> pos(MOD, vector<int>()); // pos[i]: 해시값이 i인 부분 문자열의 등장 위치들
		bool found{};

		// 가능한 모든 위치에서 길이 mid인 부분 문자열들의 해시값을 구해 보며 처리.
		for (int i{}; i <= len - mid; ++i) {
			if (i == 0) {
				// 첫 해시 구하기
				for (int j{}; j < mid; ++j) {
					// ABC -> A*2^2 + B*2^1 + C*2^0
					H = Mod(H + 1LL * str[mid - 1 - j] * power);
					if (j < mid - 1) power = Mod(((1LL * power) << 1));
				}
			}
			else {
				H = Mod(((H - 1LL * str[i - 1] * power) << 1) + str[i + mid - 1]);
			}

			// 해시 Collision => 같은 문자인지 진짜 확인
			if (!pos[H].empty()) {
				for (int& start : pos[H]) { // 해시값이 H인 문자열의 시작점들
					bool same{true};
					for (int j{}; j < mid; ++j) {
						if (str[i + j] != str[start + j]) {
							same = false;
							break;
						}
					}
					if (same) {
						found = true;
						break;
					}
				}
			}
			if (found) break; // 하나라도 있으면 더 볼 필요 없이 break
			else pos[H].push_back(i); // 현재 위치 i push_back
		}

		// 길이 mid인 부분 문자열이 두 번 이상 등장했느냐에 따라 상하값 조절
		if (found) lo = mid; // 등장
		else hi = mid; // 등장 X
	}
	cout << lo << '\n';
	return 0;
}