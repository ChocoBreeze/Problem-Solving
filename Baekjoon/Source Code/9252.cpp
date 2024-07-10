#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::max;

struct data {
	int i;
	int j;
	char a;
	data(int i, int j, char a) : i(i), j(j), a(a) {}
};

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	string A, B;
	cin >> A >> B;
	vector<vector<int>> dp(A.length() + 1, vector<int>(B.length() + 1, 0));
	vector<vector<data>> dp_index(A.length() + 1, vector<data>(B.length() + 1, data(0,0,0)));
	for (int i = 0; i <= A.length(); ++i) {
		for (int j = 0; j <= B.length(); ++j) {
			int temp = 0;
			data temp1(0, 0, 0);
			if (i > 0 && j > 0) {
				temp = dp[i - 1][j - 1];
				temp1 = dp_index[i - 1][j - 1];
				if (A[i - 1] == B[j - 1]) {
					++temp;
					temp1 = data(i-1, j-1, A[i-1]);
				}
			}
			if(i>0) {
				if (temp < dp[i - 1][j]) {
					temp = dp[i - 1][j];
					temp1 = dp_index[i - 1][j];
				}
			}
			if (j > 0) {
				if (temp < dp[i][j - 1]) {
					temp = dp[i][j - 1];
					temp1 = dp_index[i][j - 1];
				}
			}
			dp[i][j] = temp;
			dp_index[i][j] = temp1;
		}
 	}
	cout << dp[A.length()][B.length()] << "\n";
	int i = A.length(), j = B.length();
	string answer(dp[A.length()][B.length()], 0);
	for (int k = 0; k < dp[A.length()][B.length()]; ++k) {
		answer[dp[A.length()][B.length()] - 1 - k] = dp_index[i][j].a;
		int new_i = dp_index[i][j].i, new_j = dp_index[i][j].j;
		i = new_i;
		j = new_j;
	}
	cout << answer;
	return 0;
}