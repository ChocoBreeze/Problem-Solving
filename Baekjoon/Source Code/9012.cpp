#include<iostream>
#include<string>
int main() {
	int T;
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	std::cin >> T;
	std::string line;
	for (int i = 0; i < T; ++i) {
		std::cin >> line;
		int cnt = 0;
		for (int j = 0; j < line.length(); ++j) {
			if (line[j] == '(') ++cnt;
			else --cnt;
			if (cnt < 0) break; // 개수만 고려하지 않고 닫힌 괄호 하나 더 많은 경우 처리하기
		}
		if (cnt != 0) std::cout << "NO\n";
		else std::cout << "YES\n";
	}
	return 0;
}