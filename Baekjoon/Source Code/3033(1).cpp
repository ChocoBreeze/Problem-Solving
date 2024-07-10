// https://m.blog.naver.com/kks227/221028710658
// Suffix Array(SA), Longest Common Prefix(LCP)
// O(NlogNlogN)

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
string str;
vector<int> sa, pos, lcp;
int sLen{};
// sa[i] : ���������� i��° ��ġ�� ���̻簡 ���� ���ڿ��� �� ��° ���ں��� �����ϳĸ� �ǹ���.
// pos[i] : str[i:]�� sa�� �� ��°�� �ִ°� (pos[sa[i]] = i)
// lcp[i] : ���������� i��° ���̻�� (i+1)��° ���̻簡 �տ������� �� ���ڰ� �������� �ǹ���.

void ConstructSA() {
	sa = vector<int>(sLen, 0);
	pos = vector<int>(sLen, 0);
	// ��ó�� - ���� ù ��° ���������� ���ڸ� ���ڷ� ��
	for (int i{}; i < sLen; ++i) {
		sa[i] = i;
		pos[i] = str[i];
	}

	int d = 1;
	auto cmp = [&d](int i, int j) -> bool {
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

void ConstructLCP() {
	lcp = vector<int>(sLen, 0);
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
	cin >> sLen >> str;

	ConstructSA();
	ConstructLCP();

	// �κ� ���ڿ� X�� �� �� �̻� ����
	// ���� ���, trut�� trutrut�� ��� �� ���̻�� ���ļ� ���´�.
	// ��, lcp�� �߿� �ִ��� ���� ������ �ȴ�..
	auto it = max_element(begin(lcp), end(lcp));
	if (*it == -1) cout << "0\n"; // �� ���� ó��
	else cout << *it << '\n';

	return 0;
}