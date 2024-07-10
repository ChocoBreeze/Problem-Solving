// 가방에는 최대 한 개의 보석만 넣을 수 있다.
// 가장 작은 가방부터, 가장 비싼 보석 넣기
#include <iostream>
#include <vector>
#include <queue>

using namespace std;
struct jewel {
	int m, v;
	jewel(int m, int v) : m(m), v(v) {}
	bool operator< (const jewel& other) const { // pq용 - max heap
		return v < other.v;
	}
};

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N, K; cin >> N >> K; // 보석 개수, 가방 개수
	vector<jewel> jewels(N, jewel(0, 0));
	vector<int> bags(K, 0);
	for (jewel& j : jewels) cin >> j.m >> j.v;
	for (int& b : bags) cin >> b;
	sort(begin(jewels), end(jewels), [](const jewel& j1, const jewel& j2) {
		return j1.m < j2.m;
		}); // 무게 순 오름차순 정렬
	sort(begin(bags), end(bags)); // 무게 순 오름차순 정렬

	long long answer{};
	int j{};
	priority_queue<jewel> pq;
	for(int& b : bags) { 
		// 현재 가방의 무게에 들어갈 수 있는 보석 다 pq에 넣기
		for(; j < static_cast<int>(jewels.size()) && jewels[j].m <= b; ++j) {
			pq.emplace(jewels[j].m, jewels[j].v);
		}
		// 가장 가치가 높은 보석 하나 빼기(보석이 하나라도 있다면!!
		if (!pq.empty()) {
			answer += pq.top().v; pq.pop();
		}
	}

	cout << answer << '\n';
	return 0;
}