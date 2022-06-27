#include<iostream>
int main() {
	int A, B, C, temp=0;
	while (1) {
		std::cin >> A >> B >> C;
		if (A == 0 && B == 0 && C == 0) break;
		if (A > C) [&A,&C](int temp) {temp = A; A = C; C = temp; }(temp);
		if (B > C) [&B,&C](int temp) {temp = B; B = C; C = temp; }(temp);
		if (A * A + B * B == C * C) std::cout << "right" << "\n";
		else std::cout << "wrong" << "\n";
	}
	return 0;
}