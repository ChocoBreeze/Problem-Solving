#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	vector<int> A(n, 0);
	vector<int> A_(n, 0);
	vector<int> B(n, -1001);
	for (int i = 0; i < size(A);++i) {
		cin >> A[i];
		B[i] = A_[i] = A[i];
	}
	int answer = A[0];
	bool chk = false;
	for (int i = 1; i < n; ++i) { 
		if (A_[i-1] + A[i] > 0 && A_[i-1] > 0) {
			A_[i] += A_[i - 1]; // 누적
		}
		if (B[i - 1] + A[i] < A_[i - 1]) {
			B[i] = A_[i - 1];
		}
		else {
			B[i] += B[i - 1];
		}
		
		answer = max(answer, A_[i]);
		answer = max(answer, B[i]);
	}
	cout << answer;
	return 0;
}