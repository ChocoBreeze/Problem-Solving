#include<iostream>
#include<vector>
#include<utility> // pair
#include<algorithm>
using std::cin;
using std::cout;
using std::vector;
using std::pair;
using std::for_each;
int main() {
	int N, x, y, index = 0;
	vector<pair<int, int>> list;
	cin >> N;
	for (int i = 0; i < N; ++i) {
		cin >> x >> y;
		list.push_back(std::make_pair(x, y));
	}
	vector<int> answer(N);
	for (auto i = list.begin(); i != list.end(); ++i, ++index) {
		for (auto j = list.begin(); j != list.end(); ++j) {
			if (i->first < j->first && i->second < j->second) {
				answer[index]++;
			}
		}
	}
	for_each(answer.begin(), answer.end(), [](const int& n) {std::cout << n + 1 << " "; });
	return 0;
}