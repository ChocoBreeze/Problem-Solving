#include<iostream>
#include<string>
#include<algorithm>

int main() {
	std::string A, B;
	std::cin >> A >> B; 
	std::reverse(A.begin(), A.end());
	std::reverse(B.begin(), B.end());
	for (int i = 0; i < A.length(); ++i) {
		if (A[i] > B[i]) {
			std::cout << A; break;
		}
		else if (A[i] < B[i]) {
			std::cout << B;
			break;
		}
	}
	return 0;
}