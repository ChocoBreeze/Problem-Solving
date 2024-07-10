#include<iostream>
#include<cstring> // strlen

using namespace std;

int answer = 0;

int recursion(const char* s, int l, int r) {
	++answer;
	if (l >= r) return 1;
	else if (s[l] != s[r]) return 0;
	else return recursion(s, l + 1, r - 1);
}

int isPalindrome(const char* s) {
	return recursion(s, 0, static_cast<int>(strlen(s) - 1));
}

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	int T;
	cin >> T;
	char *s;
	s = new char[1001];
	for (int t = 0; t < T; ++t) {
		cin >> s;
		answer = 0;
		cout << isPalindrome(s) << " " << answer << "\n";
	}
	delete[] s;
	return 0;
}