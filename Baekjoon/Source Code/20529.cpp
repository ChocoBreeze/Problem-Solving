// 비효율적인 브루트포스 : TLE
// 비둘기집의 원리
/*
총 유형이 16개.
- 17개 넘어가면 반드시 한 개는 2개 이상
- 33개 넘어가면 반드시 한 개는 3개 이상
*/
// 5152KB, 8ms
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
int N, score{};
vector<string> strs;
vector<int> index;

int GetDiff(string& s1, string& s2) {
	int cnt{};
	for (int i{}; i < 4; ++i) {
		if (s1[i] != s2[i]) ++cnt;
	}
	return cnt;
}

void DFS(int curr) {
	if (static_cast<int>(index.size() == 3)) {
		int nowScore{};
		nowScore += GetDiff(strs[index[0]], strs[index[1]]);
		nowScore += GetDiff(strs[index[1]], strs[index[2]]);
		nowScore += GetDiff(strs[index[2]], strs[index[0]]);
		score = min(score, nowScore);
		return;
	}

	for (int i{ curr }; i < N; ++i) {
		index.push_back(i);
		DFS(i + 1);
		index.pop_back();
	}
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int T{}; cin >> T;
	while (T--) {
		cin >> N;
		score = 1 << 30;
		strs = vector<string>(N);
		for (auto& s : strs) cin >> s;
		if (N > 32) score = 0;
		else {
			DFS(0);
		}
		cout << score << '\n';
	}

	return 0;
}