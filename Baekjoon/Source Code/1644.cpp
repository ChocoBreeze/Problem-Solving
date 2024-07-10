// 소수 빨리 구하기
// 투 포인터

#include<iostream>
#include<vector>

using std::cin;
using std::cout;
using std::vector;

vector<int> make_prime(int N) { // N까지 소수인 수 찾기 - 에라토스테네스의 채
	vector<int> primes;
	vector<bool> numbers(N + 1, true);
	for (int i = 2; i <= N; ++i) {
		if (!numbers[i]) continue;
		primes.push_back(i);
		for (int j = i + i; j <= N; j += i) {
			numbers[j] = false;
		}
	}
	return primes;
}

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int N, answer = 0;
	cin >> N;
	vector<int> primes = make_prime(N);
	if (!primes.empty()) {
		auto front = begin(primes), back = begin(primes);
		long long sum = primes[0];
		while (front != end(primes)) {
			if (sum >= N) {
				if (sum == N) {
					++answer;
				}
				sum -= *back;
				++back;
			}
			else {
				if (front == end(primes) - 1) break;
				++front;
				sum += *front;
			}
		}
	}
	cout << answer;
}