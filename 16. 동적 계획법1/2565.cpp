#include<vector>
#include<iostream>
#include<utility>
#include<algorithm> // min, sort
int main() {
	using std::pair;
	using std::vector;
	int N;
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	std::cin >> N;
	vector<pair<int, int>> wire(N, std::make_pair(0,0));
	for (int i = 0; i < N; ++i) {
		std::cin >> wire[i].first >> wire[i].second;
	}
	auto compare = [](pair<int, int>& a, pair<int, int>& b) {
		if (a.first <= a.second) {
			if (b.first <= b.second) return a.first < b.first;
			else return a.first < b.second;
		}
		else {
			if (b.first <= b.second) return a.second < b.first;
			else return a.second < b.second;
		}
	};
	std::sort(wire.begin(), wire.end(), compare); // 빠른 시작 점 기준으로 정렬
	vector<int> dp(N + 1, 1);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < i; ++j) {
			if (wire[j].first <= wire[j].second && wire[i].first <= wire[i].second) {
				if (wire[j].first < wire[i].first && wire[j].second < wire[i].second) {
					dp[i + 1] = dp[i + 1] > dp[j + 1] + 1 ? dp[i + 1] : dp[j + 1] + 1;
				}
			}
			else if (wire[j].first > wire[j].second && wire[i].first > wire[i].second) {
				if (wire[j].first < wire[i].first && wire[j].second < wire[i].second) {
					dp[i + 1] = dp[i + 1] > dp[j + 1] + 1 ? dp[i + 1] : dp[j + 1] + 1;
				}
			}
			else {
				if (std::min(wire[i].first, wire[i].second) > std::max(wire[j].first, wire[j].second)) {
					dp[i + 1] = dp[i + 1] > dp[j + 1] + 1 ? dp[i + 1] : dp[j + 1] + 1;
				}
			}
		}
	}
	std::cout << N - dp[N];
	return 0;
}