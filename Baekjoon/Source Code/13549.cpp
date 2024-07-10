// 0 - 1 bfs - O(V+E)이므로 처음 도착하는 경로가 아닌 다 돌아도 무방하다고 생각.
// deque 이용
#include<deque>
#include<iostream>
#include<vector>
#include<utility> // pair

using std::cin;
using std::cout;
using std::deque;
using std::pair;
using std::make_pair;
using std::vector;

const int M = 100005;
int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int N, K, answer = M;
	cin >> N >> K;
	// 1초 +1, -1
	// 0초 *2
	deque<pair<int, int>> dq;
	vector<int> visited(M, -1); // bool이 아닌 cost 표시
	dq.push_back(make_pair(N, 0));
	visited[N] = 0;
	while (!dq.empty()) {
		auto now = dq.front();
		if (now.first == K && answer > now.second) answer = now.second; // 0 0
		dq.pop_front();
		if (now.first * 2 < M) {// 비용 변동 없기 때문에 제일 앞에 추가
			if (visited[now.first * 2] == -1 || visited[now.first * 2] > now.second) {
				if (now.first * 2 == K && answer > now.second) answer = now.second;
				dq.push_front(make_pair(now.first * 2, now.second));
				visited[now.first * 2] = now.second;
			}
		}
		if(now.first + 1 < M) { // 비용이 늘어나므로 뒤에 추가
			if (visited[now.first + 1] == -1 || visited[now.first + 1] > now.second + 1) {
				if (now.first + 1 == K && answer > now.second + 1) answer = now.second + 1;
				dq.push_back(make_pair(now.first + 1, now.second + 1));
				visited[now.first + 1] = now.second + 1;
			}
		}
		if (now.first - 1 >= 0) { // 비용이 늘어나므로 뒤에 추가
			if (visited[now.first - 1] == -1 || visited[now.first - 1] > now.second + 1) {
				if (now.first - 1 == K && answer > now.second + 1) answer = now.second + 1;
				dq.push_back(make_pair(now.first - 1, now.second + 1));
				visited[now.first - 1] = now.second + 1;
			}
		}
	}
	cout << answer;
	return 0;
}