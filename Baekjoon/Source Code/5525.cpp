// KMP
// 9000KB, 20ms
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}, M{}; cin >> N >> M;
	string S; cin >> S;

	// P_N 만들기
	string PN;
	for (int n{}; n < N; ++n) {
		PN.push_back('I');
		PN.push_back('O');
	}
	PN.push_back('I');

	
	// fail function
	const int SIZE = static_cast<int>(PN.length());
	vector<int> fail(SIZE, 0);
	for (int i = 1, j = 0; i < SIZE; ++i) {
		while (j > 0 && PN[i] != PN[j]) j = fail[j - 1];
		if (PN[i] == PN[j]) fail[i] = ++j;
	}

	// S(len = M)에서 PN 찾기.
	int answer{};
	for (int i{}, j{}; i < M; ++i) {
		// 현재 글자가 불일치하면 fail 값을 계속 따라 감.
		while (j > 0 && S[i] != PN[j]) j = fail[j - 1];
		if (S[i] == PN[j]) { 
			if (j == SIZE - 1) { // 일치하는 하나 발견!
				++answer;
				// 찾지 못한 것처럼 j를 이동해서 재탐색
				j = fail[j];
			}
			else ++j;
		}
	}
	cout << answer << '\n';
	return 0;
}