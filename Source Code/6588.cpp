// 100만까지 소수 목록 구하기
// sqrt(100만)까지만 에라토스테네스의 채 구해도 충분
#include <iostream>
#include <vector>

using namespace std;

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int n;
	vector<bool> primes(1000001, true);
	for (int i = 2; i * i <= 1000000; ++i) {
		if (!primes[i]) continue;
		for (int j = i * i; j <= 1000000; j+=i) {
			primes[j] = false;
		}
	}
	while (1) {
		cin >> n;
		if (n == 0) break;
		int a = -1, b = -1;
		for (int i = 3; i < n; ++i) {
			if (!primes[i]) continue;
			if (primes[n - i]) {
				a = i;
				b = n - i;
				break; // b - a가 가장 큰 것
			}
		}
		if (a == -1 && b == -1) cout << "Goldbach's conjecture is wrong.\n";
		else cout << n << " = " << a << " + " << b << "\n";
	}
	return 0;
}