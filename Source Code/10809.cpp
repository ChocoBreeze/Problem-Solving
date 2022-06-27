#include<string>
#include<iostream>
#include<vector>

int main() {
	std::vector<int> answer(26, -1); //-1로 26개
	std::string str;
	std::cin >> str;
	for (int i = 0; i < str.length(); ++i) {
		if (answer.at(str[i]-'a') == -1) {
			answer[str[i] - 'a'] = i;
		}
	}
	for (auto i : answer) {
		std::cout << i << " ";
	}
	return 0;
}