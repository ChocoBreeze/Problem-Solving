// ���ǻ� ����ڰ� ����� ���ڿ��� ���̰� ������ ��� �����ϰ�, ���� 0���� ũ�ٰ� �����Ѵ�.
// ��¥ �ִ����� Ȯ���ϸ� ��.
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