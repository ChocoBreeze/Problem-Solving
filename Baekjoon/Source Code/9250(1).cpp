// https://m.blog.naver.com/kks227/220992598966
// ��ȣ�ڶ��(Aho-Corasick) ����
// ���� C ���ڿ� -> <string>
// shared_ptr, weak_ptr
#include <iostream>
#include <queue>
#include <algorithm>
#include <string>
#include <memory>

using namespace std;
constinit const int ALPHABETNUM = 26;

// Ʈ���� ����ü
struct Trie {
    // ���� ��忡�� �ش� ���ڸ� ������ ���� ���
    // Trie* go[ALPHABETNUM];
    shared_ptr<Trie> go[ALPHABETNUM];

    // ���� ��忡�� �ش� ������ go �������� ���� �� ���� ���
    // Trie* fail;
    weak_ptr<Trie> fail;
    // ���� ��忡 �����ϸ� ã�� ���ڿ� ����: �� ���������� ���缺�� ������ ��
    bool output;

    Trie() : output(false) {}
    ~Trie() = default;

    void insert(string& key, int index) {
        if (index == key.length()) {
            output = true;
            return;
        }
        int next = key[index] - 'a';
        if (!go[next]) {
            go[next] = shared_ptr<Trie>(new Trie);
        }
        go[next]->insert(key, index + 1); // �� ���ڿ��� ���̴� 100�� ���� �ʴ´�. -> ���߿� �ʿ��ϸ� ����� ���� �����
    }
};

int main() {
    // �� ���ڿ��� �κ� ���ڿ��� ���� S�� �ִ��� �Ǻ��ϴ� ���α׷�
    cin.tie(nullptr)->sync_with_stdio(false);
    int N, M;
    string str;
    // Ʈ���̿� S�� ���ҵ��� ��� ����ִ´�.
    // Trie* root = new Trie;
    // shared_ptr<Trie> root = shared_ptr<Trie>(new Trie); // ����
    shared_ptr<Trie> root = std::make_shared<Trie>();
    cin >> N;
    for (int n{}; n < N; ++n) {
        cin >> str;
        root->insert(str, 0);
    }

    // BFS�� ���� Ʈ���� ��带 �湮�ϸ� fail �Լ��� �����.
    queue<weak_ptr<Trie>> Q;
    root->fail = root;
    Q.push(root);
    while (!Q.empty()) {
        weak_ptr<Trie> current = Q.front();
        Q.pop();

        // 26���� ���ĺ� ������ ���� ó���Ѵ�.
        for (int i{}; i < ALPHABETNUM; i++) {
            shared_ptr<Trie> next = current.lock()->go[i];
            if (!next) continue;

            if (current.lock() == root) next->fail = root; // �ٽ� root�� ���ư�����
            else {
                weak_ptr<Trie> dest = current.lock()->fail; // �ʱⰪ = ���� ����
                // fail�� ������ ���� ����� ������ ã�ư���.
                // �׻� fail(x)�� x�� ���� �� ���̻簡 �ƴ� ���� ����(���� �׷��� �� �ص� �ƹ� ������ ���)
                while (dest.lock() != root && !dest.lock()->go[i]) // �� ���ڰ� ���ٸ� �ǵ��� ����
                    dest = dest.lock()->fail;
                // fail(px) = go(fail(p), x)
                if (dest.lock()->go[i]) dest = dest.lock()->go[i]; // dest(p)���� x�� �� �ִٸ� dest�� 
                next->fail = dest; // ���� ���ڿ��� ���� ���ڷ� ������ �ʱⰪ ����
            }
            // fail(x) = y�� ��, output(y) �� output(x)
            if (next->fail.lock()->output) next->output = true;

            // ť�� ���� ��� push
            Q.push(next);
        }
    }

    // �� ���ڿ��� �޾� ������ Ǭ��.
    cin >> M;
    for (int m{}; m < M; ++m) {
        cin >> str;
        // ��Ʈ���� ����
        weak_ptr<Trie> current = root;
        bool result = false;
        for (char& c : str) {
            int next = c - 'a';
            // ���� ��忡�� �� �� ������ fail�� ��� ����
            while (current.lock() != root && !current.lock()->go[next])
                current = current.lock()->fail;
            // go �Լ��� �����ϸ� �̵�. ��Ʈ�� �̰� false�� ���� �ִ�
            if (current.lock()->go[next])
                current = current.lock()->go[next];
            // ���� ��忡 output�� ������ ã�� ���̴�.
            if (current.lock()->output) {
                result = true;
                break;
            }
        }
        // ��� ���
        if (result) cout << "YES\n";
        else cout << "NO\n";
    }
    // �� ���� �����ϱ⿡ �� �����Ҵ��� �����Ѵ�.
    // delete root;
    return 0;
}