// Rabin-Karp
// https://m.blog.naver.com/kks227/220927272165

/*
�ؽ��� �ϱ� ���� ��� ���ڿ��� ���̸� ���ϱ�..?
- ���� ���̰� K+1�� ���ڿ��� �� �� �����Ѵٸ�, �翬�� ���� K�� ���ڿ��� �� �� ������.
- ����� ���� K���, K ������ ��� ���̿� ���� �� �� �����ϴ� �κ� ���ڿ��� �����ϸ�, K���� ū ���̿� ���ؼ��� ����.
=> �̺� Ž���� ���� K�� ã�� �� ����! (���..)
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// �̹� ������ Ǯ���� MOD�� ��� ������ �۾ƾ� �մϴ�.
// �̰Ŵ� ����.. (�ʹ� ũ�� ������ �� ��� �׷� ����).
constinit const int MOD = 100'003;

inline int Mod(long long n) {
	if (n >= 0) return n % MOD;
	return ((-n / MOD + 1) * MOD + n) % MOD;
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int len{};
	string str;
	cin >> len >> str;

	// �� ������ K�� ã�� ���� �̺� Ž��
	int lo{}, hi{ len }; // �� �� �̻� �����ϴ� ���ڿ��� ã�� ������ len�� ���� �� �� ����.
	while (lo + 1 < hi) {
		int mid = lo + (hi - lo) / 2;

		int H{}, power = 1;
		vector<vector<int>> pos(MOD, vector<int>()); // pos[i]: �ؽð��� i�� �κ� ���ڿ��� ���� ��ġ��
		bool found{};

		// ������ ��� ��ġ���� ���� mid�� �κ� ���ڿ����� �ؽð��� ���� ���� ó��.
		for (int i{}; i <= len - mid; ++i) {
			if (i == 0) {
				// ù �ؽ� ���ϱ�
				for (int j{}; j < mid; ++j) {
					// ABC -> A*2^2 + B*2^1 + C*2^0
					H = Mod(H + 1LL * str[mid - 1 - j] * power);
					if (j < mid - 1) power = Mod(((1LL * power) << 1));
				}
			}
			else {
				H = Mod(((H - 1LL * str[i - 1] * power) << 1) + str[i + mid - 1]);
			}

			// �ؽ� Collision => ���� �������� ��¥ Ȯ��
			if (!pos[H].empty()) {
				for (int& start : pos[H]) { // �ؽð��� H�� ���ڿ��� ��������
					bool same{true};
					for (int j{}; j < mid; ++j) {
						if (str[i + j] != str[start + j]) {
							same = false;
							break;
						}
					}
					if (same) {
						found = true;
						break;
					}
				}
			}
			if (found) break; // �ϳ��� ������ �� �� �ʿ� ���� break
			else pos[H].push_back(i); // ���� ��ġ i push_back
		}

		// ���� mid�� �κ� ���ڿ��� �� �� �̻� �����ߴ��Ŀ� ���� ���ϰ� ����
		if (found) lo = mid; // ����
		else hi = mid; // ���� X
	}
	cout << lo << '\n';
	return 0;
}