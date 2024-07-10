#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	int N;
	cin >> N;
	vector<set<pair<int, int>>> vec(100 + 1);
	for (int i = 0; i < N; ++i) {
		int s, e;
		cin >> s >> e; // 0도 자연수에 포함인가? https://www.acmicpc.net/board/view/52247
		for (int j = s; j < s + 10; ++j) {
			vec[j].insert(make_pair(e, e + 10));
		}
	}
	int sum = 0;
	for (int i = 1; i <= 100; ++i) {
		int s = 0, e = 0;
		for (auto it = vec[i].begin(); it != vec[i].end(); ++it) {
			if (it == vec[i].begin()) {
				s = it->first;
				e = it->second;
				continue;
			}
			else {
				if (it->first < e) {
					e = it->second; 
					// 구간 갱신
				}
				else {
					// 기존 구간 더하기 + 새 구간
					sum += (e - s);
					s = it->first;
					e = it->second;
				}
			}
		}
		sum += (e - s);
	}
	cout << sum << '\n';


	return 0;
}