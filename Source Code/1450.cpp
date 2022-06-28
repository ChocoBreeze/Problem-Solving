// meet in the middle + lower_bound
// 2^N -> 2*2^(N/2) + NlogN
#include<iostream>
#include<vector>
#include<algorithm>

using std::cin;
using std::cout;
using std::sort;
using std::vector;
using std::lower_bound;
using std::distance;

int chk = 0;
void make_sum(vector<int>& a, vector<long long>& result, int now, int end, long long sum, int S, long long& only) {
	if (now > end) {
		if (chk != 0) {
			result.push_back(sum);
			if (sum <= S) ++only;
		}
		chk = 1;
		return;
	}

	make_sum(a, result, now + 1, end, sum, S, only); // now번째 수 추가 x
	make_sum(a, result, now + 1, end, sum + a[now], S, only); // now번째 수 추가
}

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int N;
	long long S;
	cin >> N >> S;
	vector<int> a(N, 0);
	for (int i = 0; i < N; ++i) {
		cin >> a[i];
	}
	// O(2^(N/2))
	vector<long long> result_front;
	vector<long long> result_back;
	long long only_front = 0, only_back = 0; // 아무것도 포함하지 않는 경우 제외하고 카운팅
	make_sum(a, result_front, 0, N / 2 - 1, 0, S, only_front);
	chk = 0;
	make_sum(a, result_back, N / 2, N - 1, 0, S, only_back);
	sort(begin(result_back), end(result_back));
	long long answer = only_front + only_back;
	for (auto& i : result_front) {
		// upper bound : greater than value
		// lower bound : less than or equal value
		auto finish = lower_bound(begin(result_back), end(result_back), S - i + 1);
		auto distance_ = distance(begin(result_back), finish);
		answer += distance(begin(result_back), finish); // distance<0인 경우는 없음
		
	}
	cout << answer + 1;
	return 0;
}