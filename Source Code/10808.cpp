#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    string str;
    cin >> str;
    vector<int> count(26,0);
    for(auto& s : str) {
        count[s-'a']++;
    }
    for(auto& c : count) {
        cout << c << " ";
    }
    
    return 0;
}