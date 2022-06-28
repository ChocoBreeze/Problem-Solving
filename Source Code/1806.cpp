#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>

using std::distance;
using std::cin;
using std::cout;
using std::vector;
using std::min;

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int N, S;
	cin >> N >> S;
	vector<int> L(N, 0);
	for (int i = 0; i < N; ++i) {
		cin >> L[i];
	}
	auto front = begin(L), back = begin(L);
	int sum = L[0], answer = INT_MAX; // 초기값을 잘 주자!
	while (back!=L.end()) {
		if (sum < S) {
			if (front == L.end() - 1) break;
			++front;
			sum += *front;
		}
		else { // S이상인 것을 구하는 문제.. S가 아니고..
			answer = min(answer, (int)distance(back, front));
			sum -= *back;
			++back;
		}
	}
	if (answer!=INT_MAX) cout << answer + 1;
	else cout << 0;
	return 0;
}