// Suffix Array : https://m.blog.naver.com/kks227/221028710658
// O(N{logN}^2)
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;
vector<int> sa, pos, lcp;
// sa[i] : ���������� i��° ��ġ�� ���̻簡 ���� ���ڿ��� �� ��° ���ں��� �����ϳĸ� �ǹ� => �ش� ���ڿ� ���� = str.substr(sa[i])
// pos[i] : str[i:]�� sa�� �� ��° index�� ��ġ�ϴ��� (pos[sa[i]] = i)
// lcp[i] : ���������� ������ ���� ���̻�� ���Ͽ� �տ������� �� ���� ���ڰ� ��ġ�ϴ���

void ConstructSA(string& str) {
	int sLen = static_cast<int>(str.length());
	sa = vector<int>(sLen, 0);
	pos = vector<int>(sLen, 0);

	// ��ó�� - ���� ù ��° ���������� ���ڸ� ���ڷ� ��
	for (int i{}; i < sLen; ++i) {
		sa[i] = i;
		pos[i] = str[i];
	}

	int d{ 1 };
	auto cmp = [&sLen, &d](int i, int j) -> bool {
		// 1. ���� �ڽ��� ��ġ�� ���ڸ� ��.
		if (pos[i] != pos[j]) return pos[i] < pos[j];

		// ���ڰ� ������ dĭ ���� ���ڳ��� ��
		i += d, j += d;
		return (i < sLen && j < sLen) ? (pos[i] < pos[j]) : (i > j);
		};

	// d�� 2�辿 �÷����鼭 �Ź� �տ������� d*2���ڸ� ���� ���̻� ����
	for (;; d <<= 1) {
		sort(begin(sa), end(sa), cmp);

		// temp : ���ο� �׷� ��ȣ
		vector<int> temp(sLen, 0);
		// �տ������� �����鼭 �� ���̻簡 ���� �ٸ� �׷쿡 ���� ������ �׷� ��ȣ ����.
		for (int i{}; i < sLen - 1; ++i) {
			temp[i + 1] = temp[i] + static_cast<int>(cmp(sa[i], sa[i + 1]));
		}
		// pos �迭�� temp �迭�� ��ü.
		for (int i{}; i < sLen; ++i) {
			pos[sa[i]] = temp[i];
		}

		// ��� ���̻簡 �ٸ� �׷����� ���������ٸ� ����
		if (temp[sLen - 1] == sLen - 1) break;
	}
}
void ConstructLCP(string& str) {
	int sLen = static_cast<int>(str.length());
	lcp = vector<int>(sLen, 0);

	// sa[i]�� ���������� i��° ��ġ�� ���̻簡 ���� ���ڿ��� �� ��° ���ں��� �����ϳĸ� �ǹ�
	// pos[i] = str[i:]�� sa�� �� ��°�� �ִ°� (pos[sa[i]] = i)
	// ���� �� ���̻�(str)���� ������.
	// �� �������� k > 0�̸� k--
	for (int i{}, k{}; i < sLen; ++i, k = max(k - 1, 0)) {
		// ������ ���̻�(���� ������ �������� ���̻�)�� �ƹ��͵� �� ��.
		if (pos[i] == sLen - 1) {
			lcp[pos[i]] = -1; // X ǥ��
			continue;
		}

		// �ٷ� �Ʒ� ������ ���̻�� ���Ͽ� �տ������� �� ���� ���ڰ� ��ġ�ϴ��� ī����
		// pos[i] + 1 (���������� ���� ���ڿ� ���� ���ڿ��� sa index)
		int j = sa[pos[i] + 1];
		while (str[i + k] == str[j + k]) ++k;
		lcp[pos[i]] = k;
	}
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	string str; cin >> str; // ���� 1'000'000 ����
	int strLen = static_cast<int>(str.length());
	// ababc => a, ab, aba, abc, abab, ababc, b, ba, bc, bab, babc, c => 12
	// banana => a, an, ana, anan, anana, b, ba, ban, bana, banan, banana, n, na, nan, nana => 15

	ConstructSA(str);
	ConstructLCP(str);

	long long answer{};
	for (int i{}; i < strLen; ++i) {
		answer += (static_cast<long long>(strLen) - sa[i] - lcp[i]);
		// strLen - sa[i] : �̹��� ī�����ϴ� ���̻��
		// lcp[i] : �տ��� �̹� ������ ���λ� ����(���ֱ�)
	}
	// ������ ���̻翡 �ش��ϴ� lcp : -1
	answer--; // -1�� �������� �ٽ� �����ֱ�
	cout << answer << '\n';

	return 0;
}