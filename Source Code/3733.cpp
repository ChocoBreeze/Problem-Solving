// 2020KB, 0ms
#include <iostream>

using namespace std;

int main() {
    cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
    int N{}, S{};
    while(cin >> N >> S) { 
        cout << S / (N+1) << '\n';
    }
    return 0;
}