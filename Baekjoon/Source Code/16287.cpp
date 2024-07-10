// 내 코드
// meet in the middle
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

using pii = pair<int, int>;

int counts_index[800000]{};
pii counts[800000][20]{};
int weights[5001]{};

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	int w, n;
	cin >> w >> n;
	/*vector<int> ws(n, 0);*/
	for (int i = 0; i < n;++i) {
		cin >> weights[i];
	}

	//vector<vector<pii>> counts(w);
	bool chk = false;
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			if (weights[i] + weights[j] >= w) continue;
			int sum = weights[i] + weights[j];
			counts[sum][counts_index[sum]].first = i;
			counts[sum][counts_index[sum]++].second = j;
			//counts[sum].push_back(make_pair(i, j));
			for (int k = 0; k < counts_index[w - sum]; ++k) {
				if (counts[w - sum][k].first == i || counts[w - sum][k].first == j
					|| counts[w - sum][k].second == i || counts[w - sum][k].second == j) continue;
				chk = true;
				break;
			}
			if (chk) break;
		}
		if (chk) break;
	}
	
	if (chk) cout << "YES\n";
	else cout << "NO\n";


	return 0;
}