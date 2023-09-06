/*
모든 탑의 레이저 송신기는 레이저 신호를 지표면과 평행하게 수평 직선의 왼쪽 방향으로 발사하고, 
탑의 기둥 모두에는 레이저 신호를 수신하는 장치가 설치되어 있다. 
하나의 탑에서 발사된 레이저 신호는 가장 먼저 만나는 단 하나의 탑에서만 수신이 가능하다.

각각의 탑에서 발사한 레이저 신호를 어느 탑에서 수신하는지를 알아내는 프로그램을 작성
*/

#include <iostream>
#include <vector>
#include <stack>

using namespace std;
using pii = pair<int, int>; // index, height
constinit const int INF = 1 << 30;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int N; cin >> N;
	stack<pii> S;
	S.emplace(0, INF);
	for (int n{1}; n <= N; ++n) {
		int h; cin >> h;
		while (!S.empty()) {
			if (S.top().second > h) break;
			S.pop();
		}
		cout << S.top().first << ' ';
		S.emplace(n, h);
	}

	return 0;
}