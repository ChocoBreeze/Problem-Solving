#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Planet{
	int size;
	int index;
	Planet(int s, int i) : size(s), index(i) {}
};

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	int N, M;
	cin >> M >> N; // 우주, 행성
	vector<vector<Planet>> A(M, vector<Planet>(N, Planet(0, 0)));
	for (int m = 0; m < M; ++m) {
		for (int n = 0; n < N; ++n) {
			cin >> A[m][n].size;
			A[m][n].index = n;
		}
	}
	auto compare = [](const Planet& a, const Planet& b) {
		return a.size < b.size; // ascend
	};
	for (int m = 0; m < M; ++m) {
		stable_sort(begin(A[m]), end(A[m]),compare);
	}
	int answer = 0;
	for (int m1 = 0; m1 < M; ++m1) {
		for (int m2 = m1 + 1; m2 < M; ++m2) {
			bool is_same = true;
			for (int n = 0; n < N - 1; ++n) {
				if (A[m1][n].index != A[m2][n].index) {
					is_same = false;
					break;
				}
				else {
					int m1_diff = A[m1][n + 1].size - A[m1][n].size;
					int m2_diff = A[m2][n + 1].size - A[m2][n].size;
					if (!((m1_diff > 0 && m2_diff > 0) || (m1_diff < 0 && m2_diff < 0) || (m1_diff==0 && m2_diff==0))) {
						is_same = false;
						break;
					}
				}
			}
			if (is_same) ++answer;
		}
	}
	cout << answer;
	return 0;
}