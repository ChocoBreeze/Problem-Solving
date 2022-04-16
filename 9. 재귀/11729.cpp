#include<iostream>
#include<cmath>
void hanoi(int n, int start, int waypoint, int goal) {
	if (n > 0) {
		hanoi(n - 1, start, goal, waypoint);		// n - 1개를 1에서 2경유해서 3으로
		std::cout << start << " " << goal << "\n";
		hanoi(n - 1, waypoint, start, goal);		// n - 1개를 2에서 1경유해서 3으로
	}
}

int main() {
	int n;
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	std::cin >> n;
	std::cout << static_cast<int>(std::pow(2, n) - 1) << "\n";
	hanoi(n, 1, 2, 3);
	return 0;
}