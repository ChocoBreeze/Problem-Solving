#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);

	unordered_map<string, char> colorMap{
		{"black", '0'}, {"brown", '1'},{"red",'2'},
		{"orange",'3'},{"yellow",'4'},{"green",'5'},
		{"blue",'6'},{"violet",'7'},{"grey",'8'},{"white",'9'}
	};

	string answer;
	for (int i{}; i < 2; ++i) {
		string in; cin >> in;
		if (answer.empty() && in == "black") continue;
		answer.push_back(colorMap[in]);
	}
	string in; cin >> in;
	for (int i{}; i < (colorMap[in] - '0'); ++i) {
		if (answer.empty()) continue;
		answer.push_back('0');
	}
	if (answer.empty()) answer.push_back('0');
	cout << answer << '\n';
	
	return 0;
}