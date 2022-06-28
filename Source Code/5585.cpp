#include<iostream>
#include<vector>

using namespace std;

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int N, cnt = 0;
    cin >> N;
    N = 1000 - N;
    vector<int> ch= {500,100,50,10,5,1};
    for(auto &i : ch) {
        if(N/i>=1) cnt+=(N/i);
        N%=i;
    }
    cout << cnt;
    return 0;
}