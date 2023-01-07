#include<iostream>
#include<algorithm>
#include<vector>
#include<string>

using namespace std;

struct score {
	int K;
	int E;
	int M;
	string name;
	score(int k, int e, int m, string name) : K(k), E(e), M(m), name(name) {}
};

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int N, a, b, c;
	string str;
	cin >> N;
	vector<score> S;
	for (int n = 0; n < N; ++n) {
		cin >> str >> a >> b >> c;
		S.push_back(score(a, b, c, str));
	}
	auto compare = [](const score& fi, const score& se) {
		if (fi.K != se.K) {
			return fi.K > se.K;
		}
		if (fi.E != se.E) {
			return fi.E < se.E;
		}
		if (fi.M != se.M) {
			return fi.M > se.M;
		}
		return fi.name < se.name;
	};
	sort(begin(S), end(S), compare);
	for (auto& s : S) {
		cout << s.name << "\n";
	}
	return 0;
}