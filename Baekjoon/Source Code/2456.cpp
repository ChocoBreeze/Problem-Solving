#include<iostream>
#include<vector>

using std::cin;
using std::cout;
using std::vector;

inline void print(int i, vector<int>& sum) {
	cout << i + 1 << " " << sum[i];
}
inline void else_print(int max) {
	cout << 0 << " " << max;
}

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int N;
	cin >> N;
	int a, b, c;
	vector<int> cnt_3(3, 0);
	vector<int> cnt_2(3, 0);
	vector<int> sum(3, 0);
	for (int i = 0; i < N; ++i) {
		cin >> a >> b >> c;
		if (a == 3) ++cnt_3[0];
		else if (b == 3) ++cnt_3[1];
		else ++cnt_3[2];
		if (a == 2) ++cnt_2[0];
		else if (b == 2) ++cnt_2[1];
		else ++cnt_2[2];
		sum[0] += a;
		sum[1] += b;
		sum[2] += c;
	}
	// 결정
	if (sum[0] > sum[1] && sum[0] > sum[2]) print(0, sum);
	else if (sum[1] > sum[0] && sum[1] > sum[2]) print(1, sum);
	else if (sum[2] > sum[1] && sum[2] > sum[0]) print(2, sum);
	else if (sum[0] == sum[2] && sum[0] == sum[1]) {
		if (cnt_3[0] == cnt_3[1] == cnt_3[2]) {
			if (cnt_2[0] == cnt_2[1] == cnt_2[2]) {
				else_print(sum[0]);
			}
			else {
				if (cnt_2[0] > cnt_2[1] && cnt_2[0] > cnt_2[2]) print(0, sum);
				else if (cnt_2[1] > cnt_2[0] && cnt_2[1] > cnt_2[2]) print(1, sum);
				else if (cnt_2[2] > cnt_2[0] && cnt_2[2] > cnt_2[1]) print(2, sum);
				else else_print(sum[0]);
			}
		}
		else {
			if (cnt_3[0] > cnt_3[1] && cnt_3[0] > cnt_3[2]) print(0, sum);
			else if (cnt_3[1] > cnt_3[0] && cnt_3[1] > cnt_3[2]) print(1, sum);
			else if (cnt_3[2] > cnt_3[0] && cnt_3[2] > cnt_3[1]) print(2, sum);
			else if (cnt_3[0] == cnt_3[1]) {
				if (cnt_2[0] > cnt_2[1]) print(0, sum);
				else if (cnt_2[0] < cnt_2[1]) print(1, sum);
				else else_print(sum[0]);
			}
			else if (cnt_3[1] == cnt_3[2]) {
				if (cnt_2[1] > cnt_2[2]) print(1, sum);
				else if (cnt_2[1] < cnt_2[2]) print(2, sum);
				else else_print(sum[0]);
			}
			else if (cnt_3[0] == cnt_3[2]) {
				if (cnt_2[0] > cnt_2[2]) print(0, sum);
				else if (cnt_2[0] < cnt_2[2]) print(2, sum);
				else else_print(sum[0]);
			}
		}
	}
	else if (sum[0] == sum[1]) {
		if (cnt_3[0] != cnt_3[1]) {
			if(cnt_3[0]>cnt_3[1]) print(0, sum);
			else print(1, sum);
		}
		else { // cnt_3[0] == cnt_3[1]
			if (cnt_2[0] != cnt_2[1]) {
				if (cnt_2[0] > cnt_2[1]) print(0, sum);
				else print(1, sum);
			}
			else else_print(sum[0]);
		}
	}
	else if (sum[1] == sum[2]) {
		if (cnt_3[1] != cnt_3[2]) {
			if (cnt_3[1] > cnt_3[2]) print(1, sum);
			else print(2, sum);
		}
		else { // cnt_3[1] == cnt_3[2]
			if (cnt_2[1] != cnt_2[2]) {
				if (cnt_2[1] > cnt_2[2]) print(1, sum);
				else print(2, sum);
			}
			else else_print(sum[1]);
		}
	}
	else if (sum[0] == sum[2]) {
		if (cnt_3[0] != cnt_3[2]) {
			if (cnt_3[0] > cnt_3[2]) print(0, sum);
			else print(2, sum);
		}
		else { // cnt_3[0] == cnt_3[2]
			if (cnt_2[0] != cnt_2[2]) {
				if (cnt_2[0] > cnt_2[2]) print(0, sum);
				else print(2, sum);
			}
			else else_print(sum[0]);
		}
	}
	return 0;
}