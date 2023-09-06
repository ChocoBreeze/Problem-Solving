// KMP 공부
// https://m.blog.naver.com/kks227/220917078260
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	string T, P;
	getline(cin, T);
	getline(cin, P);

	int N{ static_cast<int>(T.length()) }, M{ static_cast<int>(P.length()) };
	vector<int> fail(M + 1, 0);
	for (int i = 1, j = 0; i < M; ++i) {
		while (j > 0 && P[i] != P[j]) j = fail[j - 1];
		if (P[i] == P[j]) fail[i] = ++j;
	}

	vector<int> result; // T, P의 일치하는 지점을 result에 모으기.
	for (int i{}, j{}; i < N; ++i) {
		// 현재 글자가 불일치하면 fail 값을 계속 따라 감.
		while (j > 0 && T[i] != P[j]) j = fail[j - 1];
		if (T[i] == P[j]) { // 현재 글자가 일치
			if (j == M - 1) { // 일치하는 하나 발견!
				// i = 0부터 시작한다면 i - M + 1. 문제 조건에 따라 1을 더함.
				result.push_back(i - M + 2);
				// 찾지 못한 것처럼 j를 이동해서 재탐색
				j = fail[j];
			}
			else ++j;
		}
	}

	// 결과 출력
	cout << result.size() << '\n';
	for (int& r : result) cout << r << ' ';
	cout << '\n';

	return 0;
}