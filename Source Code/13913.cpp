#include <iostream>
#include <vector>
#include <climits>
#include <queue>

using namespace std;

const int SIZE = 100000;
int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int N, K;
	cin >> N >> K;
	queue<int> Q;
	vector<int> A(2 * SIZE, INT_MAX);
	vector<int> path(2 * SIZE, -1);
	Q.push(N);
	A[N] = 0;
	while (!Q.empty()) {
		int now = Q.front();
		Q.pop();
		if (now * 2 < 2 * SIZE && A[now * 2] > A[now] + 1) {
			path[now * 2] = now;
			Q.push(now * 2);
			A[now * 2] = A[now] + 1;
			if (now * 2 == K) break;
		}
		if (now + 1 < 2 * SIZE && A[now + 1] > A[now] + 1) {
			path[now + 1] = now;
			Q.push(now + 1);
			A[now + 1] = A[now] + 1;
			if (now + 1 == K) break;
		}
		if (now - 1 >= 0 && A[now - 1] > A[now] + 1) {
			path[now - 1] = now;
			Q.push(now - 1);
			A[now - 1] = A[now] + 1;
			if (now - 1 == K) break;
		}
	}
	cout << A[K] << "\n";
	vector<int> answer={K};
	int index = path[K];
	for (int i = A[K]; i > 0; --i) {
		answer.push_back(index);
		index = path[index];
	}
	for (auto i = rbegin(answer); i != rend(answer); ++i) {
		cout << *i << " ";
	}
	return 0;
}