#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
    int N{}; cin >> N;
    vector<vector<int>> info(N, vector<int>(5,0));
    for(int n{}; n<N;++n) {
        for(int g=0;g<5;++g) {
            cin >> info[n][g];
        }
    }

    vector<vector<int>> chk(N,vector<int>(N,0));
    for(int g=0;g<5;++g) {
        vector<vector<int>> board(10);
        for(int n{}; n<N;++n) {
            board[info[n][g]].push_back(n);
        }
        for(int b=1; b < 10; ++b) {
            auto& row = board[b];
            for(auto it = begin(row);it!=end(row); ++it) {
                for(auto it2 = it +1; it2!=end(row);++it2) {
                    chk[*it][*it2] = 1;
                    chk[*it2][*it] = 1;
                }
            } 
        }
    }

    int answer{}, maxV{};
    for(int n{}; n<N;++n) {
        int cnt{};
        for(int i{}; i<N;++i) {
            if(chk[n][i]) ++cnt;
        }
        if(maxV < cnt) {
            maxV = cnt;
            answer = n;
        }
    }
    cout << answer + 1<< '\n';
    return 0;
}