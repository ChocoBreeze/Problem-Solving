// pascal triangle
#include <iostream>
#include <vector>
using namespace std;

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int N, K;
	// N : 1 ~ 10, K : 0 ~ N
	cin >> N >> K;
	vector<vector<int>> pascal(N + 1);
	for (int i = 1; i <= N; ++i) {
		pascal[i].push_back(1); // NC0 = 1
		for (int j = 1; j < i; ++j) {
			pascal[i].push_back(pascal[i - 1][j - 1] + pascal[i - 1][j]);
		}
		pascal[i].push_back(1); // NCN = 1
	}
	cout << pascal[N][K];
	return 0;
}