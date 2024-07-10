// 2020KB, 0ms
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
    int L{}; cin >> L;
    vector<int> vec(L,0);
    for(int& v : vec) cin >> v;
    int n{}; cin >> n;
    sort(begin(vec), end(vec));

    int s{}, e{1010};
    for(int& v : vec) {
        if(v==n) {
            cout << "0\n";
            return 0;
        }
        if(v < n) s = max(s,v);
        if(v > n) e = min(e, v);
    }
    ++s;
    // cout << s << ' ' << e << '\n';
    int answer{};
    for(int i{s};i<e;++i) {
        for(int j{i+1};j<e;++j) {
            if(i<=n && j >=n) ++answer;
        }
    }
    cout << answer << '\n';
    return 0;
}