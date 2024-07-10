#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}; cin >> N;
	vector<double> hs(N, 0);
	for (double& h : hs) cin >> h;
	vector<int> cnts(N, 0);
	for (int i{}; i < N; ++i) { // A
		// 고층 빌딩 A에서 다른 고층 빌딩 B가 볼 수 있는 빌딩이 되려면, 
		// 두 지붕을 잇는 선분이 A와 B를 제외한 다른 고층 빌딩을 지나거나 접하지 않아야 한다.
		for (int j{i+1}; j < N; ++j) { // B

			bool chk{ true };
			double slope = (hs[j] - hs[i]) / (j - i);
			for (int k = i + 1; k < j; ++k) {
				double nowH = hs[i] + slope * (k - i);
				if (nowH <= hs[k]) {
					chk = false;
					break;
				}
			}
			if (chk) { // A, B는 볼 수 있다.
				cnts[i]++;
				cnts[j]++;
			}
		}
	}
	cout << *max_element(begin(cnts), end(cnts));

	return 0;
}