#include<iostream>
#include<string>
#include<unordered_set> // 정렬 필요 없다 판단

using std::string;
using std::cin;
using std::cout;
using std::unordered_set;

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	string str;
	cin >> str;
	int N = str.length();
	unordered_set<string> substr;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N - i; ++j) {
			// 알아서 중복 제거
			substr.insert(str.substr(j, i + 1));
		}
	}
	cout << substr.size();
	return 0;
}