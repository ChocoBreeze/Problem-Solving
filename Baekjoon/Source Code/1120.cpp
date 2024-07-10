/*
양쪽 번갈아 가면서 붙일 수 있음.
기존 구현은 한쪽에 다 붙이는 경우만 고려함.
*/
#include<iostream>
#include<string>
#include<algorithm>

using std::string;
using std::cin;
using std::cout;
using std::min;

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	string A, B;
	cin >> A >> B;
	int answer = 51;
	for (int i = 0; i < B.length() - A.length() + 1; ++i) {
		int cnt = 0;
		for (int j = 0; j < A.length(); ++j) {
			if (A[j] != B[i + j]) ++cnt;
		}
		answer = min(answer, cnt);
	}
	cout << answer;
	return 0;
}