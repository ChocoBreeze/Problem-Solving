/*
1(1) 3 6 10 15 21 28 36 45 55 ... 990(44)

21 = 15 + 3 + 33
*/
#include <iostream>
#include <vector>

using namespace std;

int main() {
	cin.tie(NULL)->sync_with_stdio(false);

	int arr[46]{};
	for (int i = 1; i < 45; ++i) { // 44 : 990 
		arr[i] = i * (i + 1) / 2;
	}
	int T, in;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		cin >> in;
		bool chk = false;
		for (int i = 44; i >= 1; --i) {
			if (arr[i] > in) continue;
			for (int j = 44; j >= 1; --j) {
				if (arr[i] + arr[j] > in) continue;
				for (int k = 44; k >= 1; --k) {
					if (arr[i] + arr[j] + arr[k] == in) {
						chk = true;
						cout << "1\n";
						break;
					}
					if (arr[i] + arr[j] + arr[k] < in) break;
				}
				if (chk) break;
			}
			if (chk) break;
		}
		if (!chk) cout << "0\n";
	}

	
	
	return 0;
}