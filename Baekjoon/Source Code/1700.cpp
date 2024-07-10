// use template function
// ���� �ʰ� �� �ⱸ�� ���� �ű�.
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
	supplyWillUse[nowUse].pop(); // ���� �ð� t�� ����
	if (!supplyWillUse[nowUse].empty()) { // ���� ����� �� ������
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
	vector<int> usedSupply(K + 1, 0); // usedSupply[i] : i��° �ⱸ�� ���� ���̴���
	vector<queue<int>> supplyWillUse(K+1); // supplyWillUse[i] : i��° �ⱸ�� ���߿� ���� time ����
	for (int k{}; k < K; ++k) { // �����ǰ�� �̸��� K ������ �ڿ���
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
			while (!PQ.empty()) { // nowUse ã�Ƽ� pop
				Info now = PQ.top();
				if (now.supply != nowUse) {
					tempPQ.push(now);
				}
				PQ.pop();
			}
			PQ.swap(tempPQ);

			NewSupply<Info>(supplyWillUse, nowUse, PQ);
			continue; // �̹� ���� ����.
		}
		if (PQ.size() < N) { // ���� ������ �ִٸ� �׳� �ȱ�
			NewSupply<Info>(supplyWillUse, nowUse, PQ);
			usedSupply[nowUse] = 1;
		}
		else { // ���� ������ ���ٸ�
			++answer; // ���� Ƚ�� ����

			usedSupply[PQ.top().supply] = 0;
			PQ.pop(); 

			NewSupply<Info>(supplyWillUse, nowUse, PQ);
			usedSupply[nowUse] = 1;
		}
	}
	cout << answer << '\n';

	return 0;
}