#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M;

void permutation(vector<int>& A, vector<int>& print) {
	if (print.size() == M) {
		for (auto& i : print) {
			cout << i << " ";
		}
		cout << "\n";
		return;
	}
	for (int i = 0; i < N; ++i) {
		print.push_back(A[i]);
		permutation(A, print);
		print.pop_back();
	}
}

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	cin >> N >> M;
	vector<int> A(N, 0);
	for (auto& i : A) {
		cin >> i;
	}
	sort(begin(A), end(A));
	vector<int> print;
	permutation(A, print);
	return 0;
}