// 2020KB, 0ms
#include <iostream>

using namespace std;

int main() {
	cout.tie(nullptr), cin.tie(nullptr), ios::sync_with_stdio(false);
	int N{}; cin >> N;
	int answer{}, bird{ 1 };
	while (N) {
		if (N < bird) {
			bird = 1;
			continue;
		}
		N -= bird;
		++bird;
		++answer;
	}
	cout << answer << '\n';
	
	return 0;
}