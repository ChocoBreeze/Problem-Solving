/*
���� ���� : https://m.blog.naver.com/kks227/221028710658
���� LCP ����
suffix���� ���� ������ ���� �ȴ�. => �ٷ� �ڿ� ���� ���̻�� lcp�� ���ϴ� ���� ��
�� ���ڿ��� �ٿ��� ���� �� ������, �ٷ� ���̸� ������ ���� ���� �� �ִ�.
�ٸ� ���ĺ����� ���� �󿡼� �� ����(ASCII ���� �� ����) ���ڸ� �ϳ� ������ ������.
O(N{logN}^2)
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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
	string A, B;
	cin >> A >> B;
	int aLen = static_cast<int>(A.length()), bLen = static_cast<int>(B.length());
	int maxLen = min(aLen, bLen); // ���� �� �� �ִ� ���� ū ��

	A.push_back('$');
	string str = A + B;
	ConstructSA(str);
	ConstructLCP(str);

	/*
	// Print (Ȯ�ο�)
	cout << "suffix \t\t sa \t\t lcp\n";
	for (int i{}; i < static_cast<int>(str.length()); ++i) {
		// cout << i + 1 << ": " << str.substr(i) << '\n';
		cout << str.substr(sa[i]) << "\t\t" << sa[i] << "\t\t" << lcp[i] << '\n';
	}
	*/
	// �ݷ� : abc, kkk

	// ������ ���̻� ���� LCP �� �� �ִ�
	int index{-1}, maxLcp{ -1 };
	for (int i{}; i < static_cast<int>(lcp.size()) - 1; ++i) {
		if ((sa[i] < aLen && sa[i + 1] > aLen) || (sa[i] > aLen && sa[i + 1] < aLen)) { // �ϳ��� �� ���ڿ� ��� ����, ������ �ϳ��� �� ���ڿ��� ����
			if (maxLcp < lcp[i] && lcp[i] <= maxLen) {
				maxLcp = lcp[i];
				index = i;
			}
		}
	}

	// long long index = distance(begin(lcp), max_element(begin(lcp), end(lcp))); // ���� ���� ��ġ�� ���� ��ġ ã��
	
	// if(lcp[index])
	string answer = str.substr(sa[index]).substr(0, lcp[index]); // substr 2���ؾ� ����� ��� ����
	cout << answer.length() << '\n' << answer << '\n';
	return 0;
}