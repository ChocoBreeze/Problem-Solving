/*
���� -> ����
https://m.blog.naver.com/kks227/220781557098
* 1) �ǿ����ڴ� ������ ���
* 2) �������� ���
*	������ ��� �ְų�, top�� '('�̰ų�, �̹� �����ڰ� top �����ں��� �켱������ ���� ��� => push
*	top���� �켱���� �۰ų� ������ pop �� �ٽ� 2)
* 3) '('�� push
* 4) ')'�� ��Ÿ���� '('�� ���� ������ pop�ϸ鼭 ���
* 5) �ǿ����ڰ� �� �̻� ������ pop�ϸ鼭 ��� �� ������
*/

#include <iostream>
#include <string>

using namespace std;
int CharToPriority(char& c) {
	if (c == '+' || c == '-') return 1;
	else if (c == '*' || c == '/') return 2;
	return 0; // warning ����
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	string infix; cin >> infix;
	string answer;
	string Stack;
	for (auto& l : infix) {
		// 1) �ǿ����ڴ� ������ ���
		// �ǿ����ڴ� ���ĺ� �빮�ڷ� �̷������ ���Ŀ��� �� ������ ����
		if ('A' <= l && l <= 'Z') answer.push_back(l);
		// 2) '('�� push
		else if (l == '(') Stack.push_back(l);
		// 3) ')'�� ��Ÿ���� '('�� ���� ������ pop�ϸ鼭 ���
		else if (l == ')') {
			while (!Stack.empty()) {
				char now = Stack.back(); Stack.pop_back();
				if (now == '(') break;
				answer += now;
			}
		}
		// �������� ���
		else {
			while (!Stack.empty() && Stack.back()!='(') {
				char before = Stack.back();
				int beforePriority = CharToPriority(before);
				int nowPriority = CharToPriority(l);
				if (beforePriority >= nowPriority) {
					// top���� �켱���� �۰ų� ������ pop �� �ٽ� 2)
					answer.push_back(before);
					Stack.pop_back();
				}
				else break;
			}
			// ������ ��� �ְų�, top�� '('�̰ų�, �̹� �����ڰ� top �����ں��� �켱������ ���� ��� => push
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
