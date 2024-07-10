#include <iostream>
#include <string>
#include <utility>
#include <stack>

using namespace std;
using P = pair<int,int>; // (계산된 값, 마지막 index)
string str;
bool not_correct = true;
stack<char> S;

P parentheses(int);
P Bracket(int);

P parentheses(int index) { // (
	P ret;
	ret.first = 1;
	ret.second = index;
	for (int i = index; i < str.length(); ++i) {
		if (!not_correct) break;
		if (str[i] == ')') {
			ret.second = i;
			S.pop();
			break;
		}
		else if(str[i] == ']') not_correct = false;
		else if (str[i] == '(') {
			S.push('(');
			P in = parentheses(i + 1);
			if (ret.first == 1) ret.first = 2 * in.first;
			else ret.first += 2 * in.first;
			i = in.second;
		}
		else if(str[i] == '[') {
			S.push('[');
			P in = Bracket(i + 1);
			if (ret.first == 1) ret.first = 3 * in.first;
			else ret.first += 3 * in.first;
			i = in.second;
		}
	}
	return ret;
}

P Bracket(int index) { // [
	P ret;
	ret.first = 1;
	ret.second = index;
	for (int i = index; i < str.length(); ++i) {
		if (!not_correct) break;
		if (str[i] == ']') {
			ret.second = i;
			S.pop();
			break;
		}
		else if (str[i] == ')') not_correct = false;
		else if (str[i] == '(') {
			S.push('(');
			P in = parentheses(i + 1);
			if (ret.first == 1) ret.first = 2 * in.first;
			else ret.first += 2 * in.first;
			i = in.second;
		}
		else if (str[i] == '[') {
			S.push('[');
			P in = Bracket(i + 1);
			if (ret.first == 1) ret.first = 3 * in.first;
			else ret.first += 3 * in.first;
			i = in.second;
		}
	}
	return ret;
}

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	cin >> str;
	int answer = 0;
	for (int i = 0; i < str.length(); ++i) {
		if (!not_correct) break;
		if (str[i] == '(') {
			S.push('(');
			P in = parentheses(i + 1);
			answer += 2 * in.first;
			i = in.second;
		}
		else if (str[i] == '[') {
			S.push('[');
			P in = Bracket(i + 1);
			answer += 3 * in.first;
			i = in.second;
		}
		else if (str[i] == ']') not_correct = false;
		else if (str[i] == ')') not_correct = false;
	}
	if (!not_correct || !S.empty()) cout << "0\n";
	else cout << answer << '\n';
	return 0;
}