/*
dp[i][j] : i번째까지의 동전을 이용해서 j 금액을 만들 수 있는 방법 수
[i][j] = [i-1][j-coins[i]] + [i-1][j-coins[j]*2] + ...
3 10
1 2 5

0 1 2 3 4 5 6 7 8 9 10
1 1 1 1 1 1 1 1 1 1 1
1 1 2 0 3 0 1 0 1 0 1

[i][j] = 1 + [i-1][j-coins[i]] + [i-1][j-coins[j]*2] + ...

[1][1] = 0(1<=coins[0]) + [0][1]
[1][2] = [1][0] + [0][0]
[1][3] = 0 + [0][3] + [0][1] = [1][1] + [0][3]
[1][4] = 1 + [0][2] + [0][0] = [1][2] + [0][2]
[1][6] = 1 + [0][4] + [0][2] + [0][0] = [1][4] + [0][4]
* 
*/
#include<iostream>
#include<vector>
#include<utility> // std::move

using std::cin;
using std::cout;
using std::vector;
using std::move;

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int n, k;
	cin >> n >> k;
	vector<int> coins(n,0);
	for (int i = 0; i < n; ++i) {
		cin >> coins[i];
	}
	// vector<vector<int>> possible(n, vector<int>(k + 1, 0)); // 2D 메모리 초과
	vector<int> possible(k + 1, 0);
	for (int i = 0; i < n; ++i) {
		possible[0] = 1;
		for (int j = 1; j <= k; ++j) {
			int without_i = i >= 1 ? possible[j] : 0;
			int with_i = j >= coins[i] ? possible[j - coins[i]] : 0;
			possible[j] = without_i + with_i;
		}
	}
	cout << possible[k];
	return 0;
}