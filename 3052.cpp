#include<iostream>
#include<vector>
int main() {
	int A;
	std::vector<int> cnt;
	for (int i = 0; i < 10; i++) {
		std::cin >> A;
		int chk = 0;
		for (auto j = cnt.begin(); j != cnt.end(); j++) {
			if (A % 42 == *j) { chk = 1; break; }
		}
		if (chk == 0) cnt.push_back(A % 42);
	}
	std::cout << cnt.size();
	return 0;
}