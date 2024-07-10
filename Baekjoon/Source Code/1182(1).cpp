// https://www.acmicpc.net/source/share/f10e05a86d3d4e43bf8522ae0653b1d3
// 새로운 풀이!
#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int N, S; cin >> N >> S;
	vector<int> vs(N,0);
	for(int& v : vs) cin >> v;

	// n <= 20 : int - bitmask로도 충분
	int last{1 << N}, ans{};
	for(int i{1}; i < last; ++i){
		int sum{};
		for(int j{}; j < N; ++j) {
			if(i & (1 << j)) sum += vs[j];
		}
		if(sum==S) ++ans;
	}
	cout << ans << '\n';

	return 0;
}