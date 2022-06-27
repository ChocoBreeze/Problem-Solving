#include<iostream>
int main() {
	int A, max=-1, index=0;
	for(int i=1;i<=9;i++) {
		std::cin >> A;
		if (max < A) {
			max = A;
			index = i;
		}
	}
	std::cout << max << "\n" << index;
	return 0;
}