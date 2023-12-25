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

// 트라이 구조체
struct Trie {
    // 현재 노드에서 해당 문자를 받으면 가는 노드
    Trie* go[SIZE];
    // 현재 노드에서 해당 문자의 go 목적지가 없을 때 가는 노드
    Trie* fail;
    // 현재 노드에 도달하면 찾는 문자열 집합: 이 문제에서는 존재성만 따지면 됨
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
        // marker에서 돌연변이 문자열 구성
		for (int i{}; i < m; ++i) { // 두번째 영역의 시작 인덱스
			for (int j{i}; j < m; ++j) { // 두번째 영역의 끝 인덱스
                Trie* temp = root; // insert용 root copy
                for (int k{}; k < i; ++k) { // 첫 번째 영역
                    int next = chrToInt[marker[k]];
                    if (temp->go[next] == nullptr) {
                        temp->go[next] = new Trie();
                    }
                    temp = temp->go[next];
                }
                for (int k{ j }; k >= i; --k) { // 두 번째 영역 - 거꾸로
                    int next = chrToInt[marker[k]];
                    if (temp->go[next] == nullptr) {
                        temp->go[next] = new Trie();
                    }
                    temp = temp->go[next];
                }
                for (int k{ j + 1 }; k < m; ++k) { // 세 번째 영역
                    int next = chrToInt[marker[k]];
                    if (temp->go[next] == nullptr) {
                        temp->go[next] = new Trie();
                    }
                    temp = temp->go[next];
                }
                temp->output = true; // 마지막 지점 표시
			}
		}

        // fail 함수 구성
        queue<Trie*> Q;
        root->fail = root;
        Q.push(root);
        while (!Q.empty()) {
            Trie* now = Q.front(); Q.pop();
            for (int i{}; i < SIZE; ++i) {
                Trie* next = now->go[i];
                if (!next) continue;

                if (now == root) next->fail = root; // 다시 root로 돌아가도록
                else {
                    Trie* dest = now->fail; // 초기값 = 이전 문자의 fail
                    // fail을 참조할 가장 가까운 조상을 찾아간다.
                    // 항상 fail(x)가 x의 가장 긴 접미사가 아닐 수도 있음(굳이 그렇게 안 해도 아무 영향이 없어서)

                    while (dest != root && !dest->go[i]) { // 갈 문자가 없다면 되돌아 가기
                        dest = dest->fail;
                    }

                    // fail(px) = go(fail(p), x)
                    if (dest->go[i]) dest = dest->go[i]; // dest(p)에서 x갈 수 있다면 dest를 x로 이동
                    next->fail = dest; // fail 갱신
                }
                // fail(x) = y일 때, output(y) ⊂ output(x)
                if (next->fail->output) next->output = true;

                // 큐에 다음 노드 push
                Q.push(next);
            }
        }

        // 개수 확인
        int answer{};
        Trie* curr = root;
        for (auto& c : dna) {
            int next = chrToInt[c];
            // 현재 노드에서 갈 수 없으면 fail을 계속 따라감
            while (curr != root && !curr->go[next]) {
                curr = curr->fail;
            }
            // go 함수가 존재하면 이동. 루트면 이게 false일 수도 있다
            if (curr->go[next]) curr = curr->go[next];
            if (curr->output) ++answer;
        }
        cout << answer << '\n';

        delete root;
	}

	return 0;
}