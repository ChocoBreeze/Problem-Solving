// https://m.blog.naver.com/kks227/220917078260
// https://m.blog.naver.com/PostView.naver?blogId=kks227&logNo=220710595298&referrerCode=0&searchKeyword=%EB%AC%B8%EC%9E%90%EC%97%B4%20%EC%A0%9C%EA%B3%B1
// KMP 공부
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);

	while (1) {
		string str;
		cin >> str;
		if (str == ".") break;
		int N{ static_cast<int>(str.length()) };
		vector<int> fail(N + 1, 0);
		for (int i = 1, j = 0; i < N; ++i) {
			while (j > 0 && str[i] != str[j]) j = fail[j - 1];
			if (str[i] == str[j]) fail[i] = ++j;
		}

		// 특정 문자열을 반복해서 자신이 나와야 함.
		int q = fail[N - 1], r = N - q;
		if (q == 0 || q % r != 0) cout << "1\n";
		else cout << N / r << '\n';
	}
	return 0;
}