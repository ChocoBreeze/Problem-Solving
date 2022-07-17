/*
Union Find 응용 -> 아이디어는 알았는데, 구현이 힘들었다..
! a b w : b가 a보다 w그램 무겁다. (w = 0 ~ 1,000,0000이하)
? a b : 교수님의 질문(=b가 a보다 얼마나 무거운지를 출력해라)
*/
#include <iostream>
#include <vector>
#include <utility>

using namespace std;
struct Disjoint_Set {
	vector<int> par, weight;

	Disjoint_Set(int n) : par(n, -1), weight(n, 0) {}

	int root(int x) {
		if (par[x] == -1) return x;
		else return par[x] = root(par[x]);
	}
	pair<int, int> root_weight(int x) {
		if (par[x] == -1) return make_pair(x, weight[x]);
		else {
			auto ret = root_weight(par[x]);
			weight[x] += ret.second; // 갱신
			ret.second = weight[x];
			par[x] = ret.first;
			return ret;
		}
	}
	int renew_weight(int x, int w) {
		if (par[x] == -1) return weight[x];
		else return weight[x] = w + weight[x] + renew_weight(par[x], 0);
	}

	bool join(int x, int y, int w) {
		pair<int,int> x_ = root_weight(x), y_ = root_weight(y);
		if (x_.first == y_.first) return false;
		// x -> y : w
		// y_ -> y : weight[y]
		// x_ -> x : weight[x]
		// y_ -> x_ : weight[y] - weight[x] - w;
		// x_ -> y_ : weight[x] + w - weight[y]
		if (y_.second - w > x_.second) { // y_가 root
			weight[x_.first] = weight[y] - weight[x] - w;
			// weight[x_.first] = w;
			par[x_.first] = y_.first;
		}
		else { // x_가 root
			weight[y_.first] = weight[x] - weight[y] + w;
			// weight[y_.first] = w;
			par[y_.first] = x_.first;
		}
		return true;
	}
};

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int N, M; // N : 2 ~ 100000, M : 1 ~ 100000
	while (1) {
		cin >> N >> M;
		if (N == 0 && M == 0) break;
		Disjoint_Set D(N + 1); // 1 ~ n
		char q;
		int a, b, w;
		for (int i = 0; i < M; ++i) {
			cin >> q;
			if (q == '!') {
				cin >> a >> b >> w;
				D.join(a, b, w);
			}
			else {
				cin >> a >> b;
				if (D.root_weight(a).first == D.root_weight(b).first) { // root check
					cout << D.weight[b] - D.weight[a] << "\n";
				}
				else {
					cout << "UNKNOWN\n";
				}
			}
		}
	}
	return 0;
}