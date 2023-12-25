#include <iostream>

using namespace std;
constinit const int MAXTIME = 23 * 3600 + 59 * 60 + 59 + 1;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int A, B, C, D;
	cin >> A >> B >> C >> D;
	
	int total = A * 3600 + B * 60 + C;
	total += D;
	total %= MAXTIME;

	int H = total / 3600;
	int M = (total % 3600) / 60;
	int S = total % 60;

	cout << H << ' ' << M << ' ' << S << '\n';
	return 0;
}