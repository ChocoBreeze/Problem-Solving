#include<iostream>
int main() {
	int N, new_N, count = 0,temp_N;
	std::cin >> N;
	temp_N = N;
	while(1) {
		if (N == temp_N && count!=0) break;
		if (temp_N < 10) new_N = temp_N;
		else new_N = (temp_N / 10) + (temp_N % 10);
		temp_N = (temp_N % 10) * 10 + (new_N%10);
		count++;
	}
	std::cout << count;
	return 0;
}