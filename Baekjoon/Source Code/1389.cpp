// floyd-warshall
// 2152KB, 0ms
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
constinit const int INF = 200;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}, M{}; cin >> N >> M; // 유저의 수, 친구 관계의 수
	vector Am(N + 1, vector<int>(N + 1, INF)); // Adjacency matrix
	for (int n{1}; n <= N; ++n) { // 밑에는 1번인덱스 시작해놓고 위에는 범위를 이상하게 줬네..
		Am[n][n] = 0;
	}
	for (int m{}; m < M; ++m) {
		int a{}, b{}; cin >> a >> b; // a와 b는 친구이다.(a와 b가 같은 경우는 없다)
		Am[a][b] = 1;
		Am[b][a] = 1;
	}
	for (int k = 1; k <= N; ++k) {
		for (int i = 1; i <= N; ++i) {
			for (int j = 1; j <= N; ++j) {
				Am[i][j] = min(Am[i][j], Am[i][k] + Am[k][j]);
			}
		}
	}

	int answer{}, minSum{ 1 << 30 }; // minSum 크기 설정
	for (int i = 1; i <= N; ++i) {
		int sum{};
		for (int j = 1; j <= N; ++j) {
			sum += Am[i][j];
		}
		if (sum < minSum) {
			answer = i;
			minSum = sum;
		}
	}
	cout << answer << '\n';
	return 0;
}