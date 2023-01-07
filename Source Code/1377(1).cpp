#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

using pii = pair<int, int>;

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	int N, index = 0;
	cin >> N;
	vector<pii> A(N, make_pair(0,0));
	for (auto& a : A) {
		cin >> a.first;
		a.second = index++;
	}

	stable_sort(begin(A), end(A));

	int answer = 0;
	index = 0;
	for (auto& a : A) {
		answer = max(answer, a.second - index); // 앞으로 최대 몇 칸 가는지(즉, 반전수가 몇개인지)
		++index;
	}
	
	cout << answer + 1 << '\n';

	return 0;
}