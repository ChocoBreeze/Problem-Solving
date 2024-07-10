// Segment Tree - Recursion
// https://book.acmicpc.net/ds/segment-tree
// https://www.acmicpc.net/problem/2042
// 26224KB, 224ms
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

void init(vector<ll>& A, vector<ll>& tree, ll node, ll start, ll end) {
    if (start == end) {
        tree[node] = A[start];
    }
    else {
        ll mid = start + (end - start) / 2;
        init(A, tree, node * 2, start, mid); // left
        init(A, tree, node * 2 + 1, mid + 1, end); // right
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }
}
void update(vector<ll>& A, vector<ll>& tree, int node, int start, int end, ll index, ll val) {
    if (index < start || index > end) { // out of range
        return;
    }
    if (start == end) {
        A[index] = val;
        tree[node] = val;
        return;
    }
    int mid = start + (end - start) / 2;
    update(A, tree, node * 2, start, mid, index, val); // left
    update(A, tree, node * 2 + 1, mid + 1, end, index, val); // right
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}
ll query(vector<ll>& tree, int node, int start, int end, ll left, ll right) {
    if (left > end || right < start) { // out of range
        return 0;
    }
    if (left <= start && end <= right) {
        return tree[node];
    }
    int mid = start + (end - start) / 2;
    ll lsum = query(tree, node * 2, start, mid, left, right);
    ll rsum = query(tree, node * 2 + 1, mid + 1, end, left, right);
    return lsum + rsum;
}

int main() {
    cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
    int N{}, M{}, K{}; cin >> N >> M >> K;
    // 1번 인덱스 base
    vector<ll> A(N, 0);

    int treeSize{ 1 };
    while (treeSize < N) treeSize <<= 1;
    treeSize <<= 1;
    vector<ll> tree(treeSize, 0);

    for (auto& i : A) cin >> i;
    init(A, tree, 1, 0, N - 1);

    for (int i{}; i < M + K; ++i) {
        ll a{}, b{}, c{}; cin >> a >> b >> c;
        if (a == 1) { // b번째 수를 c로
            update(A, tree, 1, 0, N - 1, b - 1, c);
        }
        else { // a == 2 : b번째 수 ~ c번째 수 까지 합
            cout << query(tree, 1, 0, N - 1, b - 1, c - 1) << '\n';
        }
    }

    return 0;
}