/*
* (A+B) mod C = (A mod C + B mod C) mod C
* (A*B) mod C = (A mod C * B mod C) mod C
123 -> 123456
123456 mod C
= (123 * 1000 + 456) mod C = (123 * 1000 mod C + 456 mod C) mod C
= ((123 mod C * 1000 mod C) mod C + 456 mod C) mod C
*/
// 28932KB, 696ms

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <numeric> // accumulate

using namespace std;
using ll = long long;


ll GCD(ll a, ll b) {
	if (b == 0) return a;
	return GCD(b, a % b);
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}; cin >> N;
	vector<string> numbers(N);
	vector<ll> remainNum(N), remain10s(N); // numbers[i] % K, 10 ^ (numbers[i]의 length) % K
	for (string& num : numbers) cin >> num;
	int K{}; cin >> K;

	// dp[표현 가능 수][표현한 수를 K로 나는 나머지] : 가 나올 수 있는 수 개수
	const int SIZE = 1 << N;
	vector dp(SIZE, vector<ll>(K, 0));
	for (int n{}; n < N; ++n) {
		ll r{}, r10{ 1 };
		for (auto& c : numbers[n]) {
			r *= 10, r %= K;
			r += (c - '0'), r %= K;
			r10 *= 10, r10 %= K;
		}
		dp[(1LL << n)][r]++;
		remainNum[n] = r;
		remain10s[n] = r10;
	}

	for (int s{ 1 }; s < SIZE; ++s) {
		for (int n{}; n < N; ++n) {
			if (s & (1 << n)) continue; // 이미 포함
			for (int r{}; r < K; ++r) { // 나올 수 있는 나머지
				if (dp[s][r] == 0) continue;
				ll newR{ ((r % K * remain10s[n] % K) % K + remainNum[n] % K) % K }; // r * remain10s[n] + remainNum[n]
				dp[s | (1LL << n)][newR] += dp[s][r];
			}
		}
	}
	if (dp[SIZE - 1][0] == 0) {
		cout << "0/1\n";
	}
	else {
		ll p = dp[SIZE - 1][0];
		ll q{ accumulate(begin(dp[SIZE - 1]), end(dp[SIZE - 1]), 0LL) };
		ll gcd = GCD(q, p);
		cout << p / gcd << "/" << q / gcd << '\n';
	}

	return 0;
}