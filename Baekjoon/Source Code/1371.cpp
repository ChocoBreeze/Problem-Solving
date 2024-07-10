#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main() {
    cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
    string str;
    vector<int> cnt(26,0);
    int maxCnt{};
    while(cin >> str) {
        for(auto& c : str) {
            cnt[c-'a']++;
            maxCnt = max(maxCnt, cnt[c-'a']);
        }
    }

    for(int i{};i<26;++i) {
        if(cnt[i]==maxCnt) {
            cout << static_cast<char>(i + 'a');
        }
    }
    cout << '\n';
    return 0;
}