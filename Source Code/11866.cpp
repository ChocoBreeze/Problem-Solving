#include<iostream>
#include<vector>
int main() {
	int N, K, index = 0;
	std::cin >> N >> K;
	std::vector<int> Q;
	for (int i = 0; i <= N; ++i) {
		Q.push_back(i);
	}
	std::cout << "<";
	while (Q.size() != 2) {
		index += K;
		if (index > Q.size() - 1) {
			index %= Q.size() - 1;
			if (index == 0) index = Q.size() - 1;
		}
		std::cout << Q.at(index) << ", ";
		Q.erase(Q.begin() + index);
		--index;
	}
	std::cout << Q.at(Q.size() - 1) << ">";
	return 0;
}