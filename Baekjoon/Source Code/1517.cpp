// number of inversions(반전수)
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int SENTINEL = 1000000001;
using llong = long long;

llong merge(vector<int>& A, int start, int mid, int end) {
	int n1 = mid - start, n2 = end - mid;
	llong cnt = 0;
	vector<int> left(n1 + 1, 0), right(n2 + 1, 0);
	for (int i = 0; i < n1; ++i) {
		left[i] = A[start + i];
	}
	for (int i = 0; i < n2; ++i) {
		right[i] = A[mid + i];
	}
	left[n1] = right[n2] = SENTINEL;
	int i = 0, j = 0;
	for (int k = start; k < end; ++k) {
		if (left[i] <= right[j]) {
			A[k] = left[i++];
		}
		else {
			A[k] = right[j++];
			cnt += static_cast<llong>(n1) - i; // # of inversion 누적
		}
	}
	return cnt;
}

llong merge_sort(vector<int>& A, int start, int end) {
	if (start + 1 < end) {
		int mid = start + (end - start) / 2;
		llong c1 = merge_sort(A, start, mid); // [ , )
		llong c2 = merge_sort(A, mid, end); // [ , )
		llong c3 = merge(A, start, mid, end);
		return c1 + c2 + c3;
	}
	else return 0;
}


int main() {
	cin.tie(NULL) -> sync_with_stdio(false);
	int N;
	cin >> N;
	vector<int> A(N, 0);
	for (auto& a : A) {
		cin >> a;
	}
	// 10 1 5 2 3 --> 3
	// 1 5 2 3 10 --> 2
	// 1 2 3 5 10 --> 1
	// 10 1 5 2 3 --> 3
	// max(# of inversion)
	llong answer = merge_sort(A, 0, N);

	cout << answer << '\n';
	
	return 0;
}