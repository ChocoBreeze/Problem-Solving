// 2020KB, 0ms
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
    int N{}; cin >> N;
    vector<int> trophy(N,0);
    for(int& tr : trophy) cin >> tr;
    int l{1}, r{1};
    int last = trophy[0];
    for(int i{1};i<N;++i) {
        if(last < trophy[i]) ++l;
        last = max(last, trophy[i]);
    }
    last = trophy.back();
    for(int i{N-2};i>=0;--i) {
        if(last < trophy[i]) ++r;
        last = max(last, trophy[i]);
    }
    cout << l << '\n' << r << '\n';
    return 0;
}