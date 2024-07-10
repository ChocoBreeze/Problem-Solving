// https://m.blog.naver.com/kks227/220824350353
// 기존에 짰던 것 보다 이게 더 간단하다!

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

// 세그먼트 트리 구조체
struct SegTree {
    int start; // leaf node 시작점
    vector<ll> arr, lazy;

    // 생성자
    SegTree(int tmpN) : start(tmpN >> 1), arr(tmpN, 0), lazy(tmpN, 0) { }

    // 리프 노드들의 값을 먼저 입력한 후 전체 세그먼트 트리 구축
    void construct() {
        for (int i{ start - 1 }; i > 0; --i) {
            arr[i] = arr[i * 2] + arr[i * 2 + 1];
        }
    }

    // 구간 [ns, ne)인 node의 lazy 값을 propagate
    void propagate(int node, int ns, int ne) {
        // lazy 값이 존재하면 실행
        if (lazy[node] != 0) {
            // 리프 노드가 아니면 자식들에게 lazy 미룸
            if (node < start) {
                lazy[node * 2] += lazy[node];
                lazy[node * 2 + 1] += lazy[node];
            }
            // 자신에 해당하는 만큼의 값을 더함
            arr[node] += lazy[node] * (ne - ns);
            lazy[node] = 0;
        }
    }

    // 구간 [s, e)에 k를 더하라
    void add(int s, int e, ll k) { add(s, e, k, 1, 0, start); }
    void add(int s, int e, ll k, int node, int ns, int ne) {
        // 일단 propagate
        propagate(node, ns, ne);

        if (e <= ns || ne <= s) return; // 해당되는 구간이 아님.
        if (s <= ns && ne <= e) {
            // 이 노드가 구간에 완전히 포함되면 lazy 부여 후 propagate
            lazy[node] += k;
            propagate(node, ns, ne);
            return;
        }
        int mid = ns + (ne - ns) / 2;
        add(s, e, k, node * 2, ns, mid);
        add(s, e, k, node * 2 + 1, mid, ne);
        // 마지막에 자식들의 값을 사용해 다시 자신의 값 갱신
        arr[node] = arr[node * 2] + arr[node * 2 + 1];
    }

    // 구간 [s, e)의 합을 구하라
    long long sum(int s, int e) { return sum(s, e, 1, 0, start); }
    long long sum(int s, int e, int node, int ns, int ne) {
        // 일단 propagate
        propagate(node, ns, ne);

        if (e <= ns || ne <= s) return 0; // 맞는 범위가 아님
        if (s <= ns && ne <= e) return arr[node]; // 정확히 포함되는 구간

        int mid = ns + (ne - ns) / 2;
        return sum(s, e, node * 2, ns, mid) + sum(s, e, node * 2 + 1, mid, ne);
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // 초기 세그먼트 트리 입력받기
    int N, M, K; // 수의 개수, 변경이 일어나는 횟수, 구간의 합을 구하는 횟수
    cin >> N >> M >> K;
    int tmpN{ 1 }; // leaf node 개수
    while (tmpN < N) {
        tmpN <<= 1;
    }
    tmpN <<= 1;

    SegTree ST(tmpN);
    for (int i{}; i < N; ++i) { // leafnode에 입력받기
        cin >> ST.arr[ST.start + i];
    }
    ST.construct();

    // 쿼리 처리
    for (int i{}; i < M + K; ++i) {
        int a{}, b{}, c{};
        ll d{};
        cin >> a;
        if (a == 1) {
            cin >> b >> c >> d;
            ST.add(b - 1, c, d);
        }
        else {
            cin >> b >> c;
            cout << ST.sum(b - 1, c) << '\n';
        }
    }
    return 0;
}