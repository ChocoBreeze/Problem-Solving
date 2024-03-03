// 16284KB, 232ms
#include <iostream>
#include <string>
#include <map>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}, M{}; cin >> N >> M;
	map<string, string> mss;
	for (int n{}; n < N; ++n) {
		string address, pwd; cin >> address >> pwd;
		mss.emplace(address, pwd);
	}
	for (int m{}; m < M; ++m) {
		string address; cin >> address;
		cout << mss[address] << '\n';
	}

	return 0;
}