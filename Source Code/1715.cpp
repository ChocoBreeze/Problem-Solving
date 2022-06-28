#include<iostream>
#include<vector>
#include<queue>

using namespace std;
int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int N, tmp;
	cin >> N;
	priority_queue<long long, vector<long long>, greater<long long>> Q; // max_heap (default)
	for (int i = 0; i < N; ++i) {
		cin >> tmp;
		Q.push(tmp);
	}
	long long int sum = 0; // 누적 하는 부분과 다시 push하는 값이 다르다.
	while (1) {
		if (Q.size() == 1) { // 1개일 때 비용 = 0
			Q.pop();
			break;
		}
		else { // Q.size() > 1
			long long int t1, t2;
			t1 = Q.top();
			Q.pop();
			t2 = Q.top();
			Q.pop();
			sum += (t1 + t2);
			if (Q.empty()) break;
			Q.push(t1 + t2);
		}
	}
	cout << sum;
	return 0;
}