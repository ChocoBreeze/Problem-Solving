#include<iostream>
#include<vector>
#include<algorithm>
int main() {
	int N, r, g, b;
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	std::cin >> N;
	std::vector<int> price(3, 0);
	std::cin >> price[0] >> price[1] >> price[2];
	for (int i = 1; i < N; ++i) {
		std::cin >> r >> g >> b;
		std::vector<int> price_temp(3, 0);
		price_temp[0] = (price[1] + r < price[2] + r) ? price[1] + r : price[2] + r;
		price_temp[1] = (price[0] + g < price[2] + g) ? price[0] + g : price[2] + g;
		price_temp[2] = (price[0] + b < price[1] + b) ? price[0] + b : price[1] + b;
		price = std::move(price_temp);
	}
	// auto result = std::max_element(price.begin(), price.end());
	std::cout << *std::min_element(price.begin(), price.end());
	return 0;
}