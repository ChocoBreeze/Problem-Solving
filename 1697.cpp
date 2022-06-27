// 메모리 초과
// Q에 인덱스와 거리를 모두 저장하니 메모리 초과
// chk배열의 인덱스를 K로 잡으니 Index out of range
#include<iostream>
#include<queue>
#include<vector>

using std::cin;
using std::cout;
using std::queue;
using std::vector;

const int SIZE = 100005;
int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int N, K;
	cin >> N >> K;
	vector<int> chk(SIZE, -1); // 중복 체크 필요
	if (N == K) {
		cout << 0;
	}
	else {
		queue<int> Q;
		Q.push(N);
		chk[N] = 0;
		while (!Q.empty()) {
			auto a = Q.front();
			Q.pop();
			if (a + 1 == K || a - 1 == K || a * 2 == K) {
				cout << chk[a] + 1;
				break;
			}
			// 한 번 들어간 값은 바뀌지 않음 (chk)
			if (a + 1 < SIZE && chk[a + 1] == -1) {
				chk[a + 1] = chk[a] + 1;
				Q.push(a + 1);
			}
			if (0 <= a - 1 && chk[a - 1] == -1) {
				chk[a - 1] = chk[a] + 1;
				Q.push(a - 1);
			}
			if (a * 2 < SIZE && chk[a * 2] == -1) {
				chk[a * 2] = chk[a] + 1;
				Q.push(a * 2);
			}
		}
	}
	return 0;
}