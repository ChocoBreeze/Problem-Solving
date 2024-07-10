#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAX = 101;
int N, K, a[MAX], d[MAX][100001];
int dp(int cur, int n) {
	if (cur == N - 1) return n == K ? 1 : N+1;
	if (d[cur][n] != -1) return d[cur][n];
	d[cur][n] = N+1;
	d[cur][n] = min(d[cur][n], dp(cur + 1, n));
	for (int i = cur + 1; i < N; i++) {
		if (n + a[i] <= K)
			d[cur][n] = min(d[cur][n], dp(i, n + a[i]) + 1);
	}
	return d[cur][n];
}
int main() {
	cin >> N >> K;
	if (!K) {
		cout << 0 << "\n";
		return 0;
	}
	for (int i = 0; i < N; i++) {
		cin >> a[i];
	}
	memset(d, -1, sizeof(d));
	int ans = N+1;
	for (int i = 0; i < N; i++) {
		ans = min(ans, dp(i, a[i]));
	}
	if (ans >= N+1)
		cout << -1 << "\n";
	else
		cout << ans << "\n";
}