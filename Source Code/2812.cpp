// 3864KB, 16ms
#include <iostream>
#include <deque>
#include <string>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}, K{}; cin >> N >> K;
	string str; cin >> str;
	deque<int> dq;

	// 자기 이전에 들어와있던 숫자가 자신보다 작다면 빼기(단 뺀 횟수가 K보다 작을 때만)
	int popCnt{};
	for (char& c : str) {
		int num{ c - '0' };
		if (popCnt == K || dq.empty()) dq.push_back(num); // 이미 K번 다 뺐거나, 빈 dq인 경우
		else {
			while (popCnt < K && !dq.empty() && dq.back() < num) {
				dq.pop_back(), ++popCnt;
			}
			dq.push_back(num);
		}
	}

	for (int k{}; k < N - K;++k) cout << dq[k]; // N - K개의 숫자만 출력
	cout << '\n';

	return 0;
}