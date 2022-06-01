#include<iostream>
int main() {
	int A, B, C, D, E, F;
	std::cin >> A >> B >> C >> D >> E >> F;
	if (A == C) std::cout << E << " ";
	else if (A == E) std::cout << C << " ";
	else std::cout << A << " ";
	if (B == D) std::cout << F;
	else if (B == F) std::cout << D;
	else std::cout << B;
	return 0;
}