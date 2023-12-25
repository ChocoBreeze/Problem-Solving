// NM 하면 당연히 TLE구나?..
// 답 : 큐에 있는 원소들

#include <iostream>
#include <vector>

using namespace std;
constinit const int QUEUE = 0;
constinit const int MAXM = 100'010;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}; cin >> N;
	vector<int> A(N, 0), B(N,0); // i번 자료구조가 큐라면 A[i] = 0, 스택이라면 A[i] = 1
	vector<int> answer;
	answer.reserve(MAXM);
	for (int& a : A) cin >> a;
	for (int& b : B) cin >> b;
	for (int n{ N - 1 }; n >= 0; --n) {
		if (A[n] == QUEUE) answer.push_back(B[n]);
	}

	int M{}; cin >> M; // 삽입할 수열의 길이
	for (int m{}; m < M;++m) {
		int c{}; cin >> c;
		answer.push_back(c);
	}

	for (int m{}; m < M; ++m) {
		cout << answer[m] << ' ';
	}
	cout << '\n';

	return 0;
}