/*
중위 -> 후위
https://m.blog.naver.com/kks227/220781557098
* 1) 피연산자는 무조건 출력
* 2) 연산자인 경우
*	스택이 비어 있거나, top이 '('이거나, 이번 연산자가 top 연산자보다 우선순위가 높을 경우 => push
*	top보다 우선순위 작거나 같으면 pop 후 다시 2)
* 3) '('는 push
* 4) ')'가 나타나면 '('를 만날 때까지 pop하면서 출력
* 5) 피연산자가 더 이상 없으면 pop하면서 출력 빌 때까지
*/

#include <iostream>
#include <string>

using namespace std;
int CharToPriority(char& c) {
	if (c == '+' || c == '-') return 1;
	else if (c == '*' || c == '/') return 2;
	return 0; // warning 제거
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	string infix; cin >> infix;
	string answer;
	string Stack;
	for (auto& l : infix) {
		// 1) 피연산자는 무조건 출력
		// 피연산자는 알파벳 대문자로 이루어지며 수식에서 한 번씩만 등장
		if ('A' <= l && l <= 'Z') answer.push_back(l);
		// 2) '('는 push
		else if (l == '(') Stack.push_back(l);
		// 3) ')'가 나타나면 '('를 만날 때까지 pop하면서 출력
		else if (l == ')') {
			while (!Stack.empty()) {
				char now = Stack.back(); Stack.pop_back();
				if (now == '(') break;
				answer += now;
			}
		}
		// 연산자인 경우
		else {
			while (!Stack.empty() && Stack.back()!='(') {
				char before = Stack.back();
				int beforePriority = CharToPriority(before);
				int nowPriority = CharToPriority(l);
				if (beforePriority >= nowPriority) {
					// top보다 우선순위 작거나 같으면 pop 후 다시 2)
					answer.push_back(before);
					Stack.pop_back();
				}
				else break;
			}
			// 스택이 비어 있거나, top이 '('이거나, 이번 연산자가 top 연산자보다 우선순위가 높을 경우 => push
			Stack.push_back(l);
		}
	}

	while (!Stack.empty()) {
		char now = Stack.back(); Stack.pop_back();
		answer.push_back(now);
	}

	cout << answer << '\n';

	return 0;
}
