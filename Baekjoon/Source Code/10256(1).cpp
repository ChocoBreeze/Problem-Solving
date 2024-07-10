// https://m.blog.naver.com/kks227/220992598966
// Aho-Corasick
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;
constinit const int SIZE = 4;
unordered_map<char, int> chrToInt{
    {'A', 0}, {'C', 1}, {'G',2}, {'T', 3}
};

// Ʈ���� ����ü
struct Trie {
    // ���� ��忡�� �ش� ���ڸ� ������ ���� ���
    Trie* go[SIZE];
    // ���� ��忡�� �ش� ������ go �������� ���� �� ���� ���
    Trie* fail;
    // ���� ��忡 �����ϸ� ã�� ���ڿ� ����: �� ���������� ���缺�� ������ ��
    bool output;

    Trie() : fail(nullptr), output(false) {
        fill(go, go + SIZE, nullptr);
    }
    ~Trie() {
        for (int i{}; i < SIZE; ++i) {
            if (go[i]) delete go[i];
        }
    }
};

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int T{}; cin >> T;
	while (T--) {
		int n{}, m{}; cin >> n >> m;
		string dna, marker;
		cin >> dna >> marker;
		
        Trie* root = new Trie();
        // marker���� �������� ���ڿ� ����
		for (int i{}; i < m; ++i) { // �ι�° ������ ���� �ε���
			for (int j{i}; j < m; ++j) { // �ι�° ������ �� �ε���
                Trie* temp = root; // insert�� root copy
                for (int k{}; k < i; ++k) { // ù ��° ����
                    int next = chrToInt[marker[k]];
                    if (temp->go[next] == nullptr) {
                        temp->go[next] = new Trie();
                    }
                    temp = temp->go[next];
                }
                for (int k{ j }; k >= i; --k) { // �� ��° ���� - �Ųٷ�
                    int next = chrToInt[marker[k]];
                    if (temp->go[next] == nullptr) {
                        temp->go[next] = new Trie();
                    }
                    temp = temp->go[next];
                }
                for (int k{ j + 1 }; k < m; ++k) { // �� ��° ����
                    int next = chrToInt[marker[k]];
                    if (temp->go[next] == nullptr) {
                        temp->go[next] = new Trie();
                    }
                    temp = temp->go[next];
                }
                temp->output = true; // ������ ���� ǥ��
			}
		}

        // fail �Լ� ����
        queue<Trie*> Q;
        root->fail = root;
        Q.push(root);
        while (!Q.empty()) {
            Trie* now = Q.front(); Q.pop();
            for (int i{}; i < SIZE; ++i) {
                Trie* next = now->go[i];
                if (!next) continue;

                if (now == root) next->fail = root; // �ٽ� root�� ���ư�����
                else {
                    Trie* dest = now->fail; // �ʱⰪ = ���� ������ fail
                    // fail�� ������ ���� ����� ������ ã�ư���.
                    // �׻� fail(x)�� x�� ���� �� ���̻簡 �ƴ� ���� ����(���� �׷��� �� �ص� �ƹ� ������ ���)

                    while (dest != root && !dest->go[i]) { // �� ���ڰ� ���ٸ� �ǵ��� ����
                        dest = dest->fail;
                    }

                    // fail(px) = go(fail(p), x)
                    if (dest->go[i]) dest = dest->go[i]; // dest(p)���� x�� �� �ִٸ� dest�� x�� �̵�
                    next->fail = dest; // fail ����
                }
                // fail(x) = y�� ��, output(y) �� output(x)
                if (next->fail->output) next->output = true;

                // ť�� ���� ��� push
                Q.push(next);
            }
        }

        // ���� Ȯ��
        int answer{};
        Trie* curr = root;
        for (auto& c : dna) {
            int next = chrToInt[c];
            // ���� ��忡�� �� �� ������ fail�� ��� ����
            while (curr != root && !curr->go[next]) {
                curr = curr->fail;
            }
            // go �Լ��� �����ϸ� �̵�. ��Ʈ�� �̰� false�� ���� �ִ�
            if (curr->go[next]) curr = curr->go[next];
            if (curr->output) ++answer;
        }
        cout << answer << '\n';

        delete root;
	}

	return 0;
}