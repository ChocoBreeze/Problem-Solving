#include <iostream>
#include <string>
#include <stack>
#include <utility>

using namespace std;

stack<int> S;
string str;

pair<int,int> open_parenthesis(int index) {
	pair<int, int> return_value;
	stack<int> S_;
	for (int i = index;; ++i) {
		if (str[i] == ')') {
			return_value.second = i;
			break;
		}
		if (str[i] == '(') {
			pair<int,int> result = open_parenthesis(i + 1);
			S_.push(result.first);
			i = result.second; // 이후 끝나고 증가됨
		}
		else {
			if (str[i] == 'H') {
				S_.push(1);
			}
			else if (str[i] == 'C') {
				S_.push(12);
			}
			else if (str[i] == 'O') {
				S_.push(16);
			}
			else { // 숫자
				int t = S_.top();
				S_.pop();
				S_.push(t * (str[i] - '0'));
			}
		}
	}
	return_value.first = 0;
	while (!S_.empty()) {
		return_value.first += S_.top();
		S_.pop();
	}
	return return_value;
}

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	
	cin >> str;
	int answer = 0;
	for (int i = 0; i < str.length();++i) {
		if (str[i] == '(') {
			pair<int, int> result = open_parenthesis(i + 1);
			S.push(result.first);
			i = result.second; // 이후 끝나고 증가됨
		}
		else {
			if (str[i] == 'H') {
				S.push(1);
			}
			else if (str[i] == 'C') {
				S.push(12);
			}
			else if (str[i] == 'O') {
				S.push(16);
			}
			else { // 숫자
				int t = S.top();
				S.pop();
				S.push(t * (str[i] - '0'));
			}
		}
	}

	while (!S.empty()) {
		answer += S.top();
		S.pop();
	}

	cout << answer;
	return 0;
}