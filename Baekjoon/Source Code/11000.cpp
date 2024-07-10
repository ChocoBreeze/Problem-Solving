// https://www.acmicpc.net/board/view/33337
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

using pii = pair<int, int>;

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	int N;
	cin >> N;
	vector<pii> vec(N, make_pair(0, 0));
	for (auto& n : vec) {
		cin >> n.first >> n.second;
	}
	auto compare = [](const pii& a, const pii& b) {
		return a.first < b.first;
	};
	sort(begin(vec), end(vec), compare);

	auto compare2 = [](const int& a, const int& b){
		return a > b;
	};
	// priority queue가 있었구나..
	priority_queue<int, vector<int>, decltype(compare2)> Q(compare2);
	Q.push(0);

	int answer = 1;
	for (auto& v : vec) {
		if (Q.top() <= v.first) {
			Q.pop();
			Q.push(v.second);
		}
		else {
			Q.push(v.second);
			answer = max(answer, static_cast<int>(Q.size()));
		}
	}
	cout << answer << '\n';


	return 0;
}