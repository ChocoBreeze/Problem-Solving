#include <iostream>
#include <string>

using namespace std;

int main() {
	int N; cin >> N;
	string space(N - 1, ' '), stars;
	stars.push_back('*');
	for (int i{}; i < N; ++i) {
		cout << space;
		if (i < N - 1) {
			space.pop_back();
		}
		cout << stars;
		stars.push_back(' ');
		stars.push_back('*');

		cout << '\n';
	}
	return 0;
}