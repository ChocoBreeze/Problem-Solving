#include<iostream>
#include<string>

using namespace std;

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	string str, s;
	getline(cin, str);
	getline(cin, s);
	int answer = 0, place = 0;
	while (1) {
		place = str.find(s, place);
		if (place == string::npos) break;
		place += s.length();
		++answer;
	}
	cout << answer;
	return 0;
}