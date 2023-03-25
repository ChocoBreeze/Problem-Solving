#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	while (1) {
		int A, B, C;
		cin >> A >> B >> C;
		if (A == 0 && B == 0 && C == 0) break;
		if (A >= B + C || B >= A + C || C >= A + B) {
			cout << "Invalid\n";
		}
		else {
			if (A == B && B == C) {
				cout << "Equilateral\n"; // 정삼각형
			}
			else if (A == B || B == C || C == A) {
				cout << "Isosceles\n"; // 이등변 삼각형
			}
			else {
				cout << "Scalene\n";
			}
		}
	}
	return 0;
}