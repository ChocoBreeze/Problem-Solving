#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M;

void permutation(vector<int>& A, vector<int>& print, vector<bool>& chk) {
	if (print.size() == M) {
		for (auto& i : print) {
			cout << i << " ";
		}
		cout << "\n";
		return;
	}
	for (int i = 0; i < N; ++i) {
		if (chk[i]) continue;
		chk[i] = true;
		print.push_back(A[i]);
		permutation(A, print, chk);
		print.pop_back();
		chk[i] = false;
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
	vector<bool> chk(N, false);
	permutation(A, print, chk);
	return 0;
}