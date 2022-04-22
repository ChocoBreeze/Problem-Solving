#include<iostream>
#include<string>
#include<stack>
int main() {
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	std::string line;
	while(1) {
		while (line.compare("") == 0) {
			std::getline(std::cin, line);
		}
		if (line.compare(".") == 0) break;
		std::stack<char> PS;
		for (int j = 0; j < line.length(); ++j) {
			if (line[j] == '(' || line[j] == ')' || line[j] == '[' || line[j] == ']') {
				if (line[j] == '(' || line[j] == '[') PS.push(line[j]);
				else if (line[j] == ')') {
					if (PS.empty() || PS.top() != '(') {
						PS.push(')');
						break;
					}
					else PS.pop();
				}
				else if (line[j] == ']') {
					if (PS.empty() || PS.top() != '[') {
						PS.push(']');
						break;
					}
					else PS.pop();
				}
			}
		}
		if (PS.empty()) std::cout << "yes\n";
		else std::cout << "no\n";
		line.clear();
	}
	return 0;
}