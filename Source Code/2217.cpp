#include<iostream>
#include<algorithm>
#include<vector>

using std::cin;
using std::cout;
using std::vector;
using std::sort;
using std::max;

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int N;
	cin >> N;
	vector<int> ropes(N, 0);
	for (int i = 0; i < N; ++i) {
		cin >> ropes[i];
	}
	sort(ropes.begin(), ropes.end(), [](const int& a, const int& b) {return a > b; });
	int answer = -1;
	for (int i = 0; i < size(ropes); ++i) {
		answer = max(answer, (i + 1) * ropes[i]);
	}
	cout << answer;
	return 0;
}