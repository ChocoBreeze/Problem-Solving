// topological sort https://hongcoding.tistory.com/94
#include<iostream>
#include<vector>
#include<queue>

using namespace std;

void delete_edge(priority_queue<int, vector<int>, greater<int>>& Qs, vector<int>& chk, vector<vector<int>>& s, int i) {
	cout << i << " ";
	for(auto & e : s[i]) {
		--chk[e];
		if (chk[e] == 0) Qs.push(e);
	}
}

void push_Q(priority_queue<int, vector<int>, greater<int>>& Qs, vector<int>& chk) {
	int N = size(chk) - 1;
	for (int i = 1; i <= N; ++i) {
		if (chk[i] == 0) {
			Qs.push(i);
			--chk[i]; // 중복 방지
		}
	}
}

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int N, M;
	cin >> N >> M;
	vector<vector<int>> s(N + 1);
	priority_queue<int, vector<int>, greater<int>> Qs;
	vector<int> chk(N + 1, 0);
	for (int i = 0; i < M; ++i) {
		int A, B;
		cin >> A >> B; // A를 B보다 먼저 풀기 100 1
		s[A].push_back(B);
		++chk[B];
	}
	push_Q(Qs, chk);
	// 다음에 찾을 노드를 heap으로 구현.
	// 순서대로 와야 하니까.
	while (!Qs.empty()) {
		int now = Qs.top();
		Qs.pop();
		delete_edge(Qs, chk, s, now); // 의존 관계 제거
		// push_Q(Qs, chk);
	}
	return 0;
}