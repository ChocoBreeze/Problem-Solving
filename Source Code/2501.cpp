#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	int N, K;
	cin >> N >> K;
	vector<int> primes;
	for (int i = 1; i*i <= N; ++i) {
		if (N%i == 0) {
			primes.push_back(i);
			if(i!=N/i) primes.push_back(N / i);
		}
	}
	sort(begin(primes), end(primes));
	if (K > size(primes)) cout << "0\n";
	else cout << primes[K - 1] << '\n';

	return 0;
}