#include<iostream>
int main() {
	int x, y, w, h;
	std::cin >> x >> y >> w >> h;
	int min = x; // Left
	if (min > y) min = y; // Down
	if (min > w - x) min = w - x; // Right
	if (min > h - y) min = h - y; // Up
	std::cout << min;
	return 0;
}