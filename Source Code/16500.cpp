#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	string S; cin >> S;
	int sLen = static_cast<int>(S.length());
	int N{}; cin >> N;
	vector<string> A(N, "");
	for (string& a : A) cin >> a;

	vector<int> possible(sLen, 0);
	// possible[i] : i번째 index까지 A에 속한 문자열로 가능한지

	for (int l{}; l < sLen; ++l) {
		for (int n{}; n < N; ++n) {
			if (l + 1 < A[n].length()) continue;

			bool isSame{true};
			int aLen = static_cast<int>(A[n].length());
			for (int i{}; i < aLen; ++i) {
				if (S[l - aLen + i + 1] != A[n][i]) {
					isSame = false;
					break;
				}
			}
			if (isSame) {
				if (possible[l]) continue;
				if (l - aLen < 0) possible[l] = 1;
				else possible[l] = possible[l - aLen];
			}
		}
	}

	cout << possible.back() << '\n';
	return 0;
}
