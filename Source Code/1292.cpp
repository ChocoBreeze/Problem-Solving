#include <iostream>
#include <vector>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	vector<int> sequence;
	sequence.reserve(1300);
	for (int i = 1; i <= 50; ++i) {
		for (int j = 1; j <= i; ++j) {
			sequence.push_back(i);
		}
	}
	// 다 넣으면 1275개

	int A, B;
	cin >> A >> B;
	int answer{};
	for (int i = A - 1; i < B; ++i) {
		answer += sequence[i];
	}
	cout << answer << '\n';

	return 0;
}