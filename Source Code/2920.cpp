#include<iostream>
#include<vector>

using namespace std;
int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	vector<int> A(8, 0);
	for (auto &i : A) {
		cin >> i;
	}
	int as_sum = 0, des_sum = 0;
	for (int i = 0; i < 8; ++i) {
		if (A[i] == i + 1) as_sum++;
		else if (A[i] == 8 - i) des_sum++;
	}
	if (as_sum == 8) cout << "ascending";
	else if (des_sum == 8) cout << "descending";
	else cout << "mixed";
	return 0;
}