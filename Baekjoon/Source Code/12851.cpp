// 간선의 가중치가 모두 동일하므로 bfs로 풀어도 무방함
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
	int N, K, time = SIZE, cnt = 1;
	cin >> N >> K;
	vector<int> chk(SIZE, SIZE); // 중복 체크 필요 + 거리 저장
	if (N == K) time = 0;
	else {
		queue<int> Q;
		Q.push(N);
		chk[N] = 0;
		while (!Q.empty()) {
			auto a = Q.front();
			Q.pop();
			if (chk[a] > time) continue; // 볼 필요 없음
			if (a + 1 < SIZE && chk[a + 1] >= chk[a] + 1) {
				chk[a + 1] = chk[a] + 1;
				Q.push(a + 1);
				if (a + 1 == K) {
					if (chk[a + 1] < time) {
						time = chk[a + 1];
						cnt = 1;
					}
					else if (chk[a + 1] == time) ++cnt;
				}
			}
			if (0 <= a - 1 && chk[a - 1] >= chk[a] + 1) {
				chk[a - 1] = chk[a] + 1;
				Q.push(a - 1);
				if (a - 1 == K) {
					if (chk[a - 1] < time) {
						time = chk[a - 1];
						cnt = 1;
					}
					else if (chk[a - 1] == time) ++cnt;
				}
			}
			if (a * 2 < SIZE && chk[a * 2] >= chk[a] + 1) {
				chk[a * 2] = chk[a] + 1;
				Q.push(a * 2);
				if (a * 2 == K) {
					if (chk[a * 2] < time) {
						time = chk[a * 2];
						cnt = 1;
					}
					else if (chk[a * 2] == time) ++cnt;
				}
			}
		}
	}
	cout << time << "\n" << cnt;
	return 0;
}