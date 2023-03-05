// https://www.acmicpc.net/blog/view/25
// 10만개 -> O(NlgN) 필요
// sweeping
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>

using namespace std;

struct coord {
	int x, y;
	coord(int x, int y) : x(x), y(y) {}
	bool operator<(const coord& other) const { // set에서 쓰려면 필요(const 키워드 마지막에 필요)
		if (y == other.y) return x < other.x;
		else return y < other.y;
	}
};

inline int dist(const coord& a, const coord& b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	int N;
	cin >> N;
	vector<coord> vec(N, coord(0, 0));
	for (coord& i : vec) {
		cin >> i.x >> i.y;
	}
	auto compare_X = [](const coord& a, const coord& b) {
		return a.x < b.x;
	};

	sort(begin(vec), end(vec), compare_X);
	
	set<coord> candidate{ vec[0], vec[1] };
	int ans = dist(vec[0], vec[1]), start = 0;
	for (int i = 2; i < N; ++i) { 
		coord& now = vec[i];
		while (start < i) {
			auto& p = vec[start];
			int x = now.x - p.x;
			if (x * x > ans) {
				candidate.erase(p);
				++start;
			}
			else {
				break;
			}
		}

		// 마찬가지로 y값에 대해서도 root(ans) 미만인 후보점들 뽑기
		int d = (int)sqrt((double)ans) + 1; // 소수 부분으로 인해 영향을 받을 수 있으니 각 bound마다 범위를 1씩 더 넉넉하게 주기.
		auto lower = candidate.lower_bound(coord(-100000, now.y - d));
		auto upper = candidate.upper_bound(coord(100000, now.y + d));

		for (auto& it = lower; it != upper; ++it) {
			ans = min(ans, dist(now, *it));
		}
		candidate.insert(now);
		
	}
	cout << ans;


	return 0;
}