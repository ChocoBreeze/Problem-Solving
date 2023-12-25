// KMP 공부
// 아무생각 없이 넣었다가 100'000 * 10'000 만듦.
// 메모리 줄이기 위해 bitset 사용
#include <iostream>
#include <vector>
#include <string>
#include <bitset>

using namespace std;
constinit const int SIZE = 100'000;
constinit const int MAXN = 500;
bitset<SIZE> result[MAXN];

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	string str;	cin >> str;
	int strLen = static_cast<int>(str.length());
	int N{}; cin >> N;

	// vector<vector<int>> result(strLen);
	vector<int> strsLen(N); // 길이 정보만 필요함.

	for (int n{}; n < N; ++n) {
		string s;
		cin >> s;
		int len = static_cast<int>(s.length());
		strsLen[n] = len;

		int M{ static_cast<int>(s.length()) };
		vector<int> fail(M + 1, 0);
		for (int i = 1, j = 0; i < M; ++i) {
			while (j > 0 && s[i] != s[j]) j = fail[j - 1];
			if (s[i] == s[j]) fail[i] = ++j;
		}

		for (int i{}, j{}; i < strLen; ++i) {
			while (j > 0 && str[i] != s[j]) j = fail[j - 1];
			if (str[i] == s[j]) {
				if (j == M - 1) {
					// result[i].push_back(n); // 끝나는 index
					result[n][i] = 1;
					j = fail[j];
				}
				else ++j;
			}
		}
	}
	
	// O(NL)
	vector<int> DP(strLen, 0);
	for (int i{ 0 }; i < strLen; ++i) {
		for (int n{}; n < N; ++n) {
			if (result[n][i]) {
				int& nowLen = strsLen[n];
				if (i - nowLen < 0) DP[i] = max(DP[i], nowLen);
				else DP[i] = max(DP[i], DP[i - nowLen] + nowLen);
			}
		}
		if(i) DP[i] = max(DP[i], DP[i - 1]);
	}
	cout << DP.back() << '\n';
	return 0;
}