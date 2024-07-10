// https://www.acmicpc.net/problem/2470
// 정렬이 되어서 온다는 점이 차이
#include<iostream>
#include<vector>
#include<iterator> // distance
#include<cmath> // abs

using namespace std;

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int N, min = 2000000001;
	cin >> N;
	vector<int> liq(N, 0);
	for (int i = 0; i < N; ++i) {
		cin >> liq[i];
	}
	int answer1 = 0, answer2 = 0;
	auto front = liq.begin(), back = liq.end() - 1;
	while (distance(front, back) > 0) {
		int sum = *front + *back;
		if (min > abs(sum)) {
			min = abs(sum);
			answer1 = *front;
			answer2 = *back;
		}
		if (sum == 0) break;
		if (sum > 0) --back;
		else ++front;
	}
	cout << answer1 << " " << answer2;
	return 0;
}