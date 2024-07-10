// KMP ����
// https://m.blog.naver.com/kks227/220917078260
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	string T, P;
	getline(cin, T);
	getline(cin, P);

	int N{ static_cast<int>(T.length()) }, M{ static_cast<int>(P.length()) };
	vector<int> fail(M + 1, 0);
	for (int i = 1, j = 0; i < M; ++i) {
		while (j > 0 && P[i] != P[j]) j = fail[j - 1];
		if (P[i] == P[j]) fail[i] = ++j;
	}

	vector<int> result; // T, P�� ��ġ�ϴ� ������ result�� ������.
	for (int i{}, j{}; i < N; ++i) {
		// ���� ���ڰ� ����ġ�ϸ� fail ���� ��� ���� ��.
		while (j > 0 && T[i] != P[j]) j = fail[j - 1];
		if (T[i] == P[j]) { // ���� ���ڰ� ��ġ
			if (j == M - 1) { // ��ġ�ϴ� �ϳ� �߰�!
				// i = 0���� �����Ѵٸ� i - M + 1. ���� ���ǿ� ���� 1�� ����.
				result.push_back(i - M + 2);
				// ã�� ���� ��ó�� j�� �̵��ؼ� ��Ž��
				j = fail[j];
			}
			else ++j;
		}
	}

	// ��� ���
	cout << result.size() << '\n';
	for (int& r : result) cout << r << ' ';
	cout << '\n';

	return 0;
}