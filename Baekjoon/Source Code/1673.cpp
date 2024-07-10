// 2020KB, 0ms
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
    while(1) {
        int n{}, k{}; cin >> n >> k;
        if(cin.eof()) break;
        int answer{n};
        while(1) {
            int now = n/k;
            if(!now) break;
            answer+=now;
            n%=k, n+=now;
        }
        cout << answer<< '\n';
    }
    return 0;
}