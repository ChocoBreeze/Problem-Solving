#include<iostream>
int main() {
	int N;
	int x1, y1, r1, x2, y2, r2;
	std::cin >> N;
	for (int i = 0; i < N; i++) {
		std::cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;
		int dist= (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
		int r_dist = (r1 - r2) * (r1 - r2);
		int r_sum  = (r1 + r2) * (r1 + r2);
		if (x1 == x2 && y1 == y2 && r1 == r2) std::cout << -1 << "\n";
		else if (dist == r_sum || dist == r_dist) std::cout << 1 << "\n";
		else if (dist > r_sum || dist < r_dist) std::cout << 0 << "\n";
		else std::cout << 2 << "\n";
	}
	return 0;
}