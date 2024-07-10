#include<iostream>
#include<algorithm>
#include<vector>

using std::cin;
using std::cout;
using std::vector;
using std::sort;

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int N;
	cin >> N;
	vector<int> A(N, 0), B(N, 0);
	for (int i = 0; i < N; ++i) {
		cin >> A[i];
	}
	for (int i = 0; i < N; ++i) {
		cin >> B[i];
	}
	sort(A.begin(), A.end()); // 오름차순
	auto compare = [](int a, int b) {
		return a > b;
	};
	sort(B.begin(), B.end(), compare);
	int answer = 0;
	for (int i = 0; i < N; ++i) {
		answer += A[i] * B[i];
	}
	cout << answer;
	return 0;
}