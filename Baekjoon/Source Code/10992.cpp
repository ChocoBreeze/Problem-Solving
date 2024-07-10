#include <iostream>
#include <string>

using namespace std;

int main() {
	int N; cin >> N;
	string space(N - 1, ' '), space1;
	for (int i{}; i < N - 1; ++i) {
		cout << space;
		if (i < N - 1) {
			space.pop_back();
		}
		cout << '*';
		if (i) {
			cout << space1 << '*';
			space1 += ' ';
		}
		space1 += ' ';
		cout << '\n';
	}
	string stars(2 * N - 1, '*');
	cout << stars << '\n';
	return 0;
}