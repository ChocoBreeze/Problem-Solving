/*
maximum number of non-connected parts from that the network may consist 
after removal of one of the joining points (not counting the removed joining point itself).
��, �� ���α׷��� ������ �� �ϳ��� ������ �� 
��Ʈ��ũ�� ������ �� �ִ� ������� ���� ��ǰ�� �ִ� ���� �����ؾ� �մϴ�(���ŵ� ������ ��ü�� ������� ����)
(�ش� �������� ���� bcc ���� + �ش� �������� ������ ���� bcc ����) �ִ밪
������ �ϳ��� ���� ���(C>=0)�� ���ؼ��� ����ϱ�
*/
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

vector<vector<int>> graph;

vector<int> dfsn; // �湮 ����
int order{};

struct Edge {
	int from, to;
	Edge(int from, int to) : from(from), to(to) {}
	bool operator==(const Edge& other) const { // �ڿ� const Ű���� ���̱�!
		return this->from == other.from && this->to == other.to;
	}
};

stack<Edge> S; // BCC�� �����ϰ� �� Edge�� ����
vector<vector<Edge>> bcc;
vector<int> bccCnt; // bccCnt[i] : i�� ���� bcc ����
vector<int> articulationPoint; // articulationPoint[i] : i�� �������ΰ�?

int DFS(int curr, int parent) {
	// return �� = curr���� �� �� �ִ� �ּ��� dfsn��
	int result = dfsn[curr] = ++order;
	int cnt{};

	for (int& next : graph[curr]) {
		if (parent == next) continue; // �ߺ� ���� ����

		// ���� �湮���� ���� ����
		if (dfsn[curr] > dfsn[next]) S.push(Edge(curr, next));

		if (dfsn[next] != 0) result = min(result, dfsn[next]); // �̹� ��
		else { // �� �湮
			int ret = DFS(next, curr);
			result = min(result, ret); // �� �ּڰ� ����

			if (ret >= dfsn[curr]) { // curr���� ������� �� �� ���� => �� BCC(curr����)
				if (parent != -1) { // �ٷ� ������
					articulationPoint[curr] = 1;
				}
				++cnt;
				// ���� (curr, next)���� pop
				++bccCnt[curr];
				Edge target(curr, next);
				while (!S.empty() && !(target == S.top())) { // S.empty() ��� �� ��?
					S.pop();
				}
				S.pop();
			}
		}
	}

	if (parent != -1 && articulationPoint[curr]) {
		// �� ������ ��Ʈ�� �ƴ϶�� ���������� 1�� �� �÷��� ������ BCC ������ ���� �� ����..(?)
		bccCnt[curr]++;
	}

	if (parent == -1 /* && cnt > 1 */) {
		// ������ ������ ����� ���� cnt�� 2�� �̻��� ��쿡�� ����� ������..
		// �ش� ���������� ���� ������ 0���� ���� �ֱ� ������ �ش� �κ� ó���� ����..
		articulationPoint[curr] = 1;
	}

	return result;
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	while (1) {
		int V, E; cin >> V >> E;
		if (V == 0 && E == 0) break;

		graph = vector<vector<int>>(V); // 0 ~ V - 1
		dfsn = vector<int>(V, 0);
		bccCnt = vector<int>(V, 0);
		articulationPoint = vector<int>(V, 0);

		for (int e{}; e < E; ++e) {
			int a, b; cin >> a >> b;
			graph[a].push_back(b);
			graph[b].push_back(a);
		}

		int tot{};
		for (int v{}; v < V; ++v) {
			if (dfsn[v] == 0) {
				tot++;
				DFS(v, -1);
			}
		}
		// cout << tot + *max_element(begin(bccCnt), end(bccCnt)) - 1 << '\n';
		int ans{};
		for (int v{}; v < V; ++v) {
			if (articulationPoint[v]) {
				ans = max(ans, tot + bccCnt[v] - 1);
			}
		}
		cout << ans << '\n';
	}
	return 0;
}