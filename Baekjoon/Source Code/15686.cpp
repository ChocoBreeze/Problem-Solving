#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;
constinit const int HOME = 1;
constinit const int CHICKEN = 2;
constinit const int INF = 1 << 30;

struct coord {
	int x, y;
	coord(int x, int y) : x(x), y(y) {}
	int distance(const coord& other) {
		return abs(x - other.x) + abs(y - other.y);
	}
};

vector<coord> chickens, homes;
vector<int> choose;
int answer;
void Backtrack(int M, int index) {
	if (static_cast<int>(choose.size()) == M) {
		int sum{};
		for (coord& home : homes) {
			int minDist{ INF };
			for (int& index : choose) {
				minDist = min(minDist, home.distance(chickens[index]));
			}
			sum += minDist;
			if (sum > answer) return;
		}
		answer = min(answer, sum);
		return;
	}
	// if(index == chickens.size())

	for (int i = index; i < static_cast<int>(chickens.size()); ++i) {
		choose.push_back(i);
		Backtrack(M, i + 1); // 바보인가?
		choose.pop_back();
	}
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	
	int N, M;
	cin >> N >> M;
	
	for (int x{}; x < N; ++x) {
		for (int y{}; y < N; ++y) {
			int in{}; cin >> in;
			if (in == CHICKEN) {
				chickens.emplace_back(x, y);
			}
			else if (in == HOME) {
				homes.emplace_back(x, y);
			}
		}
	}

	answer = INF;
	Backtrack(M, 0);
	cout << answer << '\n';

	return 0;
}