/*
3면 필요 -> 위에 4개 --> 가장 작은 3개합 * 4
2면 필요 -> 밑에 4개 + 위에 4*(n-2) + 옆에 4*(n-2) --> 가장 작은 2개합 * (8n-12)
1면 -> 나머지 (n-2)*(n-2) + (n-2)*(n-1)*4 = (n-2)(5n-6)
3면 --> ABC / ABD / ADE / ACE / FBC / FBD / FDE / FCE
2면 --> AB / AC / AD / AE / BC / BD / BF / CE / CF / DE / DF / EF
*/
#include<iostream>
#include<vector>
#include<climits>
#include<algorithm>

using namespace std;
long long int find_min_3(vector<long long int>& A) { // 3개 합
	long long int min = INT_MAX;
	if (min > A[0] + A[1] + A[2]) min = A[0] + A[1] + A[2];
	if (min > A[0] + A[1] + A[3]) min = A[0] + A[1] + A[3];
	if (min > A[0] + A[3] + A[4]) min = A[0] + A[3] + A[4];
	if (min > A[0] + A[2] + A[4]) min = A[0] + A[2] + A[4];
	if (min > A[5] + A[1] + A[2]) min = A[5] + A[1] + A[2];
	if (min > A[5] + A[1] + A[3]) min = A[5] + A[1] + A[3];
	if (min > A[5] + A[3] + A[4]) min = A[5] + A[3] + A[4];
	if (min > A[5] + A[2] + A[4]) min = A[5] + A[2] + A[4];
	return min;
}

long long int find_min_2(vector<long long int>& A) { // 2개 합
	long long int min = INT_MAX;
	if (min > A[0] + A[1]) min = A[0] + A[1];
	if (min > A[0] + A[2]) min = A[0] + A[2];
	if (min > A[0] + A[3]) min = A[0] + A[3];
	if (min > A[0] + A[4]) min = A[0] + A[4];
	if (min > A[1] + A[2]) min = A[1] + A[2];
	if (min > A[1] + A[3]) min = A[1] + A[3];
	if (min > A[1] + A[5]) min = A[1] + A[5];
	if (min > A[2] + A[4]) min = A[2] + A[4];
	if (min > A[2] + A[5]) min = A[2] + A[5];
	if (min > A[3] + A[4]) min = A[3] + A[4];
	if (min > A[3] + A[5]) min = A[3] + A[5];
	if (min > A[4] + A[5]) min = A[4] + A[5];
	return min;
}

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	long long int n;
	cin >> n;
	long long int min_1 = INT_MAX;
	vector<long long int> A(6, 0);
	for (auto& i : A) {
		cin >> i;
		if (min_1 > i) min_1 = i;
	}
	long long int answer;
	if (n == 1) {
		sort(begin(A), end(A));
		answer = A[0] + A[1] + A[2] + A[3] + A[4];
	}
	else {
		long long int min_3 = find_min_3(A);
		long long int min_2 = find_min_2(A);
		answer = 4 * min_3 + min_2 * (8 * n - 12) + min_1 * (n - 2) * (5 * n - 6);
	}
	cout << answer;
}