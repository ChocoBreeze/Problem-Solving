// 기존 값 누적. (기존 합에 새로운 값을 더했을 때 양수이고 기존 합이 양수인 경우)
#include<iostream>
#include<vector> 

int main() 
{
	int N, max;
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	std::cin >> N;
	std::vector<int> number(N,0);
	for (int i = 0; i < N; ++i) {
		std::cin >> number[i];
	}
	max = number[0];
	for (int i = 1; i < N; ++i) {
		if (number[i] + number[i - 1] > 0 && number[i - 1] > 0) number[i] = number[i] + number[i - 1];
		if (max < number[i]) max = number[i];
	}
	std::cout << max;
	return 0;
}