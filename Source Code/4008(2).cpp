// Convex Hull Trick(CHT)
// https://m.blog.naver.com/kks227/221418495037
// O(N)
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

struct LinearFunc { // f(x) = ax + b, x >= s
    ll a, b;
    double s; // 다른 직선과 교점
    LinearFunc() : LinearFunc(1, 0) {}
    LinearFunc(ll a1, ll b1) : a(a1), b(b1), s(0) {}
};

// 두 직선 f, g의 교점의 x좌표를 구함
inline double cross(const LinearFunc& f, const LinearFunc& g) {
    // f.ax + f.b = g.ax + g.b
    // x = (g.b - f.b) / (f.a - g.a)
    return static_cast<double>(g.b - f.b) / (f.a - g.a); // 일부러 실수형이 아닌 정수형을 넣은건가?
}

int main() {
    // 입력받기
    cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
    int N{}; cin >> N;
    ll a, b, c; cin >> a >> b >> c;
    vector<ll> X(N, 0), pSum(N + 1, 0);
    for (int n{}; n < N; ++n) {
        cin >> X[n];
        pSum[n + 1] = pSum[n] + X[n];
    }

    vector<ll> dp(N + 1, 0);
    // dp[0] = 0; (남아 있어야 함)
    // dp[i] = max(A(i)B(j) + C(j) + D(i)) = max(A(i)B(j) + C(j)) + D(i)
    // A(i) : slope(직선 기울기), B(j) : x(변수), C(j) : y-intercept(y절편), D(i) : constant(상수)

    vector<LinearFunc> f(N + 1);
    int top{}, fpos{};
    for (int i = 1; i <= N; ++i) {
        // i-1번에 해당하는 새로운 직선을 스택의 top에 쌓음
        ll slope = -2 * a * pSum[i - 1]; // A(i)
        ll yIntercept = a * pSum[i - 1] * pSum[i - 1] - b * pSum[i - 1] + dp[i - 1]; // C(j)

        LinearFunc g(slope, yIntercept); // 기울기, 절편
        while (top > 0) {
            g.s = cross(f[top - 1], g);
            if (f[top - 1].s < g.s) break;
            // 쌓기 전에, top과 교점을 구해서 top의 시작점보다 교점이 앞이면 pop
            --top;
        }
        f[top++] = g;

        ll x = pSum[i]; // B(j)
        ll constant = a * pSum[i] * pSum[i] + b * pSum[i] + c; // D(i)
        while (fpos + 1 < top && f[fpos + 1].s < x) ++fpos; // fpos가 x좌표를 포함할 때까지 증가시킴
        dp[i] = f[fpos].a * x + f[fpos].b + constant;// i번째 dp 값 계산
    }

    // 결과 출력
    cout << dp.back() << '\n'; // dp[N-1]
    return 0;
}