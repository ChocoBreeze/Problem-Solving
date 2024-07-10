// https://www.acmicpc.net/board/view/47197
#include <iostream>
#include <vector>
#include <queue> // min_heap

using namespace std;

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	// weight = 1, 의도는 그냥 n-1
	for (int t = 1; t <= T; ++t) {
		int N, M, a, b;
		cin >> N >> M;
		for (int m = 1; m <= M; ++m) {
			cin >> a >> b;
		}
		cout << N - 1 << "\n";
	}
	return 0;
}