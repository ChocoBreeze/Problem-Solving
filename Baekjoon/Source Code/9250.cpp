// https://m.blog.naver.com/kks227/220992598966
// ��ȣ�ڶ��(Aho-Corasick) ����
// ���� C ���ڿ� -> <string>
#include <iostream>
#include <queue>
#include <algorithm>
#include <string>

using namespace std;
constinit const int ALPHABETNUM = 26;

// Ʈ���� ����ü
struct Trie {
    // ���� ��忡�� �ش� ���ڸ� ������ ���� ���
    Trie* go[ALPHABETNUM];
    // ���� ��忡�� �ش� ������ go �������� ���� �� ���� ���
    Trie* fail;
    // ���� ��忡 �����ϸ� ã�� ���ڿ� ����: �� ���������� ���缺�� ������ ��
    bool output;

    Trie() : fail(nullptr), output(false) {
        fill(go, go + ALPHABETNUM, nullptr);
    }
    ~Trie() {
        for (int i{}; i < ALPHABETNUM; i++) {
            if (go[i]) delete go[i];
        }
    }
    void insert(string& key, int index) {
        if (index == key.length()) {
            output = true;
            return;
        }
        int next = key[index] - 'a';
        if (!go[next]) {
            go[next] = new Trie;
        }
        go[next]->insert(key, index + 1);
    }
};

int main() {
    // �� ���ڿ��� �κ� ���ڿ��� ���� S�� �ִ��� �Ǻ��ϴ� ���α׷�
    cin.tie(nullptr)->sync_with_stdio(false);
    int N, M;
    string str;
    // Ʈ���̿� S�� ���ҵ��� ��� ����ִ´�.
    Trie* root = new Trie;
    cin >> N;
    for (int n{}; n < N; ++n) {
        cin >> str;
        root->insert(str, 0);
    }

    // BFS�� ���� Ʈ���� ��带 �湮�ϸ� fail �Լ��� �����.
    queue<Trie*> Q;
    root->fail = root;
    Q.push(root);
    while (!Q.empty()) {
        Trie* current = Q.front();
        Q.pop();

        // 26���� ���ĺ� ������ ���� ó���Ѵ�.
        for (int i{}; i < ALPHABETNUM; i++) {
            Trie* next = current->go[i];
            if (!next) continue;

            if (current == root) next->fail = root; // �ٽ� root�� ���ư�����
            else {
                Trie* dest = current->fail; // �ʱⰪ = ���� ����
                // fail�� ������ ���� ����� ������ ã�ư���.
                // �׻� fail(x)�� x�� ���� �� ���̻簡 �ƴ� ���� ����(���� �׷��� �� �ص� �ƹ� ������ ���)
                while (dest != root && !dest->go[i]) // �� ���ڰ� ���ٸ� �ǵ��� ����
                    dest = dest->fail;
                // fail(px) = go(fail(p), x)
                if (dest->go[i]) dest = dest->go[i]; // dest(p)���� x�� �� �ִٸ� dest�� 
                next->fail = dest; // ���� ���ڿ��� ���� ���ڷ� ������ �ʱⰪ ����
            }
            // fail(x) = y�� ��, output(y) �� output(x)
            if (next->fail->output) next->output = true;

            // ť�� ���� ��� push
            Q.push(next);
        }
    }

    // �� ���ڿ��� �޾� ������ Ǭ��.
    cin >> M;
    for (int m{}; m < M; ++m) {
        cin >> str;
        // ��Ʈ���� ����
        Trie* current = root;
        bool result = false;
        for (char& c : str) {
            int next = c - 'a';
            // ���� ��忡�� �� �� ������ fail�� ��� ����
            while (current != root && !current->go[next])
                current = current->fail;
            // go �Լ��� �����ϸ� �̵�. ��Ʈ�� �̰� false�� ���� �ִ�
            if (current->go[next])
                current = current->go[next];
            // ���� ��忡 output�� ������ ã�� ���̴�.
            if (current->output) {
                result = true;
                break;
            }
        }
        // ��� ���
        if (result) cout << "YES\n";
        else cout << "NO\n";
    }
    // �� ���� �����ϱ⿡ �� �����Ҵ��� �����Ѵ�.
    delete root;
    return 0;
}