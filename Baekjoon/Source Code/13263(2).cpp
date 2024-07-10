// https://stonejjun.tistory.com/52
#include <iostream>
#include <vector>

using namespace std;

using ll = long long;
using pii = pair<ll, ll>;

struct lin {
    ll a, b; // 기울기, 절편
    lin(ll a, ll b) : a(a), b(b) {}
    lin() = default;
};

int sz{};
vector<lin> stk; // stack이지만, index 접근 가능하도록
double cx(ll a, ll b) { // cross - 교점 계산
    return 1.0 * static_cast<double>(stk[a].b - stk[b].b) / (stk[b].a - stk[a].a);
}
void insert(lin v) { // 필요없는 직선은 다 빼고 마지막 직선 push
    stk[sz] = v;
    // 기존 직선을 지워야 하는 경우: 기존 마지막 두 직선과의 교점 > 기존 마지막 직선과 새 직선의 교점
    while (1 < sz && cx(sz - 2, sz - 1) > cx(sz - 1, sz)) {
        stk[sz - 1] = stk[sz]; // 마지막 직선 교체
        sz--;
    }
    sz++;
}
ll sol(ll x) {
    int lo{}, hi = sz - 1;
    while (lo < hi) {
        int mid = lo + ((hi - lo) >> 1);
        if (cx(mid, mid + 1) <= x) lo = mid + 1;
        else hi = mid;
    }
    return stk[lo].a * x + stk[lo].b;
}

int main() {
    cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
    int n{}; cin >> n;
    const int SIZE = n + 1;
    vector<ll> arr(SIZE, 0), brr(SIZE, 0), dp(SIZE, 0);
    stk.assign(SIZE, lin());
    for (int i = 1; i <= n; ++i) cin >> arr[i];
    for (int i = 1; i <= n; ++i) cin >> brr[i];

    lin l{brr[1], 0}; // l.a = brr[1], l.b = 0;
    // dp[1] = 0; (초기값 = 0)

    insert(l); // 초기 직선
    for (int i = 2; i <= n; ++i) {
        dp[i] = sol(arr[i]); // 주어진 x좌표를 포함하는 선분(fpos)을 이분 탐색으로 찾음
        l.a = brr[i], l.b = dp[i];
        insert(l);
    }
    cout << dp[n] << '\n';
    return 0;
}