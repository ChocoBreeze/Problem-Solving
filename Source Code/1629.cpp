#include<iostream>

// a^2n = a^n * a^n
// a^(2n+1) = a^n * a^n * a
// (a*b) mod c = ((a mod c) * (b mod c))mod c

long long int multiply(long long int A, long long int B, long long int C) {
	if (B == 1) return A%C;
	long long int tmp = multiply(A, B / 2, C); // 이미 C보다 작은 값을 가짐
	if (B % 2 == 0) return (tmp * tmp) % C;
	else return (((tmp * tmp) % C) * (A % C)) % C;
}
int main() {
	long long int A, B, C;
	std::cin >> A >> B >> C;
	std::cout << multiply(A, B, C);
	return 0;
}