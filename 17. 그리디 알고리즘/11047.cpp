#include<iostream>
#include<vector> 
int main() 
{
	int N, K;
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	std::cin >> N >> K;
	std::vector<int> coins(N,0);
	for (int i = 0; i < N; ++i) {
		std::cin >> coins[i];
	}
	int count = 0;
	for (int i = N - 1; i >= 0; --i) {
		if (K / coins[i] != 0) {
			count += K / coins[i];
			K %= coins[i];
		}
	}
	std::cout << count;
	return 0;
}