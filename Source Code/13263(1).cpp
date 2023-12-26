// Convex Hull Trick(CHT)
// O(NlogN)
// https://m.blog.naver.com/kks227/221418495037
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;
constinit const int MAX = 100000;

struct LinearFunc { // f(x) = ax + b, x >= s
    ll a, b;
    double s; // 다른 직선과 교점
    LinearFunc() : LinearFunc(1, 0) {}
    LinearFunc(ll a1, ll b1) : a(a1), b(b1), s(0) {}
};

// 두 직선 f, g의 교점의 x좌표를 구함
inline double cross(LinearFunc& f, LinearFunc& g) {
    // f.ax + f.b = g.ax + g.b
    // x = (g.b - f.b) / (f.a - g.a)
    return static_cast<double>(g.b - f.b) / (f.a - g.a); // 일부러 실수형이 아닌 정수형을 넣은건가?
}

int main() {
    // 입력받기
    cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
    int N{}; cin >> N;
    vector<int> A(N, 0), B(N, 0); // int A[MAX], B[MAX];
    for (int& a : A) cin >> a;
    for (int& b : B) cin >> b;

    vector<ll> dp(N, 0); // long long dp[MAX] = {0};
    // dp[0] = 0, dp 테이블을 채우면서 "f(.) = B[i]*x + dp[i]" 를 스택에 쌓음

    vector<LinearFunc> f(N); //   LinearFunc f[MAX];
    int top{};
    for (int i = 1; i < N; ++i) {
        // i-1번에 해당하는 새로운 직선을 스택의 top에 쌓음
        LinearFunc g(B[i - 1], dp[i - 1]);
        while (top > 0) {
            g.s = cross(f[top - 1], g);
            if (f[top - 1].s < g.s) break;
            // 쌓기 전에, top과 교점을 구해서 top의 시작점보다 교점이 앞이면 pop
            --top;
        }
        f[top++] = g;

        ll x = A[i];
        // 주어진 x좌표를 포함하는 선분(fpos)을 이분 탐색으로 찾음
        int fpos = top - 1;
        if (x < f[top - 1].s) {
            int lo{}, hi = top - 1;
            while (lo + 1 < hi) {
                int mid = lo + ((hi - lo) >> 1);
                (x < f[mid].s ? hi : lo) = mid;
            }
            fpos = lo;
        }
        // i번째 dp 값 계산
        dp[i] = f[fpos].a * x + f[fpos].b;
    }

    // 결과 출력
    cout << dp.back() << '\n'; // dp[N-1]
    return 0;
}