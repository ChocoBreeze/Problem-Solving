// 2020KB, 0ms
#include <iostream>
#include <string>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int T{}; cin >> T;
	while (T--) {
		int N{}; cin >> N;
		string strN = to_string(N), strSqrN = to_string(N*N);
		auto l1{ strN.length() }, l2{ strSqrN.length() };
		bool chk{ true };
		for (int s{}, e{ static_cast<int>(strN.length()) }; s < e; ++s) {
			if (strN[l1 - 1 - s] != strSqrN[l2 - 1 - s]) {
				chk = false;
				break;
			}
		}
		if (chk) cout << "YES\n";
		else cout << "NO\n";
	}
	return 0;
}