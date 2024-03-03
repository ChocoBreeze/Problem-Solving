// 2024KB, 0ms
#include <iostream>
#include <string>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	string str; cin >> str;
	int strLen = static_cast<int>(str.length());

	string answer;
	int s{}, e{};
	bool chk{};
	while (1) {
		e = static_cast<int>(str.find('.', s));
		string temp = str.substr(s, e - s); // X로 구성된 애들
		int l = static_cast<int>(temp.length());
		if (l & 1) { // 길이가 홀수면 덮을 수 없음.
			chk = true;
			break;
		}
		for (int i{}; i < l / 4; ++i) answer += "AAAA";
		for (int i{}; i < l % 4 / 2; ++i) answer += "BB";
		if (e == string::npos) break; // 더 이상 문자 존재하지 않음.
		for (; e < strLen; ++e) { // . 이동
			if (str[e] != '.') break;
			answer.push_back('.');
		}
		if (e == strLen) break; // 끝 도달한 경우
		s = e;
	}
	if (chk) cout << "-1\n";
	else cout << answer << '\n';

	return 0;
}