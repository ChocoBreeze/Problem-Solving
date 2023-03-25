// 266가지 문제로 정복하는 코딩 인터뷰 in C++ - 문제 17.8
// 이번 입력보다 크거나 같은 모든 height pop하면서 최대 넓이 계산
// Stack
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;
using ll = long long;
vector<int> heights;

// 끝에 도달하거나 더 작은 높이가 입력으로 온 경우 return true
inline bool IsNewPillarOrReachEnd(int curr_idx, int last_pillar_idx) {
	return curr_idx < static_cast<int>(heights.size()) ? heights[curr_idx] <= heights[last_pillar_idx] : true;
}

ll CalculateLargestRectangle() {
	stack<int> pillar_indices;
	ll max_rectangle_area = 0;
	// size(heights)만큼 순회해야 직사각형 넓이를 균일하게 처리 가능함.
	for (int i = 0; i <= static_cast<int>(size(heights)); ++i) {
		while (!pillar_indices.empty() && IsNewPillarOrReachEnd(i, pillar_indices.top())) {
			ll height = heights[pillar_indices.top()];
			pillar_indices.pop();
			ll width = pillar_indices.empty() ? i : i - pillar_indices.top() - 1;
			max_rectangle_area = max(max_rectangle_area, height * width);
		}
		pillar_indices.emplace(i);
	}
	return max_rectangle_area;
}

int main() {
	int n;
	cin.tie(NULL)->sync_with_stdio(false);
	while (1) {
		cin >> n;
		if (n == 0) break; // EOF
		heights = vector<int>(n, 0);
		for (int& h : heights) cin >> h;
		cout << CalculateLargestRectangle() << "\n";
	}
	return 0;
}