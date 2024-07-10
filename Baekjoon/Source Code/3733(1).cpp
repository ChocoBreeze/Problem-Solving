// 2020KB, 0ms
#include <iostream>

using namespace std;

int main()
{
    cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
    while(1) { 
        int N{}, S{}; cin >> N >> S;
        if(cin.fail()) break;
        cout << S / (N+1) << '\n';
    }
    return 0;
}