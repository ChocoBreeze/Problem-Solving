// 긴 형태 -> 짧은 형태
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	string str, temp, answer;
	cin >> str;
	istringstream iss(str);
	while (getline(iss, temp, '-')) {
		answer += temp[0];
	}
	cout << answer << '\n';
	return 0;
}