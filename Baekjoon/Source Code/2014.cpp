// 수를 중복 제거 하는 것이 중요.
// 처음에는 map 이용 -> 메모리 초과!
// https://everenew.tistory.com/104
// GG..
#include <iostream>
#include <queue>
#include <vector>
#include <climits>

using namespace std;
int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int K, N;
	cin >> K >> N;
	vector<int> primes(K,0);
	priority_queue<int, vector<int>, greater<int>> PQ; // min_heap
	for (auto& k : primes) {
		cin >> k;
		PQ.push(k);
	}
	int count = 0;
	while (!PQ.empty()) {
		int now = PQ.top();
		PQ.pop();
		++count;
		if (count == N) {
			cout << now;
			break;
		}
		
		for (auto& k : primes) {
			long long n = static_cast<long long>(now) * k;
			if (n > INT_MAX) break; // 뒤에 더 볼 필요 없음
			PQ.push(now * k);
			if (!(now % k)) break; // 중복 제거 핵심
		}
	}
	return 0;
}