#include<queue>
#include<iostream>
int main() {
	int N;
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	std::cin >> N;
	std::queue<int> Q;
	for (int i = 0; i < N; ++i) {
		Q.push(i + 1);
	}
	while (Q.size()!=1) {
		// 버리기
		Q.pop();
		// 맨 밑으로 이동
		Q.push(Q.front());
		Q.pop();
	}
	std::cout << Q.front();
	return 0;
}