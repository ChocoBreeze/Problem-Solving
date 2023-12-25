#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
    int N, L, D;
    cin >> N >> L >> D;

    const int LIMIT = N * L + (N-1) * 5;
    int dMax = D;
    while(dMax < LIMIT) dMax += D;

    int answer = max(LIMIT, dMax);
    vector<int> musicRange(answer,0);
    bool musicOff{};
    for(int time{}; time < LIMIT;) {
           if(!musicOff) {
               for(int j{};j<L;++j) {
                   musicRange[time+j] = 1;
               }
               time += L;
               musicOff = true;
           }
           else {
               time +=5;
               musicOff = false;
           }
    }

    for(int time{D};time<LIMIT;time+=D) {
        if(!musicRange[time]) {
            answer = time;
            break;
        }
    }
    cout << answer << '\n';
    return 0;
}