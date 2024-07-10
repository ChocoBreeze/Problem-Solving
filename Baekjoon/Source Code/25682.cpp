// 37528KB, 116ms
#include <iostream>
#include <climits>
#include <algorithm>
#include <vector>

using namespace std;
char Map[2010][2010]{};
int wSum[2010][2010]{}, bSum[2010][2010]{};
// 시작이 W, 시작이 B

int main()
{
    cin.tie(NULL)->sync_with_stdio(false);
    int N, M, K;
    cin >> N >> M >> K;
    for (int n{1}; n <= N; ++n)
    {
        for (int m{1}; m <= M; ++m)
        {
            cin >> Map[n][m];
            wSum[n][m] = wSum[n][m - 1] + wSum[n - 1][m] - wSum[n - 1][m - 1];
            bSum[n][m] = bSum[n][m - 1] + bSum[n - 1][m] - bSum[n - 1][m - 1];
            if ((n + m) & 1)
            {
                if (Map[n][m] == 'W')
                    wSum[n][m]++;
                else
                    bSum[n][m]++;
            }
            else
            {
                if (Map[n][m] == 'W')
                    bSum[n][m]++;
                else
                    wSum[n][m]++;
            }
        }
    }

    int ans = INT_MAX;
    for (int n{K}; n <= N; ++n)
    {
        for (int m{K}; m <= M; ++m)
        {
            int W = wSum[n][m] - wSum[n][m - K] - wSum[n - K][m] + wSum[n - K][m - K];
            int B = bSum[n][m] - bSum[n][m - K] - bSum[n - K][m] + bSum[n - K][m - K];
            ans = min({ans, W, B});
        }
    }

    cout << ans << '\n';
    return 0;
}