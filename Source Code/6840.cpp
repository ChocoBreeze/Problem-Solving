// 2020KB, 0ms
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
    vector<int> vec(3,0);
    for(int& v : vec) cin >> v;
    sort(begin(vec), end(vec));
    cout << vec[1] << '\n';
    return 0;
}