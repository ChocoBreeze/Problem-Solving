#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

const int MAX = 500000;
int N, K, cnt = 0, answer = -1;
int A[MAX], temp[MAX];

void merge(int A[], int p, int q, int r) {

	if (cnt > K) return;
	int i = p, j = q + 1, t = 0;
	while (i <= q && j <= r) {
		if (A[i] <= A[j]) temp[t++] = A[i++];
		else temp[t++] = A[j++];
	}

	while (i <= q) {
		temp[t++] = A[i++];
	}

	while (j <= r) {
		temp[t++] = A[j++];
	}

	t = 0, i = p;
	while (i <= r) { // 이 부분에서 카운팅
		A[i++] = temp[t++];
		cnt++;
		if (cnt == K) answer = temp[t - 1];
		else if (cnt > K) return;
	}
}

void merge_sort(int A[], int p, int r) {
	int q;
	if (cnt > K) return;
	if (p < r) {
		q = p + (r - p) / 2;
		merge_sort(A, p, q); // front ~ mid
		merge_sort(A, q + 1, r); // mid ~ end
		merge(A, p, q, r); // 병합
	}
}

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	cin >> N >> K;

	// vector<int> A(N, 0); 속도 향상을 위해 배열로 교체
	
	for (int i = 0; i < N;++i) {
		cin >> A[i];
	}

	merge_sort(A, 0, N - 1);

	cout << answer;

	return 0;
}