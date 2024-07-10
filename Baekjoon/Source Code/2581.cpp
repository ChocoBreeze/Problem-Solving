#include<iostream>
int main() {
	int M,N,sum=0,min=-1;
	std::cin >> M >> N;
	for (int i = M; i <= N; i++) {
		if (i==1 || (i % 2 == 0 && i != 2)) continue;
		else {
			int chk = 0;
			for (int j = 3; j < i - 1; j+=2) {
				if (i % j == 0) {
					chk = 1;
					break;
				}
			}
			if (sum == 0 && chk == 0) min = i;
			if (chk == 0) sum+=i;
			
		}
	}
	if (min == -1) std::cout << -1;
	else std::cout << sum << std::endl << min;
	return 0;
}