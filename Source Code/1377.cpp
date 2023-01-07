// number of inversions.
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

const int SENTINEL = 1000001;
int answer = 0;
using llong = long long;
using pii = pair<int, int>;

void merge(vector<pii>& A, int start, int mid, int end) {
	int n1 = mid - start, n2 = end - mid;
	llong cnt = 0;
	vector<pii> left(n1 + 1, make_pair(0,0)), right(n2 + 1, make_pair(0, 0));
	for (int i = 0; i < n1; ++i) {
		left[i] = A[start + i];
	}
	for (int i = 0; i < n2; ++i) {
		right[i] = A[mid + i];
	}
	left[n1].first = right[n2].first = SENTINEL;
	int i = 0, j = 0;
	for (int k = start; k < end; ++k) {
		if (left[i].first <= right[j].first) {
			A[k] = left[i++];
		}
		else {
			right[j].second += (n1 - i);
			A[k] = right[j++];
			answer = max(answer, A[k].second);
		}
	}
}

void merge_sort(vector<pii>& A, int start, int end) {	
	if (start + 1 < end) {
		int mid = start + (end - start) / 2;
		merge_sort(A, start, mid); // [ , )
		merge_sort(A, mid, end); // [ , )
		merge(A, start, mid, end);
	}
}


int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	int N;
	cin >> N;
	vector<pii> A(N, make_pair(0,0));
	for (auto& a : A) {
		cin >> a.first;
	}

	merge_sort(A, 0, N);

	cout << answer + 1 << '\n';

	return 0;
}