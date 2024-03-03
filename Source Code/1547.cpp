// 2020KB, 0ms
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
    vector<int> vec{0, 1, 2, 3};
    int M{}; cin >> M;
    for(int m{};m<M;++m) {
        int x{}, y{}; cin >> x >> y;
        if(x==y) continue;
        swap(vec[x], vec[y]);
    }
    for(int i{};i<4;++i) {
        if(vec[i] == 1) cout << i << '\n';
    }
    return 0;
}