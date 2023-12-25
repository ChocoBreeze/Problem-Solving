// Convex Hull ¾øÀÌ..
// https://burningfalls.github.io/algorithm/boj-25308/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
constinit const int SIZE = 8;
// constinit const double rootTwo = sqrt(2);
// constexpr since C++26
const double rootTwo = sqrt(2);

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	vector<int> lengths(SIZE, 0);
	for (int& l : lengths) cin >> l;

	vector<int> indeces{ 0,1,2,3,4,5,6,7 };

	int answer{};
	do {
		int cnt{};
		for (int i{}; i < SIZE; ++i) {
			if (lengths[indeces[i]] * lengths[indeces[(i + 2) % SIZE]] * rootTwo <= (lengths[indeces[i]] + lengths[indeces[(i + 2) % SIZE]]) * lengths[indeces[(i + 1) % SIZE]]) ++cnt;
		}
		if (cnt == SIZE) ++answer;
	} while (next_permutation(begin(indeces), end(indeces)));

	cout << answer << '\n';
	return 0;
}