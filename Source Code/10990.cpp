#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
	int N; cin >> N;
	string space(N - 1, ' '), space1("");
	for (int i{}; i < N; ++i) {
		cout << space;
		cout << '*';
		if (i < N - 1) {
			space.pop_back();
		}
		if (i) {
			cout << space1;
			cout << '*';
			space1 += ' ';
		}
		space1 += ' ';
		cout << '\n';
	}
	return 0;
}