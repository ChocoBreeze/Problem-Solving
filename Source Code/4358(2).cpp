#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	map<string, int> m;
	string str;
	int cnt{};
	while (1) {
		getline(cin, str);
		if (cin.eof()) break;
		++cnt;
		if (m.find(str) == end(m)) {
			m.emplace(str, 1);
		}
		else m[str]++;
	}

	cout << fixed;
	cout.precision(4); // 백분율로 소수점 4째자리까지 반올림
	for (auto& [name, num] : m) {
		cout << name << ' ' << static_cast<double>(num) * 100 / cnt << '\n';
	}
	return 0;
}