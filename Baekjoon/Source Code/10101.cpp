#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	int A, B, C;
	cin >> A >> B >> C;
	if (A == 60 && B == 60 && C == 60) {
		cout << "Equilateral\n"; // 정삼각형
	}
	else if(180 == A + B + C) {
		if (A == B || B == C || C == A) {
			cout << "Isosceles\n"; // 이등변삼각형
		}
		else {
			cout << "Scalene\n"; // 그냥 삼각형
		}
	}
	else {
		cout << "Error\n";
	}
	return 0;
}