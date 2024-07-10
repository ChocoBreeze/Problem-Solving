// dp[j] = max(dp[j], dp[j - (i + 1)] + P[i]);
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int N;
    cin >> N;
    vector<int> P(N,0);
    for (int i = 0; i < N; ++i) {
        cin >> P[i];
    }
    vector<int> dp(N + 1, 0);
    for (int i = 0; i < N; ++i) {
        if (i == 0) {
            for (int j = 1; j <= N; ++j) {
                dp[j] = P[i] * j;
            }
        }
        else {
            for (int j = 1; j <= N; ++j) {
                if (j >= i + 1) {
                    dp[j] = max(dp[j], dp[j - (i + 1)] + P[i]);
                }
            }
        }
    }
    cout << dp[N];
    return 0;
}