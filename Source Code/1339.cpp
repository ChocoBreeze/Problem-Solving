#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
constinit const int SIZE = 26;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}; cin >> N;
	vector<string> strs(N);
	vector<int> DAT(26, -1); // [¾ËÆÄºª] -> index·Î 

	int idx{};
	for (auto& str : strs) {
		cin >> str;
		for (auto& c : str) {
			if (DAT[c - 'A'] != -1) continue;
			DAT[c - 'A'] = idx++;
		}
	}

	vector<int> vec{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int answer{ -1 };
	do {
		int sum{};
		for (auto& str : strs) {
			int num{};
			for (auto& c : str) {
				num *= 10;
				num += vec[DAT[c-'A']];
			}
			sum += num;
		}
		answer = max(answer, sum);
		
	} while (next_permutation(begin(vec), end(vec)));
	cout << answer << '\n';

	return 0;
}