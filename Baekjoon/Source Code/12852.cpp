#include<iostream>
#include<queue>
#include<vector>
#include<utility>

using std::queue;
using std::vector;
using std::cin;
using std::cout;
using std::pair;
using std::make_pair;

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int N;
	cin >> N;
	vector<pair<int,int>> visited(N + 1, make_pair(1000001, -1)); // cost, from
	queue<pair<int,int>> Q; // 현재값, cost
	Q.push(make_pair(N, 0));
	visited[N].first = 0;
	visited[N].second = -1;
	while (!Q.empty()) {
		pair<int,int> now = Q.front();
		Q.pop();
		if (now.first % 3 == 0 && now.first / 3 > 0 && visited[now.first / 3].first > now.second + 1) {
			visited[now.first / 3].first = now.second + 1;
			visited[now.first / 3].second = now.first;
			Q.push(make_pair(now.first / 3, now.second + 1));
		}
		if (now.first % 2 == 0 && now.first / 2 > 0 && visited[now.first / 2].first > now.second + 1) {
			visited[now.first / 2].first = now.second + 1;
			visited[now.first / 2].second = now.first;
			Q.push(make_pair(now.first / 2, now.second + 1));
		}
		if (now.first - 1 > 0 && visited[now.first - 1].first > now.second + 1) {
			visited[now.first - 1].first = now.second + 1;
			visited[now.first - 1].second = now.first;
			Q.push(make_pair(now.first - 1, now.second + 1));
		}
	}
	vector<int> answer = {1};
	int start = 1;
	while (start!=N) {
		answer.push_back(visited[start].second);
		start = visited[start].second;
	}
	cout << visited[1].first << "\n";
	for (auto i = answer.rbegin(); i != answer.rend(); ++i) {
		cout << *i << " ";
	}
	return 0;
}