#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <string>
#include <climits>

using namespace std;

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		int A, B;
		cin >> A >> B;
		vector<pair<int, int>> chk(10000, make_pair(0,INT_MAX)); // 이전 인덱스 + 길이
		queue<int> Q;
		chk[A].second = 0;
		Q.push(A);
		while (!Q.empty()) {
			int now = Q.front();
			Q.pop();
			int now_d, now_s, now_l, now_r;
			now_d = (now * 2) % 10000;
			now_s = now - 1 == -1 ? 9999 : now - 1;
			now_l = (now % 1000) * 10 + now / 1000;
			now_r = now / 10 + (now % 10) * 1000;
			if (chk[now_d].second > chk[now].second + 1) {
				chk[now_d].second = chk[now].second + 1;
				chk[now_d].first = now;
				if (now_d == B) break;
				Q.push(now_d);
			}
			if (chk[now_s].second > chk[now].second + 1) {
				chk[now_s].second = chk[now].second + 1;
				chk[now_s].first = now;
				if (now_s == B) break;
				Q.push(now_s);
			}
			if (chk[now_l].second > chk[now].second + 1) {
				chk[now_l].second = chk[now].second + 1;
				chk[now_l].first = now;
				if (now_l == B) break;
				Q.push(now_l);
			}
			if (chk[now_r].second > chk[now].second + 1) {
				chk[now_r].second = chk[now].second + 1;
				chk[now_r].first = now;
				if (now_r == B) break;
				Q.push(now_r);
			}
		}
		string answer;
		int start = B;
		while (start != A) {
			int now = chk[start].first;
			int now_d = (now * 2) % 10000;
			int now_s = now - 1 == -1 ? 9999 : now - 1;
			int now_l = (now % 1000) * 10 + now / 1000;
			int now_r = now / 10 + (now % 10) * 1000;
			// 하나로만 +해야됨.
			if (now_d == start) answer += 'D';
			else if (now_s == start) answer += 'S';
			else if (now_l == start) answer += 'L';
			else if (now_r == start) answer += 'R';
			start = now;
		}
		for (auto i = answer.rbegin(); i != answer.rend(); ++i) {
			cout << *i;
		}
		cout << "\n";
	}
	return 0;
}