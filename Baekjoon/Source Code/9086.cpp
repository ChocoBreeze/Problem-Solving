#include <iostream>
#include <string>

using namespace std;

int main() {
	int N;
	string str;
	cin.tie(NULL)->sync_with_stdio(false);
	cin >> N;
	for (int n{}; n < N; ++n) {
		cin >> str;
		cout << str.front() << str.back() << '\n';
	}
	
	return 0;
}