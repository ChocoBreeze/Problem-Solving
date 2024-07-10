#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
using psi = pair<string, int>;
constinit const int SIZE = 98;
// ���� ���� : 0x20(32) ~ DEL ��ȣ : 0x7F(127)

struct Trie {
	int count; // count > 1 : �� �Ǵ�
	Trie* next[SIZE]; // char - ' '
	Trie(int count = 0) : count(count) {
		for (int i{}; i < SIZE; ++i) {
			this->next[i] = nullptr;
		}
	}
	~Trie() {
		for (int i{}; i < SIZE; ++i) {
			if (this->next[i] != nullptr) delete this->next[i];
		}
	}
};

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	
	Trie* head = new Trie();
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
		Trie* now = head;
		int strLen = static_cast<int>(str.length());
		for (int i{}; i < strLen; ++i) {
			int index = str[i] - ' ';
			if (!now->next[index]) now->next[index] = new Trie();
			if(i == strLen - 1) now->next[index]->count++;
			now = now->next[index];
		}

	}

	sort(begin(strs), end(strs));
	strs.erase(unique(begin(strs), end(strs)), end(strs)); // �̸� �ߺ� ����

	cout << fixed;
	cout.precision(4); // ������� �Ҽ��� 4°�ڸ����� �ݿø�
	for (string& str : strs) {
		Trie* now = head;
		int strLen = static_cast<int>(str.length());
		for (int i{}; i < strLen; ++i) {
			int index = str[i] - ' ';
			now = now->next[index];
		}
		cout << str << ' ' << static_cast<double>(now->count) * 100 / cnt << '\n';
	}
	
	// delete head;
	return 0;
}