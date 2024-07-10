#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <ranges>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	string in; cin >> in;
	// ������ �ô� 01���� 12, ���� 00���� 59, �ʴ� 00���� 59�� ��Ÿ����.
	istringstream iss(in);
	string temp;
	vector<string> times;
	while (getline(iss, temp, ':')) {
		times.push_back(temp);
	}

	vector<int> vec;
	for (int i : std::views::iota(0) | std::views::take(3)) vec.push_back(i);
	int answer{};
	do {
		int hour = stoi(times[vec[0]]);
		int minute = stoi(times[vec[1]]);
		int second = stoi(times[vec[2]]);
		if (1 <= hour && hour <= 12) {
			if (0 <= minute && minute <= 59) {
				if (0 <= second && second <= 59) {
					++answer;
				}
			}
		}

	} while (next_permutation(begin(vec), end(vec)));
	cout << answer << '\n';

	return 0;
}