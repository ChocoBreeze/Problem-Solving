#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int L{}; cin >> L; // ������ ũ��
	string str; cin >> str; // ���� �����ǿ� ���̴� ���ڿ�

	// ����ġ�� �߻����� �� ���� �̵��ؾ� �ϴ��� ��Ÿ���� ��
	// fail(x) = W�� ó�� (x+1)���� ��, ��ġ�ϴ� ���λ�/���̻� �� �ִ� ����
	vector<int> fail(L + 1, 0); 
	for (int i{ 1 }, j{}; i < L; ++i) {
		while (j > 0 && str[i] != str[j]) j = fail[j - 1];
		if (str[i] == str[j]) fail[i] = ++j;
	}

	cout << L - fail[L - 1] << '\n';
	return 0;
}