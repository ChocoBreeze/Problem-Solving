#include<iostream>
#include<vector>
#include<algorithm>

int bsearch(std::vector<int>& A, int b) {
	int start = 0, end = A.size() - 1;
	while (start <= end) {
		int middle = (start + end) / 2;
		if (A[middle] < b) start = middle + 1;
		else if (A[middle] > b) end = middle - 1;
		else return 1;
	}
	return 0;
}

int main() {
	int n, m;
	std::cin >> n;
	std::vector<int> A(n, 0);
	for (int i = 0; i < n; ++i) {
		std::cin >> A[i];
	}
	std::cin >> m;
	std::vector<int> B(m, 0);
	for (int i = 0; i < m; ++i) {
		std::cin >> B[i];
	}
	std::sort(A.begin(), A.end()); // ascending
	for (int i = 0; i < m; ++i) { // B의 원소들이 A에 있는지
		std::cout << bsearch(A, B[i]) << "\n";
	}
	return 0;
}