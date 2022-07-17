// https://m.blog.naver.com/js568/221857286945
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
	int last = 0; // 초기값 = 될 수 없는 값
	for (int i = 0; i < N; ++i) {
		if (chk[i] || last == A[i]) continue;
		if (!print.empty() && print.back() > A[i]) continue;
		last = A[i];
		print.push_back(A[i]);
		chk[i] = true;
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