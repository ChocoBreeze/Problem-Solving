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
		// ���� ���� A���� �ٸ� ���� ���� B�� �� �� �ִ� ������ �Ƿ���, 
		// �� ������ �մ� ������ A�� B�� ������ �ٸ� ���� ������ �����ų� ������ �ʾƾ� �Ѵ�.
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
			if (chk) { // A, B�� �� �� �ִ�.
				cnts[i]++;
				cnts[j]++;
			}
		}
	}
	cout << *max_element(begin(cnts), end(cnts));

	return 0;
}