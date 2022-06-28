// https://www.acmicpc.net/board/view/21480
// dp[a][b] : 경찰차 1이 사건a, 경찰차 2가 사건b를 맡을 때의 비용
#include<iostream>
#include<vector>
#include<algorithm>
#include<utility> // pair
#include<climits>

using namespace std;

int N, W;
int get_dist(vector<pair<int, int>>& Ws, int i, int j) {
	if (j < 0) return abs(1 - Ws[i].first) + abs(1 - Ws[i].second);
	else if (i < 0) return abs(N - Ws[j].first) + abs(N - Ws[j].second);
	else return abs(Ws[i].first - Ws[j].first) + abs(Ws[i].second - Ws[j].second);
}

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	cin >> N >> W;
	vector<pair<int, int>> Ws(W);
	for (int w = 0; w < W; ++w) {
		cin >> Ws[w].first >> Ws[w].second;
	}
	vector<vector<int>> dp(W + 1, vector<int>(W+1,INT_MAX));
	vector<vector<pair<int, int>>> dp_(W + 1, vector<pair<int, int>>(W + 1, make_pair(-1, -1)));
	dp[0][0] = 0;
	dp[1][0] = get_dist(Ws, 0, -1);
	dp_[1][0] = make_pair(0, 0);
	dp[0][1] = get_dist(Ws, -1, 0);
	dp_[0][1] = make_pair(0, 0);
	for (int w = 1; w < W; ++w) {
		for (int i = 0; i < w; ++i) { // x에 w고정 -> w-1개 + y에 w고정 -> w-1개
			// dp[w][i] --> dp[w+1][i] , dp[w][w+1]
			// dp[i][w] --> dp[w+1][w] , dp[i][w+1]
			if (dp[w + 1][i] > dp[w][i] + get_dist(Ws, w, w - 1)) {
				dp[w + 1][i] = dp[w][i] + get_dist(Ws, w, w - 1);
				dp_[w + 1][i] = make_pair(w, i);
			}
			if (dp[w][w + 1] > dp[w][i] + get_dist(Ws, i - 1, w)) {
				dp[w][w + 1] = dp[w][i] + get_dist(Ws, i - 1, w);
				dp_[w][w + 1] = make_pair(w, i);
			}
			if (dp[w + 1][w] > dp[i][w] + get_dist(Ws, w, i - 1)) {
				dp[w + 1][w] = dp[i][w] + get_dist(Ws, w, i - 1);
				dp_[w + 1][w] = make_pair(i, w);
			}
			if (dp[i][w + 1] > dp[i][w] + get_dist(Ws, w - 1, w)) {
				dp[i][w + 1] = dp[i][w] + get_dist(Ws, w - 1, w);
				dp_[i][w + 1] = make_pair(i, w);
			}
		}
	}
	// W인 값들 확인.
	int answer = INT_MAX, x, y;
	for (int i = 0; i < W; ++i) {
		if (answer > dp[W][i]) {
			answer = dp[W][i];
			x = W;
			y = i;
		}
		if (answer > dp[i][W]) {
			answer = dp[i][W];
			x = i;
			y = W;
		}
	}
	vector<int> answer_list;
	for (int n = W; n >= 1; --n) {
		if (x == n) answer_list.push_back(1);
		else answer_list.push_back(2);
		pair<int, int> temp = dp_[x][y];
		x = temp.first;
		y = temp.second;
	}
	cout << answer << "\n";
	for (auto i = rbegin(answer_list); i != rend(answer_list); ++i) {
		cout << *i << "\n";
	}
	return 0;
}