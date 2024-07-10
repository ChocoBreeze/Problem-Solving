#include <iostream>
#include <deque>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}; cin >> N;
	deque<int> dq;
	for (int n{}; n < N; ++n) {
		int op{}; cin >> op;
		if (op == 1) { // push_front
			int X; cin >> X;
			dq.push_front(X);
		}
		else if (op == 2) { // push_back
			int X; cin >> X;
			dq.push_back(X);
		}
		else if (op == 3) { // pop_front
			if (dq.empty()) cout << "-1\n";
			else {
				cout << dq.front() << '\n';
				dq.pop_front();
			}
		}
		else if (op == 4) { // pop_back
			if (dq.empty()) cout << "-1\n";
			else {
				cout << dq.back() << '\n';
				dq.pop_back();
			}
		}
		else if (op == 5) { // size
			cout << dq.size() << '\n';
		}
		else if (op == 6) { // empty
			cout << dq.empty() << '\n';
		}
		else if (op == 7) { // front
			if (dq.empty()) cout << "-1\n";
			else cout << dq.front() << '\n';
		}
		else if (op == 8) { // back
			if (dq.empty()) cout << "-1\n";
			else cout << dq.back() << '\n';
		}
	}

	return 0;
}