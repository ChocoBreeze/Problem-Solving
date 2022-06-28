#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		int A, B;
		cin >> A >> B;
		vector<string> chk(10000, "0");
		queue<int> Q;
		chk[A] = "";
		Q.push(A);
		while (!Q.empty()) {
			int now = Q.front();
			Q.pop();
			int now_d, now_s, now_l, now_r;
			now_d = (now * 2) % 10000;
			now_s = now - 1 == -1 ? 9999 : now - 1;
			now_l = (now % 1000) * 10 + now / 1000;
			now_r = now / 10 + (now % 10) * 1000;
			if (chk[now_d] == "0" || chk[now_d].length() > chk[now].length() + 1) {
				chk[now_d] = chk[now] + "D";
				if (now_d == B) break;
				Q.push(now_d);
			}
			if (chk[now_s] == "0" || chk[now_s].length() > chk[now].length() + 1) {
				chk[now_s] = chk[now] + "S";
				if (now_s == B) break;
				Q.push(now_s);
			}
			if (chk[now_l] == "0" || chk[now_l].length() > chk[now].length() + 1) {
				chk[now_l] = chk[now] + "L";
				if (now_l == B) break;
				Q.push(now_l);
			}
			if (chk[now_r] == "0" || chk[now_r].length() > chk[now].length() + 1) {
				chk[now_r] = chk[now] + "R";
				if (now_r == B) break;
				Q.push(now_r);
			}
		}
		cout << chk[B] << "\n";
	}
	return 0;
}