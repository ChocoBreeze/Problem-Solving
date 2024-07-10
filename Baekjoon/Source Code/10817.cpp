#include<iostream>
int main() {
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int A, B, C, temp;
	std::cin >> A >> B >> C;
	if (A < B) { temp = A; A = B; B = temp; }
	if (B < C) { temp = B; B = C; C = B; }
	if (A < B) { temp = A; A = B; B = temp; }
	std::cout << B;
	return 0;
}