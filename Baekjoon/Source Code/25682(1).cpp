// 17660KB, 100ms
#include <iostream>
#include <climits>
#include <algorithm>
#include <vector>

using namespace std;
int wSum[2001][2001]{};
// 시작이 W, 시작이 B
// 하나만 계산해줘도 됨

int main()
{
    cin.tie(NULL)->sync_with_stdio(false);
    int N, M, K;
    cin >> N >> M >> K;
    for (int n{1}; n <= N; ++n)
    {
        for (int m{1}; m <= M; ++m)
        {
            char c;
            cin >> c;
            wSum[n][m] = wSum[n][m - 1] + wSum[n - 1][m] - wSum[n - 1][m - 1];
            if ((n + m) & 1)
            {
                if (c == 'W')
                    wSum[n][m]++;
            }
            else
            {
                if (c != 'W')
                    wSum[n][m]++;
            }
        }
    }

    int ans = INT_MAX, kk = K * K;
    for (int n{K}; n <= N; ++n)
    {
        for (int m{K}; m <= M; ++m)
        {
            int W = wSum[n][m] - wSum[n][m - K] - wSum[n - K][m] + wSum[n - K][m - K];
            ans = min({ans, W, kk - W});
        }
    }

    cout << ans << '\n';
    return 0;
}