// https://m.blog.naver.com/kks227/221386454504
// Kadane's algorithm
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
constinit const int INF = 1 << 30;
// O(TN)

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int T{}; cin >> T;
	while (T--) {
		int N{}; cin >> N;
		vector<int> X(N, 0);
		for (int& x : X) cin >> x;
		int psum1{}, psum2{}, answer{ -INF };
		for (int& x : X) {
			psum1 += x;
			answer = max(answer, psum1 - psum2);
			psum2 = min(psum2, psum1);
		}
		cout << answer << '\n';
	}
	return 0;
}