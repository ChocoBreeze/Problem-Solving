// n = 4000 nlogn = 4000 * 11.97 = 47,880(정렬)
// 다 찾기 -> 4000*4000*4000*4000 = 256,000,000,000,000(256조)
// 배열에 들어 있는 정수의 절대값은 최대 2^28 --> 4개 더해도 2^30이므로 int로 가능
// 배열이 2개일 때 개수 구하기
// 배열 4개를 2개로 변경!
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	vector<int> A(n, 0), B(n, 0), C(n, 0), D(n, 0);
	for (int i = 0; i < n; ++i) {
		cin >> A[i] >> B[i] >> C[i] >> D[i];
	}
	vector<int> AB, CD;
	AB.reserve(n * n); // 할당 안하고 pushback하면 느리다해서..
	CD.reserve(n * n);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			AB.push_back(A[i] + B[j]);
			CD.push_back(C[i] + D[j]);
		}
	}
	sort(begin(CD), end(CD));
	long long answer = 0;
	for (auto& i : AB) {
		// auto it1 = lower_bound(begin(CD), end(CD), -i);
		// auto it2 = upper_bound(begin(CD), end(CD), -i);
		auto t = equal_range(begin(CD), end(CD), -i);
		answer += distance(t.first, t.second);
		// answer += distance(it1, it2);
	}
	cout << answer;
	return 0;
}
