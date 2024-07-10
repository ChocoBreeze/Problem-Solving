#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	unordered_map<string, int> um;
	string str;
	int cnt{};
	while (1) {
		getline(cin, str);
		if (cin.eof()) break;
		++cnt;
		if (um.find(str) == end(um)) {
			um.emplace(str, 1);
		}
		else um[str]++;
	}

	vector<pair<string, int>> vec(begin(um), end(um));
	sort(begin(vec), end(vec), [](const pair<string, int>& p1, const pair<string, int>& p2) {
		return p1.first < p2.first;
	});

	cout << fixed;
	cout.precision(4); // ������� �Ҽ��� 4°�ڸ����� �ݿø�
	for (auto& [name, num] : vec) {
		cout << name << ' ' << static_cast<double>(num) * 100 / cnt << '\n';
	}
	return 0;
}