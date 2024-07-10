/*
* general case there are n jobs numbered from 0 to n-1, n servers numbered from n to 2 *n-1
* The problem asks to find the maximum number of jobs that can be processed
*/

// https://m.blog.naver.com/kks227/220816033373
// Hopcroft-Karp ����

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;
constinit const int INF = 1'000'000'000;

int N;
vector<int> A, B, dist;
// dist[i]: (A�׷���) i�� ������ ����(?)
// A[i], B[i]: �׷��� i�� ������ ��Ī�� ����� �׷� ���� ��ȣ
vector<bool> used; // (A �׷���) �� ������ ��Ī�� ���� �ִ°�?
vector<vector<int>> adj;

// ȣ��ũ����Ʈ ī�� ���� bfs �Լ� : A �׷��� �� ������ ������ �ű�
void bfs() {
	queue<int> Q;
	// ��Ī�� �� ���� A �׷��� ������ ���� 0�� ä�� ����
	for (int i{}; i < N; ++i) {
		if (!used[i]) {
			dist[i] = 0;
			Q.push(i);
		}
		else dist[i] = INF;
	}

	// BFS�� ���� A�׷� ������ 0, 1, 2, 3, ... �� ������ �ű�
	while (!Q.empty()) {
		int now = Q.front(); Q.pop();
		for (int& next : adj[now]) {
			if (B[next] != -1 && dist[B[next]] == INF) {
				dist[B[next]] = dist[now] + 1;
				Q.push(B[next]);
			}
		}
	}
}

// ȣ��ũ����Ʈ ī�� ���� dfs �Լ� : �� ��Ī�� ã���� true
bool dfs(int a) {
	for (int& b : adj[a]) {
		// �̺� ��Ī �ڵ�� ����� �����ϳ�, dist �迭�� ���� ������ �߰��� ����
		if (B[b] == -1 || (dist[B[b]] == dist[a] + 1 && dfs(B[b]))) {
			// used �迭 ���� true�� ��
			used[a] = true;
			A[a] = b;
			B[b] = a;
			return true;
		}
	}
	return false;
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	while (cin >> N) {
		A = vector<int>(N, -1);
		B = vector<int>(N, -1);
		used = vector<bool>(N, false);
		adj = vector<vector<int>>(N);
		dist = vector<int>(N, 0);

		// input
		for (int n{}; n < N; ++n) { // �׷��� ���� �Է� �ޱ�
			int job, serverN;
			char colon, openBracket, closeBracket;
			cin >> job >> colon >> openBracket >> serverN >> closeBracket; // job: (serverN)
			for (int s{}; s < serverN; ++s) {
				int server{}; cin >> server;
				adj[job].push_back(server - N);
			}
		}

		// Hopcroft-Karp
		int match{};

		while (1) {
			// �� ������ ������ �ű�� ����
			bfs();

			// �̺� ��Ī�� ����ϰ� A�׷� ������ ��ȸ�ϸ� ��Ī ������ ã��
			int flow{};
			for (int n{}; n < N; ++n) {
				if (!used[n] && dfs(n)) ++flow;
			}

			// �� �̻� ���� ��θ� �� ã���� �˰��� ����
			if (flow == 0) break;

			// ã���� ��� �ݺ�
			match += flow;
		}
		cout << match << '\n'; // ��� ���
	}
	return 0;
}