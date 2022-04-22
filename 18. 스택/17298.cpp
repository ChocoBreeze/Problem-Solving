// 38% 시간초과
// 기존에 쌓은 값들에 대한 제거가 가능한지!
#include<iostream>
#include<stack>
#include<vector>
int main() {
	int n,max = -1;
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	std::cin >> n;
	std::vector<int> numbers(n,0);
	for (int i = 0; i < n; ++i) {
		std::cin >> numbers[i];
	}
	std::vector<int> answer(n, -1);
	std::stack<int> answer_stack;
	max = numbers[n - 1];
	for (int i = n - 2; i >= 0; --i) {
		if (numbers[i] < numbers[i + 1]) {
			answer[i] = numbers[i + 1];
			answer_stack.push(numbers[i + 1]);
		}
		else {
			if (max < numbers[i]) {
				max = numbers[i];
				answer_stack.push(numbers[i]);
			}
			else {
				while(!answer_stack.empty()){
					if (numbers[i] < answer_stack.top()) {
						answer[i] = answer_stack.top();
						break;
					}
					answer_stack.pop();
				}
			}
		}
	}
	for (auto i = answer.begin(); i != answer.end(); ++i) {
		std::cout << *i << " ";
	}
	return 0;
}