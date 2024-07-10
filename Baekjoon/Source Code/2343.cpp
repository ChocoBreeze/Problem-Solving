#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int calculate_M(vector<int>& vec, int length) {
	int M = 1,temp_sum = 0;
	for (int j = 0; j < vec.size(); ++j) {
		if (temp_sum + vec[j] > length) {
			++M;
			temp_sum = 0;
		}
		temp_sum += vec[j];
	}
	return M;
}

int main()
{
	cin.tie(NULL)->sync_with_stdio(false);
	int N, M, start = 0, end = 1000000000;
	cin >> N >> M;
	vector<int> vec(N,0);
	for (auto& v : vec) {
		cin >> v;
		if (!start) start = v; // 적어도 넘겨야 할 길이
		else start = max(start, v);
	}

	while (start < end) {
		int mid = start + (end - start) / 2;
		int ret_M = calculate_M(vec, mid);
		if (ret_M <= M) end = mid;
		else start = mid + 1;
	}

	cout << start;
	return 0;
}