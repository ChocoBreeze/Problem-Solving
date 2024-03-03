// 2020KB, 0ms
#include <iostream>

using namespace std;

int main() {
    cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
    int N{}; cin >> N;
    int tt{10};
    while(1) {
        if(N/tt == 0) break;
        if(N%tt > 4 * (tt/10)) {
            N /= tt;
            N+=1;
            N*=tt;
        }
        else {
            N/=tt;
            N*=tt;
        }
        tt*=10;
    }
    cout << N << '\n';
    return 0;
}