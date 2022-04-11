#include<iostream>
int main() {
	int A, B, C, Number[10] = { 0, }, multiply;
	std::cin >> A >> B >> C;
	multiply = A * B * C;
	while(1) {
		if (multiply == 0) break;
		int temp = multiply % 10;
		Number[temp]++;
		multiply /= 10;
	}
	for (int i = 0; i < 10; i++) {
		std::cout << Number[i] << "\n";
	}
	return 0;
}