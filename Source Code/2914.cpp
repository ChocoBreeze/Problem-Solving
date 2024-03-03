// 2020KB, 0ms
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
    int A{}, I{}; cin >> A >> I;
    
    cout << A * (I-1) + 1 << '\n';
    
    return 0;
}