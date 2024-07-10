#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory> // unique_ptr

using namespace std;
using psi = pair<string, int>;
constinit const int SIZE = 98;
// ���� ���� : 0x20(32) ~ DEL ��ȣ : 0x7F(127)

struct Trie {
	int count; // count > 1 : �� �Ǵ�
	unique_ptr<Trie> next[SIZE];
	Trie(int count = 0) : count(count) {}
	~Trie() = default;
};

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	
	unique_ptr<Trie> head = unique_ptr<Trie>(new Trie());
	vector<string> strs;
	int cnt{};
	while (1) {
		string str;
		getline(cin, str);
		// ���� ��ҹ��ڿ� ���鹮��, �׸��� ����, Ư�����ڸ� ����
		if (cin.eof()) break;
		++cnt;
		strs.emplace_back(str);

		// Trie ����
		Trie* now = head.get();
		int strLen = static_cast<int>(str.length());
		for (int i{}; i < strLen; ++i) {
			int index = str[i] - ' ';
			if (!now->next[index]) now->next[index] = unique_ptr<Trie>(new Trie());
			if(i == strLen - 1) now->next[index]->count++;
			now = now->next[index].get();
		}

	}

	sort(begin(strs), end(strs));
	strs.erase(unique(begin(strs), end(strs)), end(strs)); // �̸� �ߺ� ����

	cout << fixed;
	cout.precision(4); // ������� �Ҽ��� 4°�ڸ����� �ݿø�
	for (string& str : strs) {
		Trie* now = head.get();
		int strLen = static_cast<int>(str.length());
		for (int i{}; i < strLen; ++i) {
			int index = str[i] - ' ';
			now = now->next[index].get();
		}
		cout << str << ' ' << static_cast<double>(now->count) * 100 / cnt << '\n';
	}
	
	return 0;
}