#include <unordered_map>
#include <iostream>
#include <string>

using namespace std;

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	int n, max_count = -1;
	string str, answer;
	unordered_map<string, int> Map;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> str;
		Map[str]++;
		if (max_count < Map[str]) {
			max_count = Map[str];
			answer = str;
		}
		else if (max_count == Map[str]) {
			if (str.compare(answer) < 0) answer = str;
		}
	}
	cout << answer << '\n';
	return 0;
}