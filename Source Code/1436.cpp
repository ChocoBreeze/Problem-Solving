// 왜 브루트 포스인지 처음엔 이해 안 갔음
#include<iostream>
#include<string>
int main() {
	int N, cnt = 0;
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	std::cin >> N;
	std::string tmp;
	for (int i = 666;; ++i) {
		tmp = std::to_string(i);
		if (tmp.find("666") != std::string::npos) {
			++cnt;
			if (cnt == N) break;
		}
	}
	std::cout << tmp;
	return 0;
}