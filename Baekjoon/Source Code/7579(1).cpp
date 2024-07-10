// d[i][j] : i까지만 쓰고 비용은 j까지 썼을 때의 최대 앱 가능 확보량
// 6092KB, 4ms
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}, M{}; cin >> N >> M;
	const int SIZE = N + 1;
	vector<int> m(SIZE, 0), c(SIZE, 0);
	int sum{};
	for (int i = 1; i <= N; ++i) cin >> m[i];
	for (int i = 1; i <= N; ++i) {
		cin >> c[i];
		sum += c[i];
	}
	int answer{ 10001 };
	vector d(SIZE, vector<int>(sum + 1, 0));
	for (int i = 1; i <= N; ++i) { // 물건
		for (int j{}; j <= sum; ++j) { // 무게
			d[i][j] = d[i - 1][j];
			if (c[i] <= j) {
				d[i][j] = max(d[i][j], d[i - 1][j - c[i]] + m[i]);
				if (d[i][j] >= M) answer = min(answer, j);
			}
		}
	}
	cout << answer << '\n';
	return 0;
}