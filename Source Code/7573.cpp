#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct coord {
	int x;
	int y;
	coord(int x, int y) : x(x), y(y) {}
};

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int N, I, M;
	cin >> N >> I >> M;
	vector<coord> fishes(M,coord(0,0));
	for (auto& i : fishes) {
		cin >> i.x >> i.y;
	}
	int answer = 0;
	for (auto& i : fishes) {
		for (auto& j : fishes) {
			int sx, sy;
			for (int k = 1; k < I / 2; ++k) { // 그물 길이
				sx = i.x + k > N ? N - k : i.x;
				sy = j.y + (I / 2 - k) > N ? N - (I / 2 - k) : j.y;
				int count = 0;
				for (auto& m : fishes) {
					if (m.x >= sx && m.x <= sx + k && m.y >= sy && m.y <= sy + (I / 2 - k)) {
						++count;
					}
				}
				answer = max(answer, count);
			}
		}
	}
	cout << answer;

	return 0;
}