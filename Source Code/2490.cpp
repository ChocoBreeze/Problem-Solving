#include <iostream>
#include <vector>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	
	for (int i{};i<3;++i) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		int sum = a + b + c + d;
		if (sum == 3) cout << "A\n"; // µµ
		else if (sum == 2) cout << "B\n"; // °³
		else if (sum == 1) cout << "C\n"; // °É
		else if (sum == 0) cout << "D\n"; // À·
		else cout << "E\n"; // ¸ð
	}

	return 0;
}