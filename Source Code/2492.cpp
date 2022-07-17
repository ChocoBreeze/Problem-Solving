// 매 간격마다 정사각형 두고 T에 대해 체크
// --> (N - K + 1) * (M - K + 1) * T (TLE)
// 접근 : https://justicehui.github.io/koi/2019/09/19/BOJ2492/
#include <iostream>
#include <vector>

using namespace std;

struct coord {
	int x;
	int y;
	coord(int x, int y) : x(x), y(y) {}
};

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int N, M, T, K;
	cin >> N >> M >> T >> K;
	vector<coord> D(T, coord(0, 0));
	for (auto& i : D) {
		cin >> i.x >> i.y;
	}
	int answer_x = 0, answer_y = 0, answer = -1;
	for (auto& i : D) {
		for (auto& j : D) {
			// 정사각형은 경계를 벗어나지 못 함.
			int start_x = i.x + K > N ? N - K : i.x;
			int start_y = j.y + K > M ? M - K : j.y;
			int count = 0;
			for (auto& k : D) {
				if (k.x >= start_x && k.x <= start_x + K && k.y >= start_y && k.y <= start_y + K) {
					++count;
				}
			}
			if (count > answer) { // 왼쪽 위의 점
				answer = count;
				answer_x = start_x;
				answer_y = start_y + K;
			}
		}
		
	}
	cout << answer_x << " " << answer_y << "\n" << answer;
	return 0;
}