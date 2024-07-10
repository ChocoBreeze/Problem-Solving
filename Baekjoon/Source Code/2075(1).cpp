#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}; cin >> N;
	// N x N ���� �� �߿��� N��°�� ū ��
	vector<int> vec(N * N, 0);
	for (int& v : vec) cin >> v;
	sort(begin(vec), end(vec), greater<int>());
	cout << vec[N - 1] << '\n';

	return 0;
}