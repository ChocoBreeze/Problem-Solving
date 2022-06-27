#include<queue>
#include<iostream>
#include<string>
int main() {
	int n, a;
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	std::cin >> n;
	std::string str;
	std::queue<int> Q;
	for (int i = 0; i < n; ++i) {
		std::cin >> str;
		if (str.compare("push") == 0) {
			std::cin >> a;
			Q.push(a);
		}
		else if (str.compare("pop") == 0) {
			if (Q.empty()) std::cout << -1 << "\n";
			else {
				std::cout << Q.front() << "\n";
				Q.pop();
			}
		}
		else if (str.compare("size") == 0) {
			std::cout << Q.size() << "\n";
		}
		else if (str.compare("empty") == 0) {
			if (Q.empty()) std::cout << 1 << "\n";
			else std::cout << 0 << "\n";
		}
		else if (str.compare("front") == 0) {
			if (Q.empty()) std::cout << -1 << "\n";
			else {
				std::cout << Q.front() << "\n";
			}
		}
		else if (str.compare("back") == 0) {
			if (Q.empty()) std::cout << -1 << "\n";
			else {
				std::cout << Q.back() << "\n";
			}
		}
	}
	return 0;
}