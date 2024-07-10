// 아홉 개의 수 중 합이 100이 되는 일곱 개의 수를 찾으시오
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	vector<int> numbers(9, 0);
	int sum{};
	for (int& n : numbers) {
		cin >> n;
		sum += n;
	}

	[&numbers, &sum]() -> void {
		for (int i{}; i < 9; ++i) {
			for (int j = i + 1; j < 9; ++j) {
				if (sum - numbers[i] - numbers[j] == 100) {
					for (int k{}; k < 9; ++k) {
						if (k == i || k == j) continue;
						cout << numbers[k] << '\n';
					}
					return;
				}
			}
		}
	} ();

	return 0;
}