//https://www.acmicpc.net/board/view/8301
#include<iostream>
#include<vector>
#include<algorithm>
int main() {
	long long int N, C, max = 2; // N(2~200000), C(2~N)
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	std::cin >> N >> C;
	std::vector<int> wifi(N, 0);
	for (int i = 0; i < N; ++i) {
		std::cin >> wifi[i];
		if (max < wifi[i]) max = wifi[i];
	}
	std::sort(wifi.begin(), wifi.end());
	long long int start = 1, end = max, mid = 0;
	// mid으로 만들 수 있는 wifi 구성이 가능한가?
	while (start < end) {
		mid = start + (end - start) / 2;
		long long int cnt = 0, last_choice = wifi[0];
		for (int i = 1; i < N; ++i) {
			if (wifi[i] - last_choice >= mid) {
				last_choice = wifi[i];
				cnt++;
			}
		}
		if (cnt < C - 1) end = mid;
		else start = mid + 1;
	}
	std::cout << start - 1;
	return 0;
}