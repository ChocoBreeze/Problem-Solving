// 16056KB, 124ms
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}, M{}; cin >> N >> M;
	unordered_map<string, string> um;
	for (int n{}; n < N; ++n) {
		string address, pwd; cin >> address >> pwd;
		um.emplace(address, pwd);
	}
	for (int m{}; m < M; ++m) {
		string address; cin >> address;
		cout << um[address] << '\n';
	}

	return 0;
}