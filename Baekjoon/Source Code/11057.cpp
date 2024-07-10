#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	vector<int> A = { 1,1,1,1,1,1,1,1,1,1 };
	int N;
	cin >> N;
	for (int i = 1; i < N; ++i) {
		vector<int> A_(10, 0);
		for (int j = 0; j < 10; ++j) {
			for (int k = j; k < 10; ++k) {
				A_[k] += A[j];
				A_[k] %= 10007;
			}
		}
		A = move(A_);
	}
	int sum = 0;
	for (auto& i : A) {
		sum += i;
		sum %= 10007;
	}
	cout << sum;
	return 0;
}