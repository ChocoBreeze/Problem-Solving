// 2020KB, 8ms
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
    int N{}, L{}; cin >> N >> L;
    int cnt{};
    for(int n{1};;++n) {
        int tmpN = n;
        while(tmpN) {
            int last = tmpN % 10;
            if(last == L) break;
            tmpN /= 10;
        }
        if(tmpN) continue;
        ++cnt;
        if(N==cnt) {
            cout << n << '\n';
            break;
        }
    }
    return 0;
}