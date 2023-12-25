// KMP
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int gcd(int a, int b) {
	if (b == 0) return a;
	return gcd(b, a % b);
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}; cin >> N;

	string str, target;
	for (int n{}; n < N; ++n) {
		char c{}; cin >> c;
		str.push_back(c);
	}
	str = str + str;
	str.pop_back(); // 0번 시작과 동일함.

	for (int n{}; n < N; ++n) {
		char c{}; cin >> c;
		target.push_back(c); // 찾아야 하는 문자열 만들기
	}

	int strLen = static_cast<int>(str.length());
	int M = static_cast<int>(target.length());

	vector<int> fail(M + 1, 0);
	for (int i{ 1 }, j{}; i < M; ++i) {
		while (j > 0 && target[i] != target[j]) j = fail[j - 1];
		if (target[i] == target[j]) fail[i] = ++j;
	}

	int answer{}; // 일치하는 개수
	for (int i{}, j{}; i < strLen; ++i) {
		// 현재 글자 불일치 => fail을 따라 이동
		while (j > 0 && str[i] != target[j]) j = fail[j - 1];
		if (str[i] == target[j]) { // 현재 글자 일치
			if (j == M - 1) {
				++answer; // 하나 발견
				j = fail[j];
			}
			else ++j;
		}
	}

	int gcdNum = gcd(N, answer);
	cout << answer / gcdNum << '/' << N / gcdNum << '\n';

	return 0;
}