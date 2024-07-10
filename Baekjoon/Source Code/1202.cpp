// ���濡�� �ִ� �� ���� ������ ���� �� �ִ�.
// ���� ���� �������, ���� ��� ���� �ֱ�
#include <iostream>
#include <vector>
#include <queue>

using namespace std;
struct jewel {
	int m, v;
	jewel(int m, int v) : m(m), v(v) {}
	bool operator< (const jewel& other) const { // pq�� - max heap
		return v < other.v;
	}
};

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N, K; cin >> N >> K; // ���� ����, ���� ����
	vector<jewel> jewels(N, jewel(0, 0));
	vector<int> bags(K, 0);
	for (jewel& j : jewels) cin >> j.m >> j.v;
	for (int& b : bags) cin >> b;
	sort(begin(jewels), end(jewels), [](const jewel& j1, const jewel& j2) {
		return j1.m < j2.m;
		}); // ���� �� �������� ����
	sort(begin(bags), end(bags)); // ���� �� �������� ����

	long long answer{};
	int j{};
	priority_queue<jewel> pq;
	for(int& b : bags) { 
		// ���� ������ ���Կ� �� �� �ִ� ���� �� pq�� �ֱ�
		for(; j < static_cast<int>(jewels.size()) && jewels[j].m <= b; ++j) {
			pq.emplace(jewels[j].m, jewels[j].v);
		}
		// ���� ��ġ�� ���� ���� �ϳ� ����(������ �ϳ��� �ִٸ�!!
		if (!pq.empty()) {
			answer += pq.top().v; pq.pop();
		}
	}

	cout << answer << '\n';
	return 0;
}