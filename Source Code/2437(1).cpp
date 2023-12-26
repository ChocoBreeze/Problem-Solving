// https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=hongjg3229&logNo=221627349685
// 멋지군..
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N; cin >> N;
	vector<int> weights(N, 0);
	for (int& w : weights) cin >> w;
	sort(begin(weights), end(weights));

	int answer{};
	if (weights[0] != 1) answer = 1;
	else {
		int sum{weights[0]}; // sum까지 무게 측정이 가능하다는 의미.
		for (int n{1}; n < N; ++n) {
			if (weights[n] > sum + 1) {
				answer = sum + 1;
				break;
			}
			sum += weights[n];
		}
		if (answer == 0) answer = sum + 1; // 못 찾았다면 갱신 필요
	}
	cout << answer << '\n';
	return 0;
}