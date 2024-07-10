// https://www.acmicpc.net/board/view/15795
// nCk = n!/k!(n-k)!
// 
// 1/k!(n-k)을 구하기 위해 소수 p에 대한 k!*(n-k)!의 역원을 
// 구해주는 문제로 수정해서 해결함.
// 
// 페르마의 소정리 : a * a^(p-2) = a^(p-1) ≡ 1(mod p)
// a의 역원 = a^(p-2)

// a를 k!(n-k)!라 생각했을 때, 
// a의 역원인 a^(p-2)에 n!을 곱함으로써 nCk (mod p)를 계산 가능함.

#include<iostream>
#include<vector>
const long long int P = 1000000007;

long long int power(long long int a, long long int b) { // 신기하네
	long long int result = 1;
	while (b > 0) {
		if (b % 2 == 1) {
			result *= a;
			result %= P;
		}
		a *= a;
		a %= P;
		b /= 2;
	}
	return result;
}

int main() {
	long long int answer;
	int N, K;
	std::cin >> N >> K;
	if (N == K || K == 0) {
		answer = 1;
	}
	else {
		std::vector<long long int> factorial, inverse(N + 1, 0);
		factorial.push_back(0);
		factorial.push_back(1);
		for (int i = 2; i <= N; ++i) {
			factorial.push_back((factorial[i - 1] * i) % P);
		}
		inverse[N] = power(factorial[N], P - 2);
		for (int i = N - 1; i > 0; --i) {
			inverse[i] = (inverse[i + 1] * (i + 1)) % P;
		}
		answer = (factorial[N] * inverse[N - K]) % P;
		answer = (answer * inverse[K]) % P;
	}
	std::cout << answer;
	return 0;
}