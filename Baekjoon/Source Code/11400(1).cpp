#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

vector<int> VisitOrder; // �湮 ���� ����
int order = 0; // �湮 ���� ����

struct Edge {
	int from, to;
	Edge(int from, int to) : from(from), to(to) {}
	bool operator<(const Edge& other) const {
		if (this->from == other.from) return this->to < other.to;
		return this->from < other.from;
	}
};

vector<Edge> answer;
vector<vector<int>> graph;

int dfs(int curr, int parent) {
	// ���� ����� low ���� �θ𿡰� ��ȯ�ؾ� ��.
	VisitOrder[curr] = ++order;
	int minOrder = VisitOrder[curr];

	for (int& next : graph[curr]) {
		if (next == parent) continue; // �θ� - ���� ���� ����
		if (VisitOrder[next]) { // �̹� �湮�� �� (root tree �� ����)
			minOrder = min(minOrder, VisitOrder[next]);
		}
		else { // �̹湮�� (�ڽ�)
			int low = dfs(next, curr);
			/*
				next���� Ʈ��, ������ �������� ���� ���� ������ �ּ��� dfsn�� curr�� dfsn���� ũ��, 
				next ������ ������κ��� curr �Ǵ� �� ���� �������� �� ������ ������ �ٷ� �� �����ۿ� ���ٴ� ��.
				�� �� ������ �������̶�� ���̴�.
			*/
			if (VisitOrder[curr] < low) { // �ϳ��� �����ϴ� ��� curr -> next�� ������
				// curr�� ���ؼ��� �� �� �ִ� ����! -> curr�� ������
				if (curr < next) answer.emplace_back(curr, next);
				else answer.emplace_back(next, curr);
			}
			minOrder = min(minOrder, low);
		}
	}
	return minOrder;
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int V, E;
	cin >> V >> E;
	
	graph = vector<vector<int>>(V + 1);
	VisitOrder = vector<int>(V + 1, 0); // �湮 ���� ����
	// VisitOrder.assign(V + 1, 0); 
	answer.reserve(V + 1); // push_back ������

	for (int e{}; e < E; ++e) {
		int a, b;  cin >> a >> b; // �����
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	// ���� �׷����� �ƴϹǷ� �� �������� dfs!
	for (int i = 1; i <= V; ++i) {
		if (!VisitOrder[i]) {
			dfs(i, 0);
		}
	}

	sort(begin(answer), end(answer));
	cout << answer.size() << '\n';
	for (Edge& e : answer) {
		cout << e.from << " " << e.to << '\n';
	}
	return 0;
}