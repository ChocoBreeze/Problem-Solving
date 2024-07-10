// https://sgc109.github.io/2021/03/18/largest-rectangle-in-histogram/
// DevideAndConquer
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
const int MAXH = 2000000000;
using ll = long long;

vector<int> heights;

/*
1. 왼쪽 포인터와 오른쪽 포인터 모두에 대해 다음 막대가 현재 직사각형의 높이보다 높거나 같은 높이인 경우
--> 어느 포인터를 이동해도 상관 없음
2. 한쪽은 직사각형의 높이보다 높거나 같고, 한쪽은 낮은 경우
--> 높이가 높은 쪽 포인터 움직이기
3. 왼쪽 포인터와 오른쪽 포인터 모두, 다음 막대가 현재 직사각형의 높이보다 낮은 경우
--> 다음 막대의 높이가 더 큰 포인터를 이동
*/

ll solve(int left, int right) {
	if (left == right) return heights[left]; // 1개 구간
	int mid{ left + (right - left) / 2 };
	
	// left, right 중 최대
	ll ans = max(solve(left, mid), solve(mid + 1, right));

	int lpos{ mid }, rpos{ mid + 1 };
	int minH = MAXH + 1;

	// left, right에 걸치는 경우
	while (left <= lpos && rpos <= right) {
		minH = min({ minH, heights[lpos], heights[rpos] });
		ans = max(ans, (static_cast<ll>(rpos) - lpos + 1) * minH);
		
		if (left == lpos) ++rpos;
		else if (right == rpos) --lpos;
		else if (heights[lpos - 1] <= heights[rpos + 1]) ++rpos;
		else --lpos;
	}
	return ans;
}

int main() {
	int n;
	cin.tie(NULL)->sync_with_stdio(false);
	while (1) {
		cin >> n;
		if (n == 0) break; // EOF
		heights = vector<int>(n, 0);
		for (int& h : heights) cin >> h;
		cout << solve(0, n - 1) << '\n';
	}
}