// https://gyong0117.tistory.com/entry/BOJ%EB%B0%B1%EC%A4%80-5525C-IOIOI
// 신기하군..
// 3680KB, 12ms
#include <iostream>
#include <string>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}, M{}; cin >> N >> M;
	string S; cin >> S;

	int answer{};
	for (int m{}; m < M; ++m) {
		int k{}; // IOI의 개수
		if (S[m] == 'O') continue;

		while (m + 2 < static_cast<int>(S.length()) && S[m + 1] == 'O' && S[m + 2] == 'I') {
			++k;
			if (k == N) {
				++answer;
				--k; // 찾았으니 하나 깎기
			}
			m += 2;
		}
	}
	cout << answer << '\n';
	return 0;
}