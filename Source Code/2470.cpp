// 2개만 섞음.
#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<utility>

using std::abs;
using std::cout;
using std::cin;
using std::vector;
using std::sort;
using std::distance;
using std::pair;

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int N, min = 2000000001;
	cin >> N;
	vector<int> liq(N, 0);
	for (int i = 0; i < N; ++i) {
		cin >> liq[i];
	}
	pair<int, int> answer;
	sort(liq.begin(), liq.end());
	auto front = liq.begin(), back = liq.end()-1;
	while (distance(front, back) > 0) {
		int sum = *front + *back;
		if (min > abs(sum)) {
			min = abs(sum);
			answer.first = *front;
			answer.second = *back;
		}
		if (sum == 0) break;
		if (sum > 0) --back;
		else ++front;
	}
	cout << answer.first << " " << answer.second;
	return 0;
}