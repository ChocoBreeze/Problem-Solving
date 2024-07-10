// https://excited-hyun.tistory.com/145 참고.
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
constinit const int SIZE = 26;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}; cin >> N;
	
	vector<int> charSum(26); // 각 문자별 숫자합.
	// ABC -> A : 100, B : 10, C : 1

	for (int n{}; n < N; ++n) {
		string str; cin >> str;
		int place = 1;
		for (auto it = rbegin(str); it != rend(str);++it) {
			charSum[*it - 'A'] += place;
			place *= 10;
		}
	}

	// 구한 합으로 다시 문자열에 재배치해줄 필요 없음!!
	sort(begin(charSum), end(charSum), greater<int>());

	int answer{};
	for (int i{}; i < 10;++i) { // 합이 큰 순서대로 9, 8, 7, 6, ...
		answer += charSum[i] * (9 - i);
	}
	cout << answer << '\n';

	return 0;
}