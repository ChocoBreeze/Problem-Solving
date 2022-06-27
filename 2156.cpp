// 점화식 세우기
#include<iostream>
#include<vector>

int main() {
	int N;
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	std::cin >> N; // 1<=N<=10000
	std::vector<int> wine(N + 1,0);
	for (int i = 1; i <= N; ++i) {
		std::cin >> wine[i];
	}
	std::vector<int> wine_sum(N + 1, 0);
	wine_sum[1] = wine[1];
	wine_sum[2] = wine[1] + wine[2] > wine[2] ? wine[1] + wine[2] : wine[2];
	for (int i = 3; i <= N; ++i) {
		// i번째 선택
		int tmp1;
		tmp1 = wine_sum[i - 3] + wine[i - 1] > wine_sum[i - 2] ? wine_sum[i - 3] + wine[i - 1] : wine_sum[i-2];
		tmp1 += wine[i];

		// i번째 선택 x
		wine_sum[i] = tmp1 > wine_sum[i - 1] ? tmp1 : wine_sum[i - 1];
	}
	int result = wine_sum[N - 1] > wine_sum[N] ? wine_sum[N - 1] : wine_sum[N];
	std::cout << result;
	return 0;
}