// n = 4000 nlogn = 4000 * 11.97 = 47,880(정렬)
// 다 찾기 -> 4000*4000*4000*4000 = 256,000,000,000,000(256조)
// 배열에 들어 있는 정수의 절대값은 최대 2^28 --> 4개 더해도 2^30이므로 int로 가능
// 배열이 2개일 때 two pointer로 두 배열의 합을 구할 수 있음.
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
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			AB.push_back(A[i] + B[j]);
			CD.push_back(C[i] + D[j]);
		}
	}
	sort(begin(AB), end(AB)); // ascend
	sort(begin(CD), end(CD), greater<int>()); // descend
	auto it1 = begin(AB), it2 = begin(CD);
	// int sum = *it1 + *it2;  굳이 sum 유지할 필요 없다..
	long long answer = 0;
	while (it1 < end(AB) && it2 < end(CD)) { // 하다하다 조건에 ,를 적네 ㅋㅋ
		if (*it1+(* it2) == 0) {
			long long cnt1 = 0, cnt2 = 0;
			int temp = *it1;
			while (it1 < end(AB) && *it1 == temp) {
				++cnt1;
				++it1;
			}
			while (it2 < end(CD) && -(*it2) == temp) {
				++cnt2;
				++it2;
			}
			answer += cnt1 * cnt2;
		}
		else if (*it1+*it2 < 0) {
			++it1;
		}
		else {
			++it2;
		}
	}
	cout << answer;
	return 0;
}
