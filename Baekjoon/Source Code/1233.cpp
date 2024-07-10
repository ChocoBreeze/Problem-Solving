#include <iostream>
#include <algorithm>
#include <array>

using namespace std;
constinit const int SIZE = 90; // 80±îÁö

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int A, B, C;
	cin >> A >> B >> C;
	array<int, SIZE> arr{};
	int answer{}, maxCount{};
	for (int a{ 1 }; a <= A; ++a) {
		for (int b{ 1 }; b <= B; ++b) {
			for (int c{ 1 }; c <= C; ++c) {
				arr[a + b + c]++;
				if (maxCount < arr[a + b + c]) {
					maxCount = arr[a + b + c];
					answer = a + b + c;
				}
				else if (maxCount == arr[a + b + c]) {
					answer = min(answer, a + b + c);
				}
			}
		}
	}
	cout << answer << '\n';
	return 0;
}