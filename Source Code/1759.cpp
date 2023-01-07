#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int L, C; // 3 <= L <= C <=15
void make_pw(vector<char>& chars, string str) {
	if (str.length() == L) {
		int vowel = 0;
		for (auto& c : str) {
			if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') ++vowel;
		}
		if(vowel>0 && vowel < L - 1) cout << str << '\n';
		return;
	}
	for (int i = 0; i < C; ++i) {
		if (str.empty() || str.back() < chars[i]) {
			make_pw(chars, str + chars[i]); // 현재 문자 추가
		}
	}
}

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	cin >> L >> C;
	vector<char> chars(C, '0');
	for (auto& c : chars) {
		cin >> c;
	}
	sort(begin(chars), end(chars)); // a c i s t w

	make_pw(chars, "");

	return 0;
}