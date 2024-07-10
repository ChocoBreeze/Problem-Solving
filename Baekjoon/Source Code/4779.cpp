#include <iostream>
#include <string>

using namespace std;
string str;
// [start, finish)
void recursive(int start, int finish) {
	// base case
	if (finish - start == 1) return;

	int len = (finish - start) / 3;
	recursive(start, start + len);
	for (int i{ 0 }; i < len; ++i) {
		str[start + len + i] = ' ';
	}
	recursive(finish - len, finish);

}

int main() {
	cin.tie(NULL)->sync_with_stdio(false);

	int n;
	while (cin >> n) {
		int len{ 1 };
		while (n--) len *= 3;
		str.assign(len, '-');
		recursive(0, len);
		cout << str << '\n';
	}


	return 0;
}