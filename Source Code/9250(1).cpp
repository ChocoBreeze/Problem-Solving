// https://m.blog.naver.com/kks227/220992598966
// 아호코라식(Aho-Corasick) 공부
// 기존 C 문자열 -> <string>
// shared_ptr, weak_ptr
#include <iostream>
#include <queue>
#include <algorithm>
#include <string>
#include <memory>

using namespace std;
constinit const int ALPHABETNUM = 26;

// 트라이 구조체
struct Trie {
    // 현재 노드에서 해당 문자를 받으면 가는 노드
    // Trie* go[ALPHABETNUM];
    shared_ptr<Trie> go[ALPHABETNUM];

    // 현재 노드에서 해당 문자의 go 목적지가 없을 때 가는 노드
    // Trie* fail;
    weak_ptr<Trie> fail;
    // 현재 노드에 도달하면 찾는 문자열 집합: 이 문제에서는 존재성만 따지면 됨
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
        go[next]->insert(key, index + 1); // 이 문자열의 길이는 100을 넘지 않는다. -> 나중에 필요하면 비재귀 버전 만들기
    }
};

int main() {
    // 각 문자열의 부분 문자열이 집합 S에 있는지 판별하는 프로그램
    cin.tie(nullptr)->sync_with_stdio(false);
    int N, M;
    string str;
    // 트라이에 S의 원소들을 모두 집어넣는다.
    // Trie* root = new Trie;
    // shared_ptr<Trie> root = shared_ptr<Trie>(new Trie); // 가능
    shared_ptr<Trie> root = std::make_shared<Trie>();
    cin >> N;
    for (int n{}; n < N; ++n) {
        cin >> str;
        root->insert(str, 0);
    }

    // BFS를 통해 트라이 노드를 방문하며 fail 함수를 만든다.
    queue<weak_ptr<Trie>> Q;
    root->fail = root;
    Q.push(root);
    while (!Q.empty()) {
        weak_ptr<Trie> current = Q.front();
        Q.pop();

        // 26개의 알파벳 각각에 대해 처리한다.
        for (int i{}; i < ALPHABETNUM; i++) {
            shared_ptr<Trie> next = current.lock()->go[i];
            if (!next) continue;

            if (current.lock() == root) next->fail = root; // 다시 root로 돌아가도록
            else {
                weak_ptr<Trie> dest = current.lock()->fail; // 초기값 = 이전 문자
                // fail을 참조할 가장 가까운 조상을 찾아간다.
                // 항상 fail(x)가 x의 가장 긴 접미사가 아닐 수도 있음(굳이 그렇게 안 해도 아무 영향이 없어서)
                while (dest.lock() != root && !dest.lock()->go[i]) // 갈 문자가 없다면 되돌아 가기
                    dest = dest.lock()->fail;
                // fail(px) = go(fail(p), x)
                if (dest.lock()->go[i]) dest = dest.lock()->go[i]; // dest(p)에서 x갈 수 있다면 dest를 
                next->fail = dest; // 다음 문자에서 이전 문자로 가도록 초기값 설정
            }
            // fail(x) = y일 때, output(y) ⊂ output(x)
            if (next->fail.lock()->output) next->output = true;

            // 큐에 다음 노드 push
            Q.push(next);
        }
    }

    // 각 문자열을 받아 문제를 푼다.
    cin >> M;
    for (int m{}; m < M; ++m) {
        cin >> str;
        // 루트부터 시작
        weak_ptr<Trie> current = root;
        bool result = false;
        for (char& c : str) {
            int next = c - 'a';
            // 현재 노드에서 갈 수 없으면 fail을 계속 따라감
            while (current.lock() != root && !current.lock()->go[next])
                current = current.lock()->fail;
            // go 함수가 존재하면 이동. 루트면 이게 false일 수도 있다
            if (current.lock()->go[next])
                current = current.lock()->go[next];
            // 현재 노드에 output이 있으면 찾은 것이다.
            if (current.lock()->output) {
                result = true;
                break;
            }
        }
        // 결과 출력
        if (result) cout << "YES\n";
        else cout << "NO\n";
    }
    // 내 힙은 소중하기에 꼭 동적할당을 해제한다.
    // delete root;
    return 0;
}