#include <iostream>
#include <vector>
#include <utility>

using namespace std;
using pii = pair<int, int>;
vector<pii> clauses;

int N, M;
vector<int> state; // True, False 여부
bool chk = false;

vector<int> answer;

void DFS(int index) {
	if (index == N + 1) {
		for (pii& clause : clauses) {
			bool f{}, s{};
			if (clause.first < 0) f = state[clause.first * (-1)] ^ 1;
			else f = state[clause.first];
			if (clause.second < 0) s = state[clause.second * (-1)] ^ 1;
			else s = state[clause.second];
			if (f == false && s == false) { // 더 볼 필요 없음
				return;
			}
		}
		chk = true;
		answer.assign(begin(state), end(state)); // copy
		return;
	}

	if (chk) return;
	state[index] = 0;
	DFS(index + 1);

	if (chk) return;
	state[index] = 1;
	DFS(index + 1);
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cin >> N >> M;

	clauses = vector<pii>(M, make_pair(0, 0));
	state = vector<int>(N + 1, 0);
	for (pii& p : clauses) {
		cin >> p.first >> p.second;
	}

	DFS(1);
	if (chk) {
		cout << "1\n";
		for (int i{ 1 }; i <= N; ++i) cout << answer[i] << ' ';
		cout << '\n';
	}
	else cout << "0\n";

	return 0;
}