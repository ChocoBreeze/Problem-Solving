// 그냥 간단하게 N개 유지
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}; cin >> N;
	
	priority_queue<int, vector<int>, greater<int>> pq; // min heap
	for (int n{}; n < N * N; ++n) {
		int v{}; cin >> v;
		if (static_cast<int>(pq.size()) < N) pq.push(v);
		else {
			if (pq.top() < v) {
				pq.pop();
				pq.push(v);
			}
		}
	}
	cout << pq.top() << '\n';

	return 0;
}