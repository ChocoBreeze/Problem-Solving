#include<iostream>
#include<unordered_set> // 정렬 필요 없다 판단

using std::cin;
using std::cout;
using std::unordered_set;

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int N, M, tmp;
	unordered_set<int> A;
	unordered_set<int> B;
	cin >> N >> M;
	for (int i = 0; i < N; ++i) {
		cin >> tmp;
		A.insert(tmp);
	}
	for (int i = 0; i < M; ++i) {
		cin >> tmp;
		if (A.find(tmp) != A.end()) { // 교집합의 원소인 tmp
			A.erase(tmp);	// A에서 제거
			continue;		// B에는 추가x
		}
		B.insert(tmp);
	}
	cout << A.size() + B.size();
	return 0;
}