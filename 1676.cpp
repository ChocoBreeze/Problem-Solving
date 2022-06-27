#include<iostream>
#include<vector>

int main() {
	int N;
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	std::vector<int> count(2, 0); // 2, 5
	std::cin >> N;
	for (int i = 2; i <= N; ++i) {
		int temp = i;
		while (temp%2==0 || temp%5==0) {
			if (temp % 2 == 0) { temp /= 2; count[0]++; }
			else if (temp % 5 == 0) {temp /= 5; count[1]++;	}
		}
	}
	if (count[0] < count[1]) std::cout << count[0];
	else std::cout << count[1];
	return 0;
}