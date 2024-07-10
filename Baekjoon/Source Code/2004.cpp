// 약수 개수 구하는 색다른 방법
// 시간초과 주의
#include<iostream>
#include<vector>

unsigned long long number2(unsigned long long n) {
	unsigned long long cnt = 0;
	for (unsigned long long int i = 2; i <= n; i *= 2) {
		cnt += n / i;
	}
	return cnt;
}

unsigned long long number5(unsigned long long n) {
	unsigned long long cnt = 0;
	for (unsigned long long int i = 5; i <= n; i *= 5) {
		cnt += n / i;
	}
	return cnt;
}


int main() {
	unsigned long long int n, m, temp;
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	std::vector<unsigned long long int> count_num(2, 0); 
	std::vector<unsigned long long int> count_denum(2, 0);
	std::cin >> n >> m;
	// 2와 5의 개수를 구하는 다른 방법!
	count_num[0] = number2(n);
	count_num[1] = number5(n);
	count_denum[0] = number2(m) + number2(n - m);
	count_denum[1] = number5(m) + number5(n - m);

	if (count_num[0] - count_denum[0] > count_num[1] - count_denum[1]) std::cout << count_num[1] - count_denum[1];
	else std::cout << count_num[0] - count_denum[0];
	return 0;
}