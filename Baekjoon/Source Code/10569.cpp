#include <iostream>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int T{}; cin >> T;
	while (T--) {
		int V, E; cin >> V >> E; // 꼭짓점, 모서리
		// 꼭짓점(V) - 모서리(E) + 면 = 2
		cout << 2 - V + E << '\n';
	}
	return 0;
}