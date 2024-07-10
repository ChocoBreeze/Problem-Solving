/*
N+1
2N+2
3N+3
.
.
.
(N-1)N + N-1

N(1+2+...+N-1) + 1+2+...+N-1
=(N+1)(1+2+...+N-1)
=(N+1)N(N-1)/2
*/
// 2020KB, 0ms
#include <iostream>

using namespace std;

int main() {
    cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
    unsigned long long N{}; cin >> N;
    cout << (N-1)*N*(N+1)/2 << '\n';
    return 0;
}