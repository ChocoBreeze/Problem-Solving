// 2020KB, 0ms
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
    int M{}, N{}; cin >> M >> N;
    int sum{}, minV{1<<30};
    for(int i{1};i*i<=N;++i) {
       if(i*i>=M) {
            sum += i*i;
            minV = min(minV, i*i);
        }
    }
    if(sum==0) cout << "-1\n";
    else {
        cout << sum << '\n' << minV;
    }
    return 0;
}