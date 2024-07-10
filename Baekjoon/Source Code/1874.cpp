#include<iostream>
#include<vector>
#include<stack>
int main() {
	int n;
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	std::cin >> n;
	std::vector<int> numbers(n,0);
	std::stack<int> stack_;
	for (int i = 0; i < n; ++i) {
		std::cin >> numbers[i];
	}
	int index = 0;
	std::vector<char> answer;
	for (int i = 1; i <= n; ++i) {
		stack_.push(i);
		answer.push_back('+');
		while (!stack_.empty() && stack_.top() == numbers[index]) {
			++index;
			answer.push_back('-');
			stack_.pop();
		}
	}
	if (!stack_.empty()) std::cout << "NO";
	else {
		for (auto i = answer.begin(); i != answer.end(); ++i) {
			std::cout << *i << "\n";
		}
	}
	return 0;
}