#include<iostream>
using std::cin;
using std::cout;
int main() {
	int N, sum, temp, chk = 0;
	cin >> N;
	for (int i = 0; i < N; ++i) {
		sum = 0;
		temp = i;
		while (temp) {
			sum += temp % 10;
			temp /= 10;
		}
		if (sum + i == N) {
			cout << i;
			chk = 1;
			break;
		}
	}
	if (chk == 0) cout << 0;
	return 0;
}