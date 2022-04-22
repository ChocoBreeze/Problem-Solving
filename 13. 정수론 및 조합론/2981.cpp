// 유클리드 공식
// 많이 틀림 - 착각함 (무조건 나머지가 숫자보다 작아야 되는 줄!)
#include<iostream>
#include<vector>
#include<set>
int main()
{
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int N, min = 1000000000;
	std::cin >> N;
	std::vector<int> numbers(N, 0);
	for (int i = 0; i < N; ++i) {
		std::cin >> numbers[i];
		if (min > numbers[i]) { min = numbers[i]; numbers[i] = numbers[0]; numbers[0] = min; }
	}
	int gcd = numbers[1] - min;
	for (int i = 2; i < N; ++i) {
		int N_temp = numbers[i] - min;
		int gcd_temp = gcd;
		if (N_temp % gcd == 0) continue;
		while (1) {
			if (N_temp == 0 || gcd_temp == 0) {
				if (N_temp == 0) gcd = gcd_temp;
				else gcd = N_temp;
				break;
			}
			if (N_temp < gcd_temp) gcd_temp %= N_temp;
			else N_temp %= gcd_temp;
		}
	}
	std::set<int> answer;
	for (int i = 2; i*i <= gcd; ++i) {
		if (gcd % i == 0) {
			answer.insert(i);
			answer.insert(gcd / i);
		}
	}
	answer.insert(gcd);
	for (auto i = answer.begin(); i != answer.end(); ++i) {
		std::cout << *i << " ";
	}
	return 0;
}