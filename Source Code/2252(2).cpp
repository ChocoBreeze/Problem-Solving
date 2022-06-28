#include<iostream>
#include<vector>
#include<queue>
#include<map>
#include<utility> // pair

using namespace std;

void print(vector<int>& chk, vector<priority_queue<int, vector<int>, greater<int>>>& Qs, int i, int start) {
	if (i > start || chk[i] > 0) return;
	cout << i << " ";
	while (!Qs[i].empty()) {
		--chk[Qs[i].top()];
		print(chk, Qs, Qs[i].top(), start);
		Qs[i].pop();
	}
	return;
}

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int N, M;
	cin >> N >> M;
	vector<priority_queue<int, vector<int>, greater<int>>> Qs(N+1); // max_heap
	vector<int> chk(N + 1, 0);
	for (int i = 0; i < M; ++i) {
		int A, B;
		cin >> A >> B; // A를 B보다 먼저 풀기 100 1
		Qs[A].push(B);
		++chk[B];
	}
	for (int i = 1; i <= N; ++i) {
		if (chk[i] > 0) continue;
		print(chk, Qs, i, i);
	}
	return 0;
}