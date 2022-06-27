#include<iostream>
#include<vector>

using namespace std;

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int N, M;
	cin >> N >> M; // 구간이 M으로 나눠떨어지는 개수
	vector<int> A(N, 0);
	vector<long long> accum(N, 0);
	vector<long long> cnt(M, 0); // 나머지가 인덱스인 개수
	for (int i = 0; i < N; ++i) {
		cin >> A[i];
		if (i == 0) accum[i] = A[i];
		else accum[i] = accum[i - 1] + A[i];
		cnt[accum[i] % M]++;
	}
	long long count = 0;
	for (int i = 0; i < M; ++i) {
		if (cnt[i] == 0) continue;
		if (i == 0) count += (cnt[i] * (cnt[i] + 1)) / 2;
		else count += (cnt[i] * (cnt[i] - 1)) / 2;
	}
	cout << count << "\n";
	return 0;
}