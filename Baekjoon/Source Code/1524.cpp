// 2708KB, 68ms
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{

    cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
    int T{}; cin >> T;
    while(T--) {
        int N{}, M{}; cin >> N >> M;
        vector<int> S(N,0), B(M,0);
        for(int& s : S ) cin >> s;
        for(int& b : B) cin >> b;
        sort(begin(S), end(S));
        sort(begin(B), end(B));
        int si{}, bi{};
        while(1) {
            if(si==N) {
                cout << "B\n";
                break;
            }
            if(bi==M) {
                cout << "S\n";
                break;
            }
            if(S[si]< B[bi]) ++si;
            else ++bi;
        }
    }
    return 0;
}