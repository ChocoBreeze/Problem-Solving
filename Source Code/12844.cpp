// https://m.blog.naver.com/kks227/220824350353
// 기존에 짰던 것 보다 이게 더 간단하다!
// 구간이 짝수인 경우 갱신할 필요 없음.(짝수 개 XOR은 의미 없음)

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 세그먼트 트리 구조체
struct SegTree {
    int start; // leaf node 시작점
    vector<int> arr, lazy;

    // 생성자
    SegTree(int tmpN) : start(tmpN >> 1), arr(tmpN, 0), lazy(tmpN, 0) { }

    // 리프 노드들의 값을 먼저 입력한 후 전체 세그먼트 트리 구축
    void construct() {
        for (int i{ start - 1 }; i > 0; --i) {
            arr[i] = arr[i * 2] ^ arr[i * 2 + 1];
        }
    }

    // 구간 [ns, ne)인 node의 lazy 값을 propagate
    void propagate(int node, int ns, int ne) {
        // lazy 값이 존재하면 실행
        if (lazy[node] != 0) {
            if (node < start) { // 리프 노드가 아니면 자식들에게 lazy 미룸
                lazy[node * 2] ^= lazy[node];
                lazy[node * 2 + 1] ^= lazy[node];
            }
            else { // 리프 노드이면 값 갱신
                arr[node] ^= lazy[node];
            }
            lazy[node] = 0;
        }
    }

    // 구간 [s, e)에 k를 XOR하기.
    void Query(int s, int e, int k) { Query(s, e, k, 1, 0, start); }
    void Query(int s, int e, int k, int node, int ns, int ne) {
        // 일단 propagate
        propagate(node, ns, ne);

        if (e <= ns || ne <= s) return; // 해당되는 구간이 아님.
        if (s <= ns && ne <= e) {
            // 이 노드가 구간에 완전히 포함되면 lazy 부여 후 propagate
            lazy[node] ^= k; // 0 ^ k = k
            propagate(node, ns, ne);
            return;
        }
        int mid = ns + (ne - ns) / 2;
        Query(s, e, k, node * 2, ns, mid); // left
        Query(s, e, k, node * 2 + 1, mid, ne); // right
        // 마지막에 자식들의 값을 사용해 다시 자신의 값 갱신
        arr[node] = arr[node * 2] ^ arr[node * 2 + 1];
    }

    // 구간 [s, e)의 XOR을 구하라
    int XOR(int s, int e) { return XOR(s, e, 1, 0, start); }
    int XOR(int s, int e, int node, int ns, int ne) {
        // 일단 propagate
        propagate(node, ns, ne);

        if (e <= ns || ne <= s) return 0; // 맞는 범위가 아님
        if (s <= ns && ne <= e) return arr[node]; // 정확히 포함되는 구간

        int mid = ns + (ne - ns) / 2;
        return XOR(s, e, node * 2, ns, mid) ^ XOR(s, e, node * 2 + 1, mid, ne);
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // 초기 세그먼트 트리 입력받기
    int N; cin >> N; // 수의 개수

    int tmpN{ 1 }; // leaf node 개수 * 2
    while (tmpN < N) {
        tmpN <<= 1;
    }
    tmpN <<= 1;

    SegTree ST(tmpN);
    for (int i{ST.start}; i < ST.start + N; ++i) { // leafnode에 입력받기
        cin >> ST.arr[i];
    }
    ST.construct();

    int M{}; cin >> M; // 쿼리 개수
    for (int i{}; i < M; ++i) {
        int a{}, b{}, c{}, d{};
        cin >> a;
        if (a == 1) {
            cin >> b >> c >> d;
            ST.Query(b, c + 1, d);
        }
        else {
            cin >> b >> c;
            cout << ST.XOR(b, c + 1) << '\n';
        }
    }
    return 0;
}