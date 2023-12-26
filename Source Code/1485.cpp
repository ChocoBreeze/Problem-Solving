// 바보
// 네 변의 길이가 같고, 두 대각선의 길이가 같음.
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;
using coord = pair<ll, ll>;

int main() {
    cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
    int T{}; cin >> T;

    while (T--) {
        vector<coord> cs(4,make_pair(0,0));
        for (coord& c : cs) {
            cin >> c.first >> c.second;
        }

        vector<ll> len;
        for (int i{}; i < 4; ++i) {
            for (int j{i+1}; j < 4; ++j) {
                coord& first = cs[i], & second = cs[j];
                len.push_back((first.first - second.first) * (first.first - second.first)
                    + (first.second - second.second) * (first.second - second.second));
            }
        }
        sort(begin(len), end(len));
        // 두 대각선 길이가 같고, 네 변의 길이가 같은지
        if (len[4] == len[5] && len[0] == len[1] && len[1] == len[2] && len[2] == len[3]) {
            cout << "1\n";
        }
        else cout << "0\n";
    }

    return 0;
}