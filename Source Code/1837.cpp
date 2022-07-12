// https://www.acmicpc.net/board/view/13891
// 많이 틀림..
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int cal_mod(string& s, int p) {
	int mod = 0;
	// a = b (mod P) (3개짜리 없어서 등호로..)
	// a x c = b x c (mod P)
	// a + c = b + c (mod P)
	for (auto& i : s) {
		mod = (mod * 10 + (i - '0')) % p;
	}
	return mod;
}

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	string P; // 10^100
	int K;
	cin >> P >> K;
	vector<bool> is_prime(K + 1, true);
	for (int i = 2; i * i <= K; ++i) {
		if (!is_prime[i]) continue;
		for (int j = i + i; j <= K ; j += i) {
			is_prime[j] = false;
		}
	}
	int answer = K + 1;
	for (int i = 2; i <= K; ++i) {
		if (!is_prime[i]) continue;
		if (cal_mod(P, i) == 0) {
			answer = i;
			break;
		}
	}
	if (answer < K) cout << "BAD " << answer;
	else cout << "GOOD";
	return 0;
}