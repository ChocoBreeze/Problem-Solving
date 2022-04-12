#include<iostream>
void check_number(bool* check, int index) {
	while (1) {
		if (index >= 1000) index = index + index / 1000 + index / 100 % 10 + index / 10 % 10 + index % 10;
		else if (index >= 100) index = index + index / 100 + index / 10 % 10 + index % 10;
		else if (index >= 10) index = index + index / 10 + index % 10;
		else index = index + index;
		if (index > 10000) break;
		check[index] = false;
	}
}

int main() {
	bool* check = new bool[10001];
	for (int i = 1; i <= 10000; i++) {
		check[i] = true;
	}
	for (int i = 1; i <= 10000; i++) {
		check_number(check, i);
	}
	for (int i = 1; i <= 10000; i++) {
		if (check[i]) std::cout << i << std::endl;
	}
	return 0;
}