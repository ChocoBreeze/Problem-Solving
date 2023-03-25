#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	while (1) {
		int N, sum{1};
		cin >> N;
		if (N == -1) break;
		vector<int> primes{ 1 };
		for (int i = 2; i*i <= N; ++i) {
			if (N%i == 0) {
				sum += i;
				primes.push_back(i);
				if (i != N / i) {
					sum += (N / i);
					primes.push_back(N / i);
				}
			}
		}
		if (N == sum) {
			cout << N << " = " << primes[0] << ' ';
			sort(begin(primes), end(primes));
			for (int i = 1; i < primes.size();++i) {
				cout << "+ " << primes[i] << ' ';
			}
		}
		else {
			cout << N << " is NOT perfect.";
		}
		cout << '\n';
	}
	

	return 0;
}