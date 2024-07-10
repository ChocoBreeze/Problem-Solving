// 간단하게 생각하기..
#include <iostream>

using namespace std;

int arr[101][101]{};

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	int N;
	cin >> N;

	for (int i = 0; i < N; ++i) {
		int s, e;
		cin >> s >> e;
		for (int j = s; j < s + 10; ++j) {
			for (int k = e; k < e + 10; ++k) {
				arr[j][k] = 1;
			}
		}
	}
	int sum = 0;
	for (int i = 0; i < 101; ++i) {
		for (int j = 0; j < 101; ++j) {
			sum += arr[i][j];
		}
	}
	
	cout << sum << '\n';

	return 0;
}