// 편의상 사용자가 출력한 문자열의 길이가 문제의 답과 동일하고, 답은 0보다 크다고 가정한다.
// 진짜 있는지만 확인하면 됨.
#include <iostream>
#include <string>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	
	string A, B, userAnswer;
	cin >> A >> B >> userAnswer;
	if (A.find(userAnswer) != string::npos && B.find(userAnswer) != string::npos) {
		cout << "YES\n";
	}
	else cout << "NO\n";

	return 0;
}