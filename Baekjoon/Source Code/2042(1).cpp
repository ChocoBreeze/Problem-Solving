// Fenwick Tree
// https://www.acmicpc.net/blog/view/21
// 17652KB, 220ms
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

ll sum(vector<ll>& tree, ll i) {
    ll ans{};
    while (i > 0) {
        ans += tree[i];
        i -= (i & -i);
    }
    return ans;
}
void update(vector<ll>& tree, ll i, ll diff) {
    while (i < static_cast<ll>(tree.size())) {
        tree[i] += diff;
        i += (i & -i);
    }
}

int main() {
    cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
    int N{}, M{}, K{}; cin >> N >> M >> K;
    // 1번 인덱스 base
    vector<ll> A(N + 1, 0), tree(N + 1, 0);
    for (int i{ 1 }; i <= N; ++i) {
        cin >> A[i];
        update(tree, i, A[i]);
    }

    for (int i{}; i < M + K; ++i) {
        ll a{}, b{}, c{}; cin >> a >> b >> c;
        if (a == 1) { // b번째 수를 c로
            update(tree, b, c - A[b]);
            A[b] = c;
        }
        else { // a == 2 : b번째 수 ~ c번째 수 까지 합
            cout << sum(tree, c) - sum(tree, b - 1) << '\n';
        }
    }

    return 0;
}