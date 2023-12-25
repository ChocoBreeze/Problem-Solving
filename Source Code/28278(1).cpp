#include <iostream>
#include <stack>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}; cin >> N;
	stack<int> S;

	for (int n{}; n < N; ++n) {
		int op{}; cin >> op;
		if (op == 1) { // push
			int X{}; cin >> X;
			S.push(X);
		}
		else if (op == 2) { // pop
			if (S.empty()) cout << -1 << '\n';
			else {
				cout << S.top() << '\n';
				S.pop();
			}
		}
		else if (op == 3) { // size
			cout << S.size() << '\n';
		}
		else if (op == 4) { // empty
			cout << S.empty() << '\n';
		}
		else if (op == 5) { // top
			if (S.empty()) cout << -1 << '\n';
			else {
				cout << S.top() << '\n';
			}
		}
	}

	return 0;
}