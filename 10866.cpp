#include<iostream>
#include<string>
#include<deque> 
int main() {
	int N, temp;
	std::string str;
	std::deque<int> deQ;
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	std::cin >> N; // 명령
	for (int i = 0; i < N; ++i) {
		std::cin >> str;
		if (str.compare("push_front") == 0) {
			std::cin >> temp;
			deQ.push_front(temp);
		}
		else if (str.compare("push_back") == 0) {
			std::cin >> temp;
			deQ.push_back(temp);
		}
		else if (str.compare("pop_front") == 0) {
			if (deQ.empty()) std::cout << -1 << "\n";
			else {
				std::cout << deQ.front() << "\n";
				deQ.pop_front();
			}
		}
		else if (str.compare("pop_back") == 0) {
			if (deQ.empty()) std::cout << -1 << "\n";
			else {
				std::cout << deQ.back() << "\n";
				deQ.pop_back();
			}
		}
		else if (str.compare("size") == 0) {
			std::cout << deQ.size() << "\n";
		}
		else if (str.compare("empty") == 0) {
			if (deQ.empty()) std::cout << 1 << "\n";
			else std::cout << 0 << "\n";
		}
		else if (str.compare("front") == 0) {
			if (deQ.empty()) std::cout << -1 << "\n";
			else std::cout << deQ.front() << "\n";
		}
		else if (str.compare("back") == 0) {
			if (deQ.empty()) std::cout << -1 << "\n";
			else std::cout << deQ.back() << "\n";
		}
	}
	return 0;
}