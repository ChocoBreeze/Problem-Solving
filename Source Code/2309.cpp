#include<iostream>
#include<algorithm>
#include<vector>

using std::cin;
using std::cout;
using std::vector;
using std::sort;

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	vector<int> A(9, 0);
	int sum = 0, chk = 0;
	for (int i = 0; i < 9; ++i) {
		cin >> A[i];
		sum += A[i];
	}
	sort(A.begin(), A.end());
	for (int i = 0; i < 9; ++i) {
		for (int j = i + 1; j < 9; j++) {
			// 뺄 2명 - i, j
			int sum_temp = 0;
			for (int k = 0; k < 9; ++k) {
				if (k == i || k == j) continue;
				sum_temp += A[k];
			}
			if (sum_temp == 100) {
                chk=1;
				for (int k = 0; k < 9; ++k) {
					if (k == i || k == j) continue;
					cout << A[k] << "\n";
				}
			}
			if (chk == 1) break;
		}
		if (chk == 1) break;
	}
	return 0;
}