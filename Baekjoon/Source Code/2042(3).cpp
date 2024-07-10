// Segment Tree
// non-Recursion
// 18408KB, 208ms

#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

void InitTree(vector<ll>& tree, int leafStart) {
    for (int i{ leafStart - 1 }; i >= 1; --i) {
        tree[i] = tree[(i << 1)] + tree[(i << 1) + 1];
    }
}
void Update(vector<ll>& tree, int leafStart, ll index, ll value) {
    index += leafStart - 1;
    tree[index] = value;
    while (index > 1) {
        index >>= 1;
        tree[index] = tree[(index << 1)] + tree[(index << 1) + 1];
    }
}

ll Sum(vector<ll>& tree, int leafStart, ll s, ll e) {
    ll sum{};
    s += leafStart - 1, e += leafStart - 1;
    while (s <= e) {
        if ((s & 1) == 1) sum += tree[s]; // s가 right일 때
        if ((e & 1) == 0) sum += tree[e]; // e가 left일 때
        s = (s + 1) >> 1;
        e = (e - 1) >> 1;
    }
    return sum;
}

int main() {
    cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
    int N{}, M{}, K{}; cin >> N >> M >> K;

    int leafStart{ 1 };
    while (leafStart < N) leafStart <<= 1;
    leafStart <<= 1;
    vector<ll> tree(leafStart, 0);
    leafStart >>= 1;

    for (int n{}; n < N; ++n) {
        cin >> tree[leafStart + n];
    }
    InitTree(tree, leafStart);

    for (int i{}; i < M + K; ++i) {
        ll a{}, b{}, c{}; cin >> a >> b >> c;
        if (a == 1) { // b번째 수를 c로
            Update(tree, leafStart, b, c);
        }
        else { // a == 2 : b번째 수 ~ c번째 수 까지 합
            cout << Sum(tree, leafStart, b, c) << '\n';
        }
    }

    return 0;
}