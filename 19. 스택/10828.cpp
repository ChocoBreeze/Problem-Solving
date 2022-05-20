#include<iostream>
#include<stack>
#include<string>
int main() {
	int N, a;
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	std::cin >> N;
	std::string command;
	std::stack<int> stack_;
	for (int i = 0; i < N; ++i) {
		std::cin >> command;
		if (command.compare("push") == 0) {
			std::cin >> a;
			stack_.push(a);
		}
		else if (command.compare("pop") == 0) {
			if (stack_.empty()) std::cout << -1 << "\n";
			else {
				std::cout << stack_.top() << "\n";
				stack_.pop();
			}
		}
		else if (command.compare("size") == 0) std::cout << stack_.size() << "\n";
		else if (command.compare("empty") == 0) {
			if (stack_.empty()) std::cout << 1 << "\n";
			else std::cout << 0 << "\n";
		}
		else if (command.compare("top") == 0) {
			if (stack_.empty()) std::cout << -1 << "\n";
			else std::cout << stack_.top() << "\n";
		}
	}
	return 0;
}