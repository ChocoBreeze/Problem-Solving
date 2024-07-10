#include<iostream>
#include<queue>
#include<string>

using std::cin;
using std::cout;
using std::queue;
using std::string;

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int N, a;
	cin >> N;
	string query;
	queue<int> Q;
	for (int i = 0; i < N; ++i) {
		cin >> query;
		if (query.compare("push") == 0) {
			cin >> a;
			Q.push(a);
		}
		else if (query.compare("pop") == 0) {
			if (Q.empty()) cout << "-1\n";
			else {
				cout << Q.front() << "\n";
				Q.pop();
			}
		}
		else if (query.compare("size") == 0) {
			cout << Q.size() << "\n";
		}
		else if (query.compare("empty") == 0) {
			if (Q.empty()) cout << "1\n";
			else cout << "0\n";
		}
		else if (query.compare("front") == 0) {
			if (Q.empty()) cout << "-1\n";
			else cout << Q.front() << "\n";
		}
		else if (query.compare("back") == 0) {
			if (Q.empty()) cout << "-1\n";
			else cout << Q.back() << "\n";
		}
	}
	return 0;
}