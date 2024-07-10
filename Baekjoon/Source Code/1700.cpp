// use template function
// 가장 늦게 쓸 기구를 빼고 꼽기.
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
constinit const int INF = 1 << 30;

struct Info {
	int supply;
	int nextTime;
	Info(int supply, int nextTime) : supply(supply), nextTime(nextTime) {}
};

template<typename T, typename Comp>
void NewSupply(vector<queue<int>>& supplyWillUse, int nowUse, priority_queue<T, vector<T>, Comp>& PQ) {
	supplyWillUse[nowUse].pop(); // 지금 시간 t값 빼기
	if (!supplyWillUse[nowUse].empty()) { // 다음 사용할 게 있으면
		PQ.emplace(nowUse, supplyWillUse[nowUse].front());
	}
	else {
		PQ.emplace(nowUse, INF);
	}
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int N, K; cin >> N >> K;
	vector<int> supplies(K, 0); // input
	vector<int> usedSupply(K + 1, 0); // usedSupply[i] : i번째 기구가 지금 쓰이는지
	vector<queue<int>> supplyWillUse(K+1); // supplyWillUse[i] : i번째 기구가 나중에 쓰일 time 저장
	for (int k{}; k < K; ++k) { // 전기용품의 이름이 K 이하의 자연수
		cin >> supplies[k];
		supplyWillUse[supplies[k]].push(k);
	}

	auto comp = [](const Info& i1, const Info& i2) {
		return i1.nextTime < i2.nextTime; // max heap
	};
	priority_queue<Info, vector<Info>, decltype(comp)> PQ(comp);

	int answer{};
	for (int t{}; t < K; ++t) { // time
		int nowUse = supplies[t];
		if (usedSupply[nowUse]) {

			priority_queue<Info, vector<Info>, decltype(comp)> tempPQ(comp);
			while (!PQ.empty()) { // nowUse 찾아서 pop
				Info now = PQ.top();
				if (now.supply != nowUse) {
					tempPQ.push(now);
				}
				PQ.pop();
			}
			PQ.swap(tempPQ);

			NewSupply<Info>(supplyWillUse, nowUse, PQ);
			continue; // 이미 꽂혀 있음.
		}
		if (PQ.size() < N) { // 남은 공간이 있다면 그냥 꽂기
			NewSupply<Info>(supplyWillUse, nowUse, PQ);
			usedSupply[nowUse] = 1;
		}
		else { // 남은 공간이 없다면
			++answer; // 뽑은 횟수 증가

			usedSupply[PQ.top().supply] = 0;
			PQ.pop(); 

			NewSupply<Info>(supplyWillUse, nowUse, PQ);
			usedSupply[nowUse] = 1;
		}
	}
	cout << answer << '\n';

	return 0;
}