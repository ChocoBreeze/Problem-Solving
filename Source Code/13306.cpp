#include <iostream>
#include <vector>
#include <string>

using namespace std;
constinit const int DEL = 0;
constinit const int QUERY = 1;

struct UnionFind {
	vector<int> par;
	UnionFind(int n) : par(n, -1) {}
	int Find(int a) {
		if (par[a] < 0) return a;
		return par[a] = Find(par[a]);
	}
	bool Union(int a, int b) {
		a = Find(a), b = Find(b);
		if (a == b) return false;
		if (-par[a] < -par[b]) swap(a, b); // a가 더 크도록
		par[a] += par[b];
		par[b] = a;
		return true;
	}
	bool IsSame(int a, int b) {
		a = Find(a), b = Find(b);
		if (a == b) return true;
		else return false;
	}
};

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N, Q; // 정점 개수, 질의 개수
	cin >> N >> Q;
	UnionFind uf(N + 1); // 1 ~ N
	vector<int> parInfo(N + 1); // n번 정점의 par 저장
	for (int n = 2; n <= N; ++n) {
		cin >> parInfo[n];
	}

	// Query 저장
	vector<vector<int>> queries(N + Q - 1, vector<int>(3, 0));
	for (auto& q : queries) {
		cin >> q[0];
		if (q[0] == DEL) {
			cin >> q[1];
		}
		else {
			cin >> q[1] >> q[2];
		}
	}

	// 거꾸로
	vector<string> answers;
	for (auto it = rbegin(queries); it != rend(queries); ++it) {
		vector<int>& q = *it;
		if (q[0] == DEL) {
			// q[1]의 부모 정점과 q[1] 연결 (삭제가 아닌)
			uf.Union(q[1], parInfo[q[1]]);
		}
		else {
			// q[1], q[2] 연결되어 있는지 확인
			if (uf.IsSame(q[1], q[2])) answers.push_back("YES");
			else answers.push_back("NO");
		}
	}

	for (auto it = rbegin(answers); it != rend(answers); ++it) {
		cout << *it << '\n';
	}

	return 0;
}
