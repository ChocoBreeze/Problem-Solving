// Kruskal로 풀려면 모든 거리를 다 구해야 하므로 prim이 적절해 보임.
#include <iostream>
#include <queue>
#include <vector>
#include <cmath>

using namespace std;

struct coord {
	double x;
	double y;
	coord(double x, double y) : x(x), y(y) {}
};

int main () {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	// pair -> first = index, second = distance from border
	auto compare = [](pair<int, int>& a, pair<int, int>& b) {
		return a.second > b.second;
	};
	priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compare)> PQ(compare); // min_heap
	vector<coord> stars(n,coord(0,0));
	for (int i = 0; i < n; ++i) {
		cin >> stars[i].x >> stars[i].y;
		if (i == 0) continue;
		double distance = (stars[0].x - stars[i].x) * (stars[0].x - stars[i].x) + (stars[0].y - stars[i].y) * (stars[0].y - stars[i].y);
		PQ.push(make_pair(i, distance));
	}
	vector<bool> chk(n, false); // 
	chk[0] = true;
	double sum = 0;
	while (!PQ.empty()) {
		auto now = PQ.top(); 
		PQ.pop();
		if (chk[now.first]) continue;
		chk[now.first] = true;
		sum += sqrt(now.second);
		for (int i = 0; i < n; ++i) {
			if (chk[i]) continue;
			double distance = (stars[now.first].x - stars[i].x) * (stars[now.first].x - stars[i].x) + (stars[now.first].y - stars[i].y) * (stars[now.first].y - stars[i].y);
			PQ.push(make_pair(i, distance));
		}
	}
	cout << fixed;
	cout.precision(2);
	cout << sum << "\n";
	return 0;
}
